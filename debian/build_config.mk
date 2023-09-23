#!/usr/bin/make -f

export CC = /bin/clang
export LD = /bin/ld.lld
export DH_VERBOSE = 1

CC_BIN = $(test -f /usr/bin/clang)
  
DEB_BUILD_ARCH ?= $(shell dpkg-architecture -qDEB_BUILD_ARCH)
DEB_HOST_MULTIARCH ?= $(shell dpkg-architecture -qDEB_HOST_MULTIARCH)

all:
indef CC_BIN
	@echo
else
	echo  Clang not Found ! && exit 127
endif
