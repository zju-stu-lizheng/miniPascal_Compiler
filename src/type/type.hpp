#pragma once

namespace Our_Type{
    class PascalType{
    public:
        enum class Type_Group{
            BUILT_IN, ENUMERATE, SUBRANGE, ARRAY, STRING, RECORD
        };

        Type_Group type_group;

        PascalType(Type_Group _type_group){
            type_group = _type_group;
        }

        bool isSimple() const{
            return type_group == Type_Group::BUILT_IN;
        }

    };

    bool isEqual(const PascalType *const a, PascalType *const b ){
        //判断属性是否相等   
    }

    
};