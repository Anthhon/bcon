#!/bin/bash

SOURCE=../src/main.c
OUTPUT=bcon
FLAGS=-Wall -Werror

build:
	gcc -o $(OUTPUT) $(SOURCE) $(FLAGS)
check:
	clang-tidy -checks=* $(SOURCE)
