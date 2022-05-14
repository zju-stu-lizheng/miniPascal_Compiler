#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <llvm/IR/Value.h>

class AST_BaseNode{
    private:
        // location for error information
        int column;
        int row;
    public:
        AST_BaseNode() = default; //default 
        AST_BaseNode(int _column, int _row):column(_column), row(_row){}
        int GetColumn() const{
            return this->column;
        }
        int GetRow() const{
            return this->row;
        }
        std::pair<int,int> GetLocation() const{
            return std::make_pair(this->column, this->row);
        }

        void SetColumn(int _column){
            this->column = _column;
        }
        void SetRow(int _row){
            this->row = _row;
        }
        void SetLocation(std::pair<int, int> location){
            this->column = location.first;
            this->row = location.second;
        }
        void SetLocation(int _column, int _row){
            this->column = _column;
            this->row = _row;
        }

        virtual void LevelOrder(){
            std::cout << "root" << std::endl;
        }

        virtual llvm::Value* CodeGenerate() = 0;
        
};