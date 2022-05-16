#include "generator_error_check.hpp"

void Record_and_Output_Error(bool is_error, std::string error_str, std::pair<int, int> location){
    if (is_error){
        Contents::error_record->Add_Error_Information(error_str,location);
        std::cerr << error_str;
    }
}

bool Check_Result_NULLPtr(std::shared_ptr<Custom_Result> ptr, std::string func_name, std::pair<int, int> location, int cnt ){
    bool is_null = (ptr == nullptr);
    std::string error_str = "Meet nullptr at " + func_name + " code generation! ";
    if (cnt != -1)
        error_str += "At parameter: " + std::to_string(cnt) + "\n";

    Record_and_Output_Error(is_null,error_str,location);
    return !is_null;
}

bool Check_Multiple_Label(std::shared_ptr<Label_Type> label, std::pair<int, int> location){
    bool exist_label = (Contents::GetCurrentBlock()->label_2_block.count(label) > 0);
    std::string error_str = "Multiple label";

    Record_and_Output_Error(exist_label,error_str,location);
    return !exist_label;
}