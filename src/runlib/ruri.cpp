#include "runlib.hpp"

int main(int argc, char** argv) {
    runlib::runlib("libruri.so", "main", argc, argv);
    return 0;
}

