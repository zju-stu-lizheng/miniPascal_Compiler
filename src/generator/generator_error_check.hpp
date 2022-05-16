#include <iostream>
#include <string>
#include "../contents/Contents.hpp"
#define GEN_DEBUG


void Record_and_Output_Error(bool is_error, std::string error_str, std::pair<int, int> location);

bool Check_Result_NULLPtr(std::shared_ptr<Custom_Result> ptr, std::string func_name, std::pair<int, int> location, int cnt = -1);

bool Check_Multiple_Label(std::shared_ptr<Label_Type> label, std::pair<int, int> location);