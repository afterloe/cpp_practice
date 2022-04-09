#!/bin/bash

echo '开始编译'

/usr/bin/c++ -fdiagnostics-color=always -c enter.c -o ./enter.o -I ./include
/usr/bin/c++ -fdiagnostics-color=always -g enter.o main.c -o ./config_file.app -I ./include
rm -rf ./enter.o
mv ./config_file.app ../out
../out/config_file.app ./conifg.txt
