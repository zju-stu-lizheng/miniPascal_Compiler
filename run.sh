#### at Our_Pascal_Compiler/, run run.sh ###

path="./"
filename="test.pas"

## make ##
cd build
cmake ..
make 
cd ..
## generate .o .ll file ##
echo "$path$filename" 
build/src/opc "$path" "$filename"
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