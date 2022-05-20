# Our_Pascal_Compiler
2022春夏编译原理大程——面向Pascal语言的编译器设计

## Branch info

main: 开始llvm

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

## Dependencies
g++
llvm >= 12.0
cmake >= 3.10

## llvm test
在Our_Pascal_Compiler目录下
```
mkdir build
cd build
cmake ..
make
.src/opc < ../test/test.pas
.src/opc < ../test/test.pas
```

## Please use cmake to build this project.
Usage
<<<<<<< HEAD
* ./opc : Generate IR code and object code from test.pas to test.pas.ll and test.pas.o.
* lli test.pas.ll: Generate an executable file from IR code test.pas.ll
* clang++ -o main test.pas.o : Generate an executable file(main) from object code test.pas.o

=======
* `./opc test.pas` : Generate IR code and object code from test.pas to test.pas.ll and test.pas.o.
* `lli test.pas.ll`: Generate an executable file from IR code test.pas.ll
* `clang++ -o main test.pas.o` : Generate an executable file(main) from object code test.pas.o
>>>>>>> 36f2e218d8715323379dc66c840a8d9bcab30bdb
