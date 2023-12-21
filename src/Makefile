# SPDX-License-Identifier: Apache-2.0
#
# This file is part of termux-container, with ABSOLUTELY NO WARRANTY.
#
# Copyright (c) 2023 dabao1955
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
#

ifeq ("$(wildcard out)","")
 $(shell mkdir out)
endif

.PHONY: all
all: ruri.o yoshinon.o container-console.o nekoasc.o pkc.o install
ruri.o:
	@[ -e ruri/ruri ]||(make -C ruri static)
yoshinon.o:
	@[ -e yoshinon/yoshinon ]||(make -C yoshinon)
container-console.o:
	@[ -e container-console/container-console ]||(make -C container-console)
nekoasc.o:
	@[ -e nekoasc/nekoasc ]||(make -C nekoasc static-bionic)
pkc.o:
	@cd pkc && rm -rf build && mkdir build && cd build && cmake .. && make
install:
	@cp rootfstool/rootfstool out
	@mv ruri/ruri out
	@mv yoshinon/yoshinon out
	@mv pkc/build/pkc out
	@cp container/container out
	@mv container-console/container-console out
	@mv nekoasc/nekoasc out

gettext:
	@xgettext -o container.pot -L Shell --keyword=po_getmsg --no-wrap container/container
	@msginit -i container.pot -l zh_CN.UTF-8 --no-wrap -o container.po
	@rm container.pot
	@mv container.po ../lang/container-newlang.po

format:
	@shfmt -i 2 -w container/container
	@shfmt -i 2 -w ../share/shell/*

sync:
	@cd nekoasc&&git pull git@github.com:moe-hacker/nekoasc main
	@cd rootfstool&&git pull git@github.com:moe-hacker/rootfstool main
	@cd ruri&&git pull git@github.com:moe-hacker/ruri main
	@cd yoshinon&&git pull git@github.com:moe-hacker/yoshinon main

.PHONY: clean

clean: out
	@rm -rf out ruri/ruri yoshinon/yoshinon container-console/container-console pkc/build
