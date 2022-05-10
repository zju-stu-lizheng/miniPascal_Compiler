#include <iostream>

using namespace std;

class AST_BaseNode{
    private:
        // location for error information
        int column;
        int row;
    public:
        AST_BaseNode(int _column, int _row):column(_column), row(_row){

        }
        GetColumn(){
            return this->column;
        }
        GetRow(){
            return this->row;
        }
        GetLocation(){
            return std::make_pair(this->column, this->row);
        }
        SetColumn(int _column){
            this->column = _column;
        }
        SetRow(int _row){
            this->row = _row;
        }
        SetLocation(std::pair<int, int> location){
            this->column = location.first;
            this->row = location.second;
        }
        SetLocation(int _column, int _row){
            this->column = _column;
            this->row = _row;
        }
};