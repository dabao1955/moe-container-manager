CCCOLOR     = \033[1;38;2;254;228;208m
STRIPCOLOR  = \033[1;38;2;254;228;208m
BINCOLOR    = \033[34;1m
ENDCOLOR    = \033[0m
CC_LOG = @printf '    $(CCCOLOR)CC$(ENDCOLOR) $(BINCOLOR)%b$(ENDCOLOR)\n'
STRIP_LOG = @printf ' $(STRIPCOLOR)STRIP$(ENDCOLOR) $(BINCOLOR)%b$(ENDCOLOR)\n'
O = out
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
	sleep 4s
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

build: src/Makefile
	@make -C src
	cp -R src/out/* out/bin/
	cp LICENSE out/doc/moe-container-manager/
update-code:
	@git submodule init && git submodule update --remote
install:build
	@printf "\033[1;38;2;254;228;208m[+] Install.\033[0m\n"&&sleep 1s
	@cp -rv $(O)/bin/* /usr/bin/
	@cp -rv $(O)/doc/* /usr/share/doc/
	@cp -rv $(O)/moe-container-manager /usr/share/
DEB=$(O)/deb
$(DEB):build
ifneq ($(shell test -d $(DEB)||echo x),)
	@mkdir -v $(DEB)
	@mkdir -pv $(DEB)/usr
	@mkdir -pv $(DEB)/usr/bin/
	@mkdir -pv $(DEB)/usr/share/
	@mkdir -pv $(DEB)/usr/share/doc
	@cp -v $(O)/bin/* $(DEB)/usr/bin/
	@cp -rv $(O)/moe-container-manager $(DEB)/usr/share/
	@cp -rv $(O)/doc/* $(DEB)/usr/share/doc

endif

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
	python3 tools/c-format.py
shell-format:
	python3 tools/shell-format.py

.PHONY: distclean
distclean:
	rm -rf $(O) 
	make -C src clean
