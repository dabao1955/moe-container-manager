# SPDX-License-Identifier: Apache-2.0
# This file is part of moe-container-manager.
#
# Copyright (c) 2024 dabao1955
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# Colors and Formatting
COLOR     = \033[1;38;2;254;228;208m
BINCOLOR  = \033[34;1m
ENDCOLOR  = \033[0m

# Directory Paths
O          = out
BIN        = $(O)/bin
SHARE      = $(O)/share/moe-container-manager
PREFIX     = /usr/local
DESTDIR    = $(PREFIX)

# Build Configurations
CORES      = $(shell nproc)  # Auto-detect number of cores
CC = $(shell which gcc)
CXX = $(shell which g++)
VERBOSE ?= 0
LIB ?= 0
Q           = $(if $(filter 1,$(VERBOSE)),, @)
N           = $(if $(filter 1,$(VERBOSE)),-v,)
D           = $(if $(filter 1,$(VERBOSE)),on,)
L           = $(if $(filter 1,$(LIB)),on,off)

LINK        = $(if $(filter 1,$(LIB)), \
              mv out/bin/ruri-runlib out/bin/ruri && mv out/bin/interface-runlib out/bin/interface, \
              echo "LINK is disabled")


# CMake and Ninja Build Flags
CMAKE_FLAGS = -DCMAKE_C_COMPILER=$(CC) -DCMAKE_CXX_COMPILER=$(CXX) -DCMAKE_C_FLAGS="-pipe" -GNinja
NINJA_FLAGS = -j$(CORES) $(N)

# Directory Creation Function
define make-dirs
	$(shell mkdir -p $1)
endef

# Main Build Command
BUILD = cd src/out && cmake .. $(CMAKE_FLAGS) -DDEBUG_MODE=$(D) -DMOE_LIB=$(L) && ninja $(NINJA_FLAGS) && ninja install

# Install Directories
INSTALL_BIN_DIR = $(DESTDIR)/bin
INSTALL_SHARE_DIR = $(DESTDIR)/share/moe-container-manager
INSTALL_DOC_DIR = $(INSTALL_SHARE_DIR)/../doc/moe-container-manager

# Default Target
.PHONY: all show-greetings clean distclean help install build update-ruri c-format shell-format
all: show-greetings $(BIN) $(SHARE) build

install: out
	$(Q)$(LINK)
	$(Q)printf "$(COLOR)[+] Install.\n"
	$(Q)install -d $(INSTALL_BIN_DIR) $(INSTALL_SHARE_DIR) $(INSTALL_DOC_DIR)
	$(Q)install -m 755 $(O)/bin/* $(INSTALL_BIN_DIR)
	$(Q)cp -r $(O)/share/* $(INSTALL_SHARE_DIR)
	$(Q)(if [ -d "$(O)/lib" ]; then \
		install -d $(DESTDIR)/lib; \
		cp $(O)/lib/* $(DESTDIR)/lib/; \
		ldconfig; \
	fi)

.PHONY: clean distclean

clean:
	$(Q)printf "$(COLOR)[+] Clean.\n"
	$(Q)rm -rf $(O) src/out src/ruri/src/include/version.h
	$(Q)printf "$(COLOR)    .^.   .^.\n"
	$(Q)printf "    /⋀\\_ﾉ_/⋀\\ \n"
	$(Q)printf "   /ﾉｿﾉ\\ﾉｿ丶)|\n"
	$(Q)printf "  |ﾙﾘﾘ >   )ﾘ\n"
	$(Q)printf "  ﾉノ㇏ Ｖ ﾉ|ﾉ\n"
	$(Q)printf "        ⠁⠁$(ENDCOLOR)\n"
	$(Q)printf "$(COLOR)[*] Cleaned Up.\n"

distclean:
	$(Q)printf "$(COLOR)[+] Distclean.\n"
	$(Q)perl tools/clean.pl

show-greetings:
	$(Q)printf "$(CCCOLOR)"
	$(Q)echo Starting Build ...
	$(Q)printf "                  _________\n"
	$(Q)printf "                 /        /\\ \n"
	$(Q)printf "                /        /  \\ \n"
	$(Q)printf "               /        /    \\ \n"
	$(Q)printf "              /________/      \\ \n"
	$(Q)printf "              \\        \\      /\n"
	$(Q)printf "               \\        \\    /\n"
	$(Q)printf "                \\        \\  /\n"
	$(Q)printf "                 \\________\\/\n"

# Directory Creation
$(call make-dirs, src/out out/share/doc/moe-container-manager out/share/moe-container-manager/proc out/bin out/share out/share/moe-container-manager)

# Build Rules
build: src/CMakeLists.txt
	$(Q)$(BUILD)

# Documentation Build
DOC = doc
$(DOC): /usr/bin/w3m
	ifneq ($(shell test -d $(DOC)||echo x),)
		$(Q)$(MAKE) -C doc
		$(Q)echo "To read docs, run <cd doc && make preview>."
	endif

# Run Tests
test:
	$(Q)out/bin/interface -v

# Help
help:
	@echo "Makefile is for advanced usage only. Use the released .deb files instead."
	@echo "Targets:"
	@echo "  all       - Build everything"
	@echo "  install   - Install the binaries and documentation"
	@echo "  clean     - Clean up the build artifacts"
	@echo "  distclean - Perform a deep clean, removing all build directories"
	@echo "  update-ruri - Update the ruri source from the remote repository"
	@echo "  test      - Run tests on the built binaries"
	@echo
	@echo "(>_) "

update-ruri:
	$(Q)mkdir -p src/tmp
	$(Q)mv src/ruri/CMakeLists.txt src/ruri/config.h.in src/ruri/debian/rules src/tmp
	$(Q)rm -rf src/ruri
	$(Q)git clone https://github.com/Moe-Hacker/ruri src/ruri
	$(Q)rm -rf src/ruri/LICENSE src/ruri/.git src/ruri/.github src/ruri/.clang-format src/ruri/.clang-format src/ruri/Makefile src/ruri/configure src/ruri/src/include/version.h
	$(Q)mv src/tmp/* src/ruri/
	$(Q)mv src/ruri/rules src/ruri/debian
	$(Q)mv src/ruri/src/main.c src/ruri/src/ruri.c
	$(Q)rm -rf src/tmp
