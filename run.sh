OUTPUT=./build/main

mkdir -p build
if [ -f $OUTPUT ] ; then
    rm $OUTPUT 
fi

clang++ src/main.cpp src/utils.cpp -o $OUTPUT && $OUTPUT $1 $2
