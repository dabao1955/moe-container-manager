#include "runlib.hpp"

int main(int argc, char* argv[]) {
    runlib::runlib("../lib/libinterface.so", "main", argc, argv);
    return 0;
}

