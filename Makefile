CCCOLOR     = \033[1;38;2;254;228;208m
STRIPCOLOR  = \033[1;38;2;254;228;208m
BINCOLOR    = \033[34;1m
ENDCOLOR    = \033[0m
CC_LOG = @printf '    $(CCCOLOR)CC$(ENDCOLOR) $(BINCOLOR)%b$(ENDCOLOR)\n'
STRIP_LOG = @printf ' $(STRIPCOLOR)STRIP$(ENDCOLOR) $(BINCOLOR)%b$(ENDCOLOR)\n'
O = out
.PHONY: all
all: show-greetings build
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
$(O):
ifneq ($(shell test -d $(O)||echo x),)
	@mkdir -v $(O)
endif
DOC = $(O)/doc
$(DOC):$(O)
ifneq ($(shell test -d $(DOC)||echo x),)
	@mkdir -pv $(DOC)/moe-container-manager
	@cp -rv doc/* $(O)/doc/moe-container-manager/
endif
SHARE = $(O)/moe-container-manager
$(SHARE):$(O)
ifneq ($(shell test -d $(SHARE)||echo x),)
	@cp -rv share $(O)/moe-container-manager
endif
BIN = $(O)/bin
$(BIN):$(O)
ifneq ($(shell test -d $(BIN)||echo x),)
	@mkdir -v $(BIN)
endif
CONTAINER = $(O)/bin/container
$(CONTAINER):$(BIN)
ifneq ($(shell test -f $(CONTAINER)||echo x),)
	@cp -v src/container $(O)/bin/container
endif
CONTAINER_CONSOLE = $(O)/bin/container-console
$(CONTAINER_CONSOLE):$(BIN)
ifneq ($(shell test -f $(CONTAINER_CONSOLE)||echo x),)
	@printf "\033[1;38;2;254;228;208m[+] Compile container-console.\033[0m\n"&&sleep 1s
	@cd src/container-console && clang -static -ffunction-sections -fdata-sections -Wl,--gc-sections -O3 -z noexecstack -z now -fstack-protector-all -fPIE -flto container-console.c -o container-console&&strip container-console && clang -static  pkc.c -o pkc
	@mv -v src/container-console/container-console $(O)/bin/container-console
	@mv -v src/container-console/pkc $(O)/bin/pkc
endif
src/ruri/ruri.c:
	@printf "\033[1;38;2;254;228;208m[+] Update source code.\033[0m\n"&&sleep 1s
	@printf "\033[1;38;2;254;228;208m[+] Update submodule.\033[0m\n"&&sleep 1s
	@git submodule update --init
RURI = $(O)/bin/ruri
$(RURI):src/ruri/ruri.c $(BIN)
ifneq ($(shell test -f $(RURI)||echo x),)
	@printf "\033[1;38;2;254;228;208m[+] Compile ruri.\033[0m\n"&&sleep 1s
	@cd src/ruri&&make static
	@mv -v src/ruri/ruri $(O)/bin/ruri
endif
build:$(DOC) $(SHARE) $(CONTAINER) $(CONTAINER_CONSOLE) $(RURI)
update-code:src/ruri/ruri.c
install:build
	@printf "\033[1;38;2;254;228;208m[+] Install.\033[0m\n"&&sleep 1s
	@cp -rv $(O)/bin /usr/share/moe-container/
	@cp -rv $(O)/moe-container-manager /usr/share/
	@cp -rv $(O)/doc/* /usr/share/doc
	@test -f /usr/bin/container-console || ln -sf /usr/share/moe-container-manager/bin/container-console /usr/bin/containe>
	@test -f /usr/bin/pkc || ln -sf /usr/share/moe-container-manager/bin/pkc /usr/bin/pkc
	@test -f /usr/bin/container || ln -sf /usr/share/moe-container-manager/bin/container /usr/bin/container
	@test -f /usr/bin/ruri || ln -sf /usr/share/moe-container-manager/bin/ruri /usr/bin/ruri
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
help :
	@echo "Makefile is not for common user, please use the released .deb files instead."
	@echo "(>_) Moe-hacker"
