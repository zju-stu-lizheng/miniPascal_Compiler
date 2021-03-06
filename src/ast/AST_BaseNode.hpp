#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <string>
#include "../type/type.hpp"
#include "../visualization/graph_visual.hpp"
#include <llvm/IR/Value.h>

//增加一个PrintNode方法
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
        std::string GetLocationString() const{
            return "(" + std::to_string(this->row) + "," + std::to_string(this->column) + ")";
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

        virtual void PrintNode(GraphViz *) = 0;

        virtual std::shared_ptr<Custom_Result> CodeGenerate() = 0;
};