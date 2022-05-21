#### at Our_Pascal_Compiler/, run run.sh ###

path="../test/"
filename="advisor.pas"
exp_str="< ../test/advisor_input.txt"


rm -rf "$filename.o" "$filename.ll"

## make ##
cd build && cmake ..
make 
## clean ##

## generate .o .ll file ##
./src/opc $path $filename
## generate new executable file ##
rm -rf main
clang++ -o main "$filename.o" 
# debug

echo ""
echo "test file name: $filename"
echo "======================== begin debug ===================="

./main $exp_str

# test quicksort
# ../test/quicksort/linux-amd64 ./build/main
# test 

# test advisor (not ok for bash)
# cd ../test/auto-advisor/
# ./auto-advisor-x86_64-unknown-linux-gnu ../../build/main
# ./test/auto-advisor/auto-advisor-x86_64-unknown-linux-gnu ./build/main
# test 