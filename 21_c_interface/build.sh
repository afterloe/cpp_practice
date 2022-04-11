#!/bin/bash

clang -c game.c -I game_impl.h -o game_impl.a
clang game_impl.a main.c -I game_impl.h -I game.h -o game.app
rm -rf game_impl.a
mv game.app ../out