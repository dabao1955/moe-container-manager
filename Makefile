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


CCCOLOR     = \033[1;38;2;254;228;208m
STRIPCOLOR  = \033[1;38;2;254;228;208m
BINCOLOR    = \033[34;1m
ENDCOLOR    = \033[0m

BIN = $(O)/bin/
SHARE = $(O)/share/moe-container-manager/
O = out

ifeq ("$(origin VERBOSE)", "command line")
  BUILD_VERBOSE = $(VERBOSE)
endif
ifndef BUILD_VERBOSE
  BUILD_VERBOSE = 0
endif

ifeq ($(BUILD_VERBOSE),1)
  Q =
  SRCODE = cd src && \
	mkdir build && \
	cd build && \
	cmake .. -DCMAKE_C_COMPILER=`which gcc` -DCMAKE_CXX_COMPILER=`which g++` -GNinja && \
	ninja -v -j8 && \
	ninja -v install
else
  Q = @
  SRCODE = cd src && \
	mkdir build && \
	cd build && \
	cmake .. -DCMAKE_C_COMPILER=`which gcc` -DCMAKE_CXX_COMPILER=`which g++` -GNinja && \
	ninja -j8 && \
	ninja install
endif

.PHONY: all
all: show-greetings $(BIN) $(SHARE) build
show-greetings:
	$(Q)echo Starting Build ...
	$(Q)printf "\033[1;38;2;254;228;208m"
	$(Q)printf "                  _________\n"
	$(Q)printf "                 /        /\\ \n"
	$(Q)printf "                /        /  \\ \n"
	$(Q)printf "               /        /    \\ \n"
	$(Q)printf "              /________/      \\ \n"
	$(Q)printf "              \\        \\      /\n"
	$(Q)printf "               \\        \\    /\n"
	$(Q)printf "                \\        \\  /\n"
	$(Q)printf "                 \\________\\/\n"

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

DOC = doc
$(DOC): /usr/bin/w3m
ifneq ($(shell test -d $(DOC)||echo x),)
	$(Q)$(MAKE) -C doc
	$(Q)echo you can run <cd doc && make preview> to read docs.
endif

build: src/CMakeLists.txt
	$(Q)$(SRCODE)

install: out/share/doc/moe-container-manager/LICENSE
	$(Q)printf "\033[1;38;2;254;228;208m[+] Install.\033[0m\n"&&sleep 1s
	$(Q)cp -r $(O)/bin/* /usr/bin/
	$(Q)cp -r $(O)/share/doc/* /usr/share/doc/
	$(Q)cp -r $(O)/share/moe-container-manager /usr/share/
test:
	$(Q)out/bin/interface -v

.PHONY: clean
clean:
	$(Q)printf "\033[1;38;2;254;228;208m[+] Clean.\033[0m\n"&&sleep 1s
	$(Q)rm -rf $(O)
	$(Q)printf "\033[1;38;2;254;228;208m    .^.   .^.\n"
	$(Q)printf "    /⋀\\_ﾉ_/⋀\\ \n"
	$(Q)printf "   /ﾉｿﾉ\\ﾉｿ丶)|\n"
	$(Q)printf "  |ﾙﾘﾘ >   )ﾘ\n"
	$(Q)printf "  ﾉノ㇏ Ｖ ﾉ|ﾉ\n"
	$(Q)printf "        ⠁⠁\n"
	$(Q)printf "\033[1;38;2;254;228;208m[*] Cleaned Up.\033[0m\n"

help:
	$(Q)echo "Makefile is not for common user, please use the released .deb files instead."
	$(Q)echo "(>_) "
update-ruri: src/ruri
	$(Q)mkdir -p src/tmp
	$(Q)mv src/ruri/CMakeLists.txt src/ruri/ruri.cmake src/ruri/config.h.in src/tmp
	$(Q)rm -rf src/ruri
	$(Q)git clone https://github.com/Moe-Hacker/ruri src/ruri
	$(Q)rm -rf src/ruri/LICENSE src/ruri/.git src/ruri/.github src/ruri/.clang-format src/ruri/.clang-format src/ruri/Makefile src/ruri/configure src/ruri/src/include/version.h
	$(Q)mv src/tmp/* src/ruri/
	$(Q)rm -rf src/tmp

c-format:
	$(Q)python3 tools/c-format.py
shell-format:
	$(Q)python3 tools/shell-format.py

.PHONY: distclean
distclean:
	$(Q)perl tools/clean.pl
