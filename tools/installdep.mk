#!/usr/bin/make -f

ifeq ("$(wildcard /usr/bin/sudo)","")
SUDO = $(sudo)
endif

ifneq ($(shell dpkg -l libspdlog-dev ||echo x),)
DEP = apt install -y debhelper build-essential clang dpkg-dev libcap-dev pkg-config git libseccomp-dev golang lld cmake libpthreadpool0 libpthreadpool-dev shfmt perl libspdlog-dev
endif

.PHONY: all
all:
	@$(SUDO) $(DEP)
