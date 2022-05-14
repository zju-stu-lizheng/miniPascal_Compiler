#pragma once
#include <vector>
#include <string>

namespace Our_Type{

    class Pascal_Type{
    public:
        enum class Type_Group{
            BUILT_IN, 
            ENUMERATE, 
            SUBRANGE, 
            ARRAY, 
            STRING, 
            RECORD
        };

        Type_Group type_group;

        Pascal_Type(Type_Group _type_group){
            type_group = _type_group;
        }

        bool isSimple() const{
            return type_group == Type_Group::BUILT_IN;
        }
        bool isEnumerate() const{
            return type_group == Type_Group::ENUMERATE;
        }
        bool isSubrange() const{
            return type_group == Type_Group::SUBRANGE;
        }
        bool isArray() const{
            return type_group == Type_Group::ARRAY;
        }
        bool isString() const{
            return type_group == Type_Group::STRING;
        }
        bool isRecord() const{
            return type_group == Type_Group::RECORD;
        }
    };

    bool isEqual(const Pascal_Type *const a, Pascal_Type *const b ){
        //判断属性是否相等   
    }


    class Buildin_Type : public Pascal_Type{
        public:
            enum class Buildin_Type_Name{
                INT,
                FLOAT,
                BOOLEAN,
                CHAR
            };

            Buildin_Type_Name buildin_type_name;

            Buildin_Type(Buildin_Type_Name _buildin_type_name):
                    buildin_type_name(_buildin_type_name), Pascal_Type(Type_Group::BUILT_IN){}
    };

    class Enumerate_Type: public Pascal_Type{ // string -> constant int
        public:
            std::vector<std::string> enum_list;

            Enumerate_Type(std::vector<std::string> _enum_list):
                enum_list(_enum_list), Pascal_Type(Type_Group::ENUMERATE){}
    };

    class Subrange_Type : public Pascal_Type{
        public:
            std::pair<int,int> begin_2_end; //first->begin, second->end

            Subrange_Type(int _begin, int _end):
                        begin_2_end(std::make_pair(_begin,_end)), Pascal_Type(Type_Group::SUBRANGE){}
    };
    
    class Array_Type : public Pascal_Type{
        public:
            Subrange_Type subrange;
            Pascal_Type* element_type;
        
        Array_Type(Subrange_Type _subrange, Pascal_Type* _element_type):
            subrange(_subrange), element_type(_element_type), Pascal_Type(Type_Group::ARRAY){}
    };

    class String_Type : public Pascal_Type{
        public:
            int len; // string array
        
        String_Type(int _len = 255):len(_len), Pascal_Type(Type_Group::STRING){}

    };

    class Record_Type : public Pascal_Type{
        public:
            std::vector<std::string> name_list;
            std::vector<Pascal_Type*> type_list;

            Record_Type(std::vector<std::string> _name_list, std::vector<Pascal_Type*> _type_list):
            name_list(_name_list), type_list(_type_list), Pascal_Type(Type_Group::RECORD){
            }
    };
};