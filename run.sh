#### at Our_Pascal_Compiler/, run run.sh ###

path="../test/"
filename="record.pas"

## make ##
cd build && cmake ..
make 
## generate .o .ll file ##
src/opc $path $filename
## generate executable file ##
clang++ -o main "$path$filename.o" 
# debug

echo ""
echo "test file name: $filename"
echo "======================== begin debug ===================="

./main filename

# test quicksort
# /test/quicksort/linux-amd64 ./build/main
# test 