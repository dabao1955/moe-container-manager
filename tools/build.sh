#!/bin/bash
#warning: this shell sctipt only used in codeql.

cd src/
mkdir o
cd o
cmake .. -DCMAKE_C_COMPILER=`which gcc` -DCMAKE_CXX_COMPILER=`which g++` --debug-trycompile --log-context --debug-output --debug-find -DCMAKE_CXX_FLAGS="-v" -DCMAKE_C_FLAGS="-v" -GNinja
ninja -j8
ninja install
