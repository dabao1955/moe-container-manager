# Makefile optimized for CodeQL
O = out
BIN = $(O)/bin
SHARE = $(O)/share/moe-container-manager
BUILD_DIR = src/build

# Define flags
CMAKE_FLAGS = -DCMAKE_C_COMPILER=$(shell which gcc) -DCMAKE_CXX_COMPILER=$(shell which g++) -GNinja \

.PHONY: all install setup_dirs

# Rule to create necessary directories
setup_dirs:
	mkdir -p $(O) $(BIN) $(SHARE)/proc $(SHARE)/doc/moe-container-manager $(BUILD_DIR)

all: setup_dirs
	cd $(BUILD_DIR) && cmake .. $(CMAKE_FLAGS) && ninja -v -j8

install:
	cd $(BUILD_DIR) && ninja install

