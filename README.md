# miniPascal_Compiler
2022春夏编译原理大程——面向Pascal语言的编译器设计

## 分支名称

* main : 主分支
* visualization : 可视化分支


## 文件结构
* src : 源码文件夹
* test : 测试代码文件夹
* report : 项目报告与可视化AST结果

### 推送指南 (git push)：
* git checkout main : 切换到`main`分支
* git add . 
* git commit -m "first commit to main"
* git push origin main

### 拉取指南 (git fetch)：

* git fetch origin main     

## Time Line
4.23: First commit Lexer.

5.10: Finish Parser.

5.13: Finish AST.

5.20: Finish LLVM.

5.25: Finish visualization.

## Dependencies
* g++
* llvm >= 12.0
* cmake >= 3.10

## Please use cmake to build this project.
Usage
* `./opc test.pas` : Generate IR code and object code from test.pas to test.pas.ll and test.pas.o.
* `lli test.pas.ll`: Generate an executable file from IR code test.pas.ll
* `clang++ -o main test.pas.o` : Generate an executable file(main) from object code test.pas.o

或者直接运行脚本，需要运行的pas文件写入脚本内
* `run.sh`

#### 可视化方法(使用graphviz)
* `sudo apt-get install graphviz` :安装相关依赖

* `dot -Kdot -Tpng test.pas.dot  -o sample.png` :可以将`test.pas.dot`文件生成可视化图片`sample.png`