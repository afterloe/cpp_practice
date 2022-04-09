#!/bin/bash

/usr/bin/c++ -fdiagnostics-color=always -c enter.c -o ./enter.o -I ./include
/usr/bin/c++ -fdiagnostics-color=always -c code.c -o ./code.o -I ./include
/usr/bin/c++ -fdiagnostics-color=always code.o enter.o main.c -o ../out/config_file.app -I ./include

echo '编译完毕'

rm -rf ./enter.o ./code.o
