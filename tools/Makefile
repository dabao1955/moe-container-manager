ifeq ("$(wildcard src/build)","")
        $(shell mkdir src/build)
endif

all:
	cd src/build && cmake .. -DCMAKE_C_COMPILER=`which gcc` -DCMAKE_CXX_COMPILER=`which g++` --debug-trycompile --log-context --debug-output --debug-find -DCMAKE_CXX_FLAGS="-v" -DCMAKE_C_FLAGS="-v" -GNinja -DDEBUG_MODE=on && ninja -v -j8
install:
	cd src/build && ninja install
