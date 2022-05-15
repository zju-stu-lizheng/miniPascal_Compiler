#pragma once
#include <vector>
#include <string>
#include <memory>
#include <iostream>

#include <llvm/IR/Value.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Function.h>

namespace Our_Type
{
    class Pascal_Type
    {
    public:
        enum class Type_Group
        {
            BUILT_IN,
            ENUMERATE,
            SUBRANGE,
            ARRAY,
            STRING,
            RECORD
        };

        Type_Group type_group;

        Pascal_Type(Type_Group _type_group)
        {
            type_group = _type_group;
        }

        bool isSimple() const
        {
            return type_group == Type_Group::BUILT_IN;
        }
        bool isEnumerate() const
        {
            return type_group == Type_Group::ENUMERATE;
        }
        bool isSubrange() const
        {
            return type_group == Type_Group::SUBRANGE;
        }
        bool isArray() const
        {
            return type_group == Type_Group::ARRAY;
        }
        bool isString() const
        {
            return type_group == Type_Group::STRING;
        }
        bool isRecord() const
        {
            return type_group == Type_Group::RECORD;
        }
    };

    // 定义在type.cpp
    bool isEqual(const Pascal_Type *const a, const Pascal_Type *const b);

    class Buildin_Type : public Pascal_Type
    {
    public:
        enum class Buildin_Type_Name
        {
            INT,
            FLOAT,
            BOOLEAN,
            CHAR,
            VOID
        };

        Buildin_Type_Name buildin_type_name;

        Buildin_Type(Buildin_Type_Name _buildin_type_name) : buildin_type_name(_buildin_type_name), Pascal_Type(Type_Group::BUILT_IN) {}
    };

    class Enumerate_Type : public Pascal_Type
    { // string -> constant int
    public:
        std::vector<std::string> enum_list;

        Enumerate_Type(std::vector<std::string> _enum_list) : enum_list(_enum_list), Pascal_Type(Type_Group::ENUMERATE) {}
    };

    class Subrange_Type : public Pascal_Type
    {
    public:
        std::pair<int, int> begin_2_end; // first->begin, second->end

        Subrange_Type(int _begin, int _end) : begin_2_end(std::make_pair(_begin, _end)), Pascal_Type(Type_Group::SUBRANGE) {}
    };

    class Array_Type : public Pascal_Type
    {
    public:
        Subrange_Type subrange;
        Pascal_Type *element_type;

        Array_Type(Subrange_Type _subrange, Pascal_Type *_element_type) : subrange(_subrange), element_type(_element_type), Pascal_Type(Type_Group::ARRAY) {}
    };

    class String_Type : public Pascal_Type
    {
    public:
        int len; // string array

        String_Type(int _len = 255) : len(_len), Pascal_Type(Type_Group::STRING) {}
    };

    class Record_Type : public Pascal_Type
    {
    public:
        std::vector<std::string> name_list;
        std::vector<Pascal_Type *> type_list;

        Record_Type(std::vector<std::string> _name_list, std::vector<Pascal_Type *> _type_list) : name_list(_name_list), type_list(_type_list), Pascal_Type(Type_Group::RECORD)
        {
        }
    };

    const Buildin_Type INT_TYPE_INST(Buildin_Type::Buildin_Type_Name::INT);
    const Buildin_Type REAL_TYPE_INST(Buildin_Type::Buildin_Type_Name::FLOAT);
    const Buildin_Type CHAR_TYPE_INST(Buildin_Type::Buildin_Type_Name::CHAR);
    const Buildin_Type BOOLEAN_TYPE_INST(Buildin_Type::Buildin_Type_Name::BOOLEAN);
    const Buildin_Type VOID_TYPE_INST(Buildin_Type::Buildin_Type_Name::VOID);
    Pascal_Type *const INT_TYPE = (Pascal_Type *)(&INT_TYPE_INST);
    Pascal_Type *const REAL_TYPE = (Pascal_Type *)(&REAL_TYPE_INST);
    Pascal_Type *const CHAR_TYPE = (Pascal_Type *)(&CHAR_TYPE_INST);
    Pascal_Type *const BOOLEAN_TYPE = (Pascal_Type *)(&BOOLEAN_TYPE_INST);
    Pascal_Type *const VOID_TYPE = (Pascal_Type *)(&VOID_TYPE_INST);

