#!/bin/bash

echo '开始编译'

/usr/bin/c++ -fdiagnostics-color=always -c enter.c -o ./enter.o -I ./include
/usr/bin/c++ -fdiagnostics-color=always enter.o main.c -o ../out/config_file.app -I ./include

echo '编译完毕'

rm -rf ./enter.o
