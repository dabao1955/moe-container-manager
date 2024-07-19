#Warning: this Makefile only used on CodeQL
O = out
BIN = $(O)/bin/
SHARE = $(O)/share/moe-container-manager/

ifeq ("$(wildcard out/)","")
        $(shell mkdir out/)
endif
ifeq ("$(wildcard $(SHARE))","")
        $(shell mkdir out/share)
        $(shell mkdir $(SHARE))
        $(shell mkdir $(SHARE)/proc)
endif
ifeq ("$(wildcard $(SHARE)/doc)","")
        $(shell mkdir out/share/doc)
        $(shell mkdir out/share/doc/moe-container-manager)
endif
ifeq ("$(wildcard $(BIN))","")
        $(shell mkdir $(BIN))
endif

ifeq ("$(wildcard src/build)","")
        $(shell mkdir src/build)
endif

all:
	cd src/build && cmake .. -DCMAKE_C_COMPILER=`which gcc` -DCMAKE_CXX_COMPILER=`which g++` --debug-trycompile --log-context --debug-output --debug-find -DCMAKE_CXX_FLAGS="-v" -DCMAKE_C_FLAGS="-v" -GNinja -DDEBUG_MODE=on && ninja -v -j8
install:
	cd src/build && ninja install