    llvm::Type *GetLLVMType(llvm::LLVMContext &context, Pascal_Type *const p_type)
    {
        if (p_type->type_group == Pascal_Type::Type_Group::BUILT_IN)
        {
            if (isEqual(p_type, INT_TYPE))
                return llvm::Type::getInt32Ty(context);
            else if (isEqual(p_type, REAL_TYPE))
                return llvm::Type::getDoubleTy(context);
            else if (isEqual(p_type, CHAR_TYPE))
                return llvm::Type::getInt8Ty(context);
            else if (isEqual(p_type, BOOLEAN_TYPE))
                return llvm::Type::getInt1Ty(context);
            else if (isEqual(p_type, VOID_TYPE))
                return llvm::Type::getVoidTy(context);
            else
                return nullptr;
        }else if(p_type->type_group == Pascal_Type::Type_Group::STRING){
            String_Type *str = (String_Type *) p_type;
            return llvm::ArrayType::get(GetLLVMType(context,CHAR_TYPE),(uint64_t)(str->dim));
        }else if(p_type->type_group == Pascal_Type::Type_Group::RECORD){
            Record_Type *record = (Record_Type *) p_type;
            std::vector<llvm::Type *> llvm_type_vec;
            for (auto t : record->type_list) {
                llvm_type_vec.push_back(GetLLVMType(context, t));
            }
            return llvm::StructType::get(context, llvm_type_vec);
        }else if(p_type->type_group == Pascal_Type::Type_Group::ENUMERATE){
            // does not mean that enum type does not exist
            // it means that we do not consider it as a basic type
            return llvm::Type::getInt32Ty(context);
        }else if(p_type ->type_group == Pascal_Type::Type_Group::SUBRANGE){
            // not implemented
            return nullptr;
        }
    }
};

using namespace Our_Type;

//定义llvm 返回值的类型
class Custom_Result
{
};

//以下类均为Custom_Result的子类

//单独返回一个值()
class Value_Result : public Custom_Result
{
public:
    Value_Result(Our_Type::Pascal_Type *_type, llvm::Value *_value, llvm::Value *_memory = nullptr) : type(_type), value(_value), memory(_memory) {}

    ~Value_Result() = default;

    llvm::Value *GetValue() const
    {
        return value;
    }

    llvm::Value *GetMemory() const
    {
        return memory;
    }

    Pascal_Type *GetType() const
    {
        return type;
    }

    llvm::Type *Get_llvm_Type() const
    {
        return value->getType();
    }

private:
    llvm::Value *value;  // value
    llvm::Value *memory; // point
    Pascal_Type *type;
};

//返回一个identifier 的列表
class Name_List : public Custom_Result
{
private:
    std::vector<std::string> name_list;

public:
    Name_List(const std::vector<std::string> &list) : name_list(list) {}

    ~Name_List() = default;

    const std::vector<std::string> &GetNameList()
    {
        return name_list;
    }
};

//返回一个值 列表
class Value_List_Result : public Custom_Result
{
public:
    Value_List_Result(std::vector<std::shared_ptr<Value_Result>> _value_list) : value_list(_value_list) {}

    ~Value_List_Result() = default;

    const std::vector<std::shared_ptr<Value_Result>> &GetValueList() const
    {
        return value_list;
    }

private:
    std::vector<std::shared_ptr<Value_Result>> value_list;
};

//返回一个类型
class Type_Result : public Custom_Result
{
public:
    Type_Result(Our_Type::Pascal_Type *_type, bool _is_var = false) : type(_type), is_var(_is_var) {}
    const Our_Type::Pascal_Type *GetType() const
    {
        return type;
    }

    const bool GetIsVal() const
    {
        return is_var;
    }

    void SetIsVal(bool _is_var)
    {
        is_var = _is_var;
    }

private:
    Our_Type::Pascal_Type *type;
    bool is_var; // 作为函数参数进行传递时，考虑时值传递还是指针传递
};

//返回一个类型 列表
class Type_List_Result : public Custom_Result
{
public:
    Type_List_Result(std::vector<std::shared_ptr<Type_Result>> _type_list, std::vector<std::string> _name_list) : type_list(_type_list), name_list(_name_list) {}

    const std::vector<std::shared_ptr<Type_Result>> &GetTypeList()
    {
        return type_list;
    }

    const std::vector<std::string> &GetNameList()
    {
        return name_list;
    }

private:
    std::vector<std::shared_ptr<Type_Result>> type_list;
    std::vector<std::string> name_list;
};

//返回一个 声明类型
class Type_Declaration_Result : public Custom_Result
{
private:
    std::vector<std::string> name_list;
    Our_Type::Pascal_Type *type;

public:
    Type_Declaration_Result(std::vector<std::string> _name_list, Our_Type::Pascal_Type *_type) : name_list(_name_list), type(_type) {}
    const std::vector<std::string> &GetNameList()
    {
        return name_list;
    }

    Our_Type::Pascal_Type *GetType()
    {
        return type;
    }
};

//返回一个 声明类型 列表
class Type_Declaration_List_Result : public Custom_Result
{
public:
    Type_Declaration_List_Result() {}
    void AddTypeDeclResult(std::shared_ptr<Type_Declaration_Result> _type_decl_result)
    {
        type_decl_list.push_back(_type_decl_result);
    }
    std::vector<std::shared_ptr<Type_Declaration_Result>> &getTypeDeclList()
    {
        return type_decl_list;
    }

private:
    std::vector<std::shared_ptr<Type_Declaration_Result>> type_decl_list;
};
