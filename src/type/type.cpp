#include "type.hpp"

namespace Our_Type
{
    class Pascal_Type;

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
        }
        else if (p_type->type_group == Our_Type::Pascal_Type::Type_Group::STRING)
        {
            Our_Type::String_Type *str = (Our_Type::String_Type *)p_type;
            return llvm::ArrayType::get(GetLLVMType(context, CHAR_TYPE), (uint64_t)(str->len));
        }
        else if (p_type->type_group == Our_Type::Pascal_Type::Type_Group::ARRAY) {
            Our_Type::Array_Type *array = (Our_Type::Array_Type *) p_type;
            llvm::ArrayType *ret = nullptr;
            int len = array->subrange.begin_2_end.second - array->subrange.begin_2_end.first + 1;
            std::cout << "creating array of length " <<len << std::endl;
            
            ret = llvm::ArrayType::get(GetLLVMType(context, array->element_type), (uint64_t) len);
            return ret;
        }
        else if (p_type->type_group == Our_Type::Pascal_Type::Type_Group::RECORD)
        {
            Our_Type::Record_Type *record = (Our_Type::Record_Type *)p_type;
            std::vector<llvm::Type *> llvm_type_vec;
            for (auto t : record->type_list)
            {
                llvm_type_vec.push_back(GetLLVMType(context, t));
            }
            return llvm::StructType::get(context, llvm_type_vec);
        }
        else if (p_type->type_group == Our_Type::Pascal_Type::Type_Group::ENUMERATE)
        {
            // does not mean that enum type does not exist
            // it means that we do not consider it as a basic type
            return llvm::Type::getInt32Ty(context);
        }
        else if (p_type->type_group == Our_Type::Pascal_Type::Type_Group::SUBRANGE)
        {
            // not implemented
            return nullptr;
        }
        //report error
        return nullptr;
    }
    bool isEqual(const Our_Type::Pascal_Type *const a, const Our_Type::Pascal_Type *const b)
    {
        //判断属性是否相等
        if (a == nullptr && b == nullptr)
            return true;
        if (a == nullptr || b == nullptr)
            return false;

        //先判断两个的所属类型组别是否相同
        if (a->type_group != b->type_group)
            return false;
        //如果是内置pascal变量
        if (a->type_group == Our_Type::Pascal_Type::Type_Group::BUILT_IN)
            return ((Our_Type::Buildin_Type *)a)->buildin_type_name == ((Our_Type::Buildin_Type *)b)->buildin_type_name;
        //如果是结构变量
        else if (a->type_group == Our_Type::Pascal_Type::Type_Group::RECORD)
        {
            Our_Type::Record_Type *ra = (Our_Type::Record_Type *)a, *rb = (Our_Type::Record_Type *)b;
            if (ra->name_list.size() != rb->name_list.size())
                return false;
            for (int i = 0; i < ra->name_list.size(); i++)
            {
                if (ra->name_list[i] != rb->name_list[i])
                    return false;
                if (ra->type_list[i] != rb->type_list[i])
                    return false;
            }
        }
        //如果是数组变量
        else if (a->type_group == Our_Type::Pascal_Type::Type_Group::ARRAY)
        {
            Our_Type::Array_Type *aa = (Our_Type::Array_Type *)a, *bb = (Our_Type::Array_Type *)b;
            if (aa->subrange.begin_2_end != bb->subrange.begin_2_end)
                return false;
            return isEqual((Our_Type::Pascal_Type *)aa->element_type, (Our_Type::Pascal_Type *)bb->element_type);
        }
        //如果是SUB-RANGE类型
        else if (a->type_group == Our_Type::Pascal_Type::Type_Group::SUBRANGE)
        {
            Our_Type::Subrange_Type *sa = (Our_Type::Subrange_Type *)a, *bb = (Our_Type::Subrange_Type *)b;
            return (sa->begin_2_end.first == bb->begin_2_end.first && sa->begin_2_end.second == bb->begin_2_end.second);
        }
        //如果是字符串
        else if (a->type_group == Our_Type::Pascal_Type::Type_Group::STRING)
        {
            Our_Type::String_Type *sa = (Our_Type::String_Type *)a, *bb = (Our_Type::String_Type *)b;
            return sa->len == bb->len;
        }
        //如果是枚举
        else if (a->type_group == Our_Type::Pascal_Type::Type_Group::ENUMERATE)
        {
            Our_Type::Enumerate_Type *sa = (Our_Type::Enumerate_Type *)a, *bb = (Our_Type::Enumerate_Type *)b;
            if (sa->enum_list.size() != bb->enum_list.size())
                return false;
            for (int i = 0; i < sa->enum_list.size(); i++)
            {
                if (sa->enum_list[i] != bb->enum_list[i])
                    return false;
            }
            return true;
        }
        else
        {
            #ifdef GEN_DEBUG
            std::cout << "Unknown Error Occurred at Our_Type::isEqual" << std::endl;
            #endif
            
            return false;
        }
        #ifdef GEN_DEBUG
        std::cout << "Bad Error Occurred at Our_Type::isEqual" << std::endl;
        #endif
        return false;
    }

    bool Pascal_Type::isIntegerTy() const{
        return isEqual(this,INT_TYPE);
    }

    bool Pascal_Type::isCharTy() const{
        return isEqual(this,CHAR_TYPE);
    }

    bool Pascal_Type::isFloatingPointTy() const{
        return isEqual(this,REAL_TYPE);
    }
}
