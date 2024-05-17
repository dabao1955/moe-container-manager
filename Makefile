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
CC_LOG = @printf '    $(CCCOLOR)CC$(ENDCOLOR) $(BINCOLOR)%b$(ENDCOLOR)\n'
STRIP_LOG = @printf ' $(STRIPCOLOR)STRIP$(ENDCOLOR) $(BINCOLOR)%b$(ENDCOLOR)\n'
O = out
SRCODE = cd src && mkdir build && cd build && cmake .. -DCMAKE_C_COMPILER=`which gcc` -DCMAKE_CXX_COMPILER=`which g++` -GNinja && ninja -j8 && ninja install
.PHONY: all
all: show-greetings $(BIN) $(SHARE) build
show-greetings:
	@echo Starting Build ...
	@printf "\033[1;38;2;254;228;208m"
	@printf "                  _________\n"
	@printf "                 /        /\\ \n"
	@printf "                /        /  \\ \n"
	@printf "               /        /    \\ \n"
	@printf "              /________/      \\ \n"
	@printf "              \\        \\      /\n"
	@printf "               \\        \\    /\n"
	@printf "                \\        \\  /\n"
	@printf "                 \\________\\/\n"
	@sleep 1s
ifeq ("$(wildcard out/)","")
	$(shell mkdir out/)
endif
ifeq ("$(wildcard $(SHARE))","")
	$(shell mkdir out/share)
	$(shell cp src/share $(SHARE) -R)
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
	$(MAKE) -C doc
	echo you can run <cd doc && make preview> to read docs.
endif

BIN = $(O)/bin/

SHARE = $(O)/share/moe-container-manager

build: src/CMakeLists.txt
	@$(SRCODE)
	@cp -r src/out/* out/bin/
	@cp LICENSE out/share/doc/moe-container-manager/
	@tar -xf src/share/proc.tar.xz -C $(SHARE)/proc
install: out/share/doc/moe-container-manager/LICENSE
	@printf "\033[1;38;2;254;228;208m[+] Install.\033[0m\n"&&sleep 1s
	@rm -rf $(SHARE)/proc.tar.xz
	@cp -r $(O)/bin/* /usr/bin/
	@cp -r $(O)/share/doc/* /usr/share/doc/
	@cp -r $(O)/share/moe-container-manager /usr/share/
test:
	@out/bin/interface -v

.PHONY: clean
clean:
	@printf "\033[1;38;2;254;228;208m[+] Clean.\033[0m\n"&&sleep 1s
	@rm -rf $(O)
	@printf "\033[1;38;2;254;228;208m    .^.   .^.\n"
	@printf "    /⋀\\_ﾉ_/⋀\\ \n"
	@printf "   /ﾉｿﾉ\\ﾉｿ丶)|\n"
	@printf "  |ﾙﾘﾘ >   )ﾘ\n"
	@printf "  ﾉノ㇏ Ｖ ﾉ|ﾉ\n"
	@printf "        ⠁⠁\n"
	@printf "\033[1;38;2;254;228;208m[*] Cleaned Up.\033[0m\n"

help:
	@echo "Makefile is not for common user, please use the released .deb files instead."
	@echo "(>_) "

c-format:
	@python3 tools/c-format.py
shell-format:
	@python3 tools/shell-format.py

.PHONY: distclean
distclean:
	@perl tools/clean.pl
