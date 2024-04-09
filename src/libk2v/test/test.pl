#!/bin/perl

system("clang -ggdb -O0 -fno-omit-frame-pointer -z norelro -z execstack -fno-stack-protector -Wall -Wextra -pedantic -Wconversion -Wno-newline-eof -Wl,--gc-sections -o testk2v test/test.c build/libk2v.a");
system("./testk2v");
