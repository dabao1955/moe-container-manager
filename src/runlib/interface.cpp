#include "runlib.hpp"

int main(int argc, char* argv[]) {
    runlib::runlib("libinterface.so", "main", argc, argv);
    return 0;
}

