#!/bin/perl -w

if ( -e "test.c" ) {
    print("err");
    1;
}
else {
    system("clang -ggdb -O0 -fno-omit-frame-pointer -z norelro -z execstack -fno-stack-protector -Wall -Wextra -pedantic -Wconversion -Wno-newline-eof -Wl,--gc-sections -o test/testk2v test/test.c build/libk2v.a");
}

if ( -e "test" ) {
    system("cd test && ./testk2v");
}
else {
    system("./testk2v");
}
