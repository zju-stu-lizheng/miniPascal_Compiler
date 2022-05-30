#### at miniPascal_Compiler/, run run.sh ###

path="../test/"
filename="for.pas"
# exp_str="< ../test/advisor_input.txt"


rm -rf "$filename.o" "$filename.ll"

## make ##
cd build && cmake ..
make 
## clean ##

## generate .o .ll file ##
./src/opc $path $filename

## generate png from dot file ##
cd "$path"
rm -rf sample.png
dot -Kdot -Tpng "$filename.dot" -o sample.png
cd -
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