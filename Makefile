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
SRCODE = make -C src 
.PHONY: all
all: show-greetings update-code $(BIN) $(SHARE) build
show-greetings:
	echo Starting Build ...
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

DOC = doc
$(DOC): /usr/bin/w3m
ifneq ($(shell test -d $(DOC)||echo x),)
	make -C doc
	echo you can run <cd doc && make preview> to read docs.
endif

	
BIN = $(O)/bin/

SHARE = $(O)/moe-container-manager
$(SHARE):$(O)

ifeq ("$(wildcard out/moe-container-manager)","")
$(shell cp share out/moe-container-manager -R)
endif

$(BIN):$(O)

ifeq ("$(wildcard out/bin)","")
$(shell mkdir out/bin)
endif
ifeq ("$(wildcard out/doc)","")
$(shell mkdir out/doc out/doc/moe-container-manager)
endif

sync: 
	@$(SRCODE) sync

build: src/Makefile
	@$(SRCODE) 
	@cp -R src/out/* out/bin/
	@cp LICENSE out/doc/moe-container-manager/
update-code:
	@git submodule init && git submodule update --remote
	@sleep 1s
install: out/doc/moe-container-manager/LICENSE
	@printf "\033[1;38;2;254;228;208m[+] Install.\033[0m\n"&&sleep 1s
	@cp -rv $(O)/bin/* /usr/bin/
	@cp -rv $(O)/doc/* /usr/share/doc/
	@cp -rv $(O)/moe-container-manager /usr/share/
.PHONY: clean
clean:
	@printf "\033[1;38;2;254;228;208m[+] Clean.\033[0m\n"&&sleep 1s
	@rm -rfv $(O)
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
	@rm -rf $(O) 
	@$(SRCODE) clean
