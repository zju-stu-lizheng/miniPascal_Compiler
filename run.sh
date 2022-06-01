#### at miniPascal_Compiler/, run run.sh ###

path="test/"
## choose the test file ##
fileprefix="matrix"    
filename=$fileprefix".pas"
exp_str="< ../test/advisor_input.txt"

rm -rf "$filename.o" "$filename.ll"

## make ##
cd build && cmake ..
make 
cd ..
## clean ##

## generate .o .ll file ##
./build/src/opc $path $filename

## generate png from dot file ##
echo "generate png"
cd "$path"
if [ -f $fileprefix.png ]; then rm $fileprefix.png; fi
dot -Kdot -Tpng "$filename.dot" -o $fileprefix.png
cd -

## generate new executable file ##
if [ -f $fileprefix ]; then rm $fileprefix; fi
clang++ -o $fileprefix "$filename.o" 

echo ""
echo "test file name: $filename"
echo "======================== begin debug ===================="

./$fileprefix $exp_str

## move file to demo/$fileprefix ##
if [ ! -d demo/$fileprefix/ ];then
   mkdir -p demo/$fileprefix
fi
mv $fileprefix demo/$fileprefix/
mv $path/$fileprefix.png demo/$fileprefix/
mv "$filename.o" demo/$fileprefix/
mv "$filename.ll" demo/$fileprefix/
mv $path/$filename.dot demo/$fileprefix/

# test quicksort
# ../test/quicksort/linux-amd64 ./build/main
# test 

# test advisor (not ok for bash)
# cd ../test/auto-advisor/
# ./auto-advisor-x86_64-unknown-linux-gnu ../../build/main
# ./test/auto-advisor/auto-advisor-x86_64-unknown-linux-gnu ./build/main
# test 