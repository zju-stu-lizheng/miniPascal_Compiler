#include "type.hpp"

using namespace Our_Type;

llvm::ConstantInt *Array_Type::GetLLVMLow(llvm::LLVMContext &context)
{
    return llvm::ConstantInt::get(llvm::Type::getInt32Ty(context), subrange.begin_2_end.first, true);
}

llvm::ConstantInt *Array_Type::GetLLVMHigh(llvm::LLVMContext &context)
{
    return llvm::ConstantInt::get(llvm::Type::getInt32Ty(context), subrange.begin_2_end.second, true);
}

llvm::Type *Our_Type::GetLLVMType(llvm::LLVMContext &context, Pascal_Type *const p_type)
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
    else if (p_type->type_group == Pascal_Type::Type_Group::STRING)
    {
        String_Type *str = (String_Type *)p_type;
        return llvm::ArrayType::get(GetLLVMType(context, CHAR_TYPE), (uint64_t)(str->len));
    }
    else if (p_type->type_group == Pascal_Type::Type_Group::RECORD)
    {
        Record_Type *record = (Record_Type *)p_type;
        std::vector<llvm::Type *> llvm_type_vec;
        for (auto t : record->type_list)
        {
            llvm_type_vec.push_back(GetLLVMType(context, t));
        }
        return llvm::StructType::get(context, llvm_type_vec);
    }
    else if (p_type->type_group == Pascal_Type::Type_Group::ENUMERATE)
    {
        // does not mean that enum type does not exist
        // it means that we do not consider it as a basic type
        return llvm::Type::getInt32Ty(context);
    }
    else if (p_type->type_group == Pascal_Type::Type_Group::SUBRANGE)
    {
        // not implemented
        return nullptr;
    }
}

bool Our_Type::isEqual(const Pascal_Type *const a, const Pascal_Type *const b)
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
    if (a->type_group == Pascal_Type::Type_Group::BUILT_IN)
        return ((Buildin_Type *)a)->buildin_type_name == ((Buildin_Type *)b)->buildin_type_name;
    //如果是结构变量
    else if (a->type_group == Pascal_Type::Type_Group::RECORD)
    {
        Record_Type *ra = (Record_Type *)a, *rb = (Record_Type *)b;
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
    else if (a->type_group == Pascal_Type::Type_Group::ARRAY)
    {
        Array_Type *aa = (Array_Type *)a, *bb = (Array_Type *)b;
        if (aa->subrange.begin_2_end != bb->subrange.begin_2_end)
            return false;
        return isEqual((Pascal_Type *)aa->element_type, (Pascal_Type *)bb->element_type);
    }
    //如果是SUB-RANGE类型
    else if (a->type_group == Pascal_Type::Type_Group::SUBRANGE)
    {
        Subrange_Type *sa = (Subrange_Type *)a, *bb = (Subrange_Type *)b;
        return (sa->begin_2_end.first == bb->begin_2_end.first && sa->begin_2_end.second == bb->begin_2_end.second);
    }
    //如果是字符串
    else if (a->type_group == Pascal_Type::Type_Group::STRING)
    {
        String_Type *sa = (String_Type *)a, *bb = (String_Type *)b;
        return sa->len == bb->len;
    }
    //如果是枚举
    else if (a->type_group == Pascal_Type::Type_Group::ENUMERATE)
    {
        Enumerate_Type *sa = (Enumerate_Type *)a, *bb = (Enumerate_Type *)b;
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
        std::cout << "Unknown Error Occurred at Our_Type::isEqual" << std::endl;
        return false;
    }
}