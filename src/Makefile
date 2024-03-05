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
all: ruri.o yoshinon.o nekoasc.o interface.o libk2v.o install-bin install-lib
ruri.o:
	@[ -e ruri/ruri ]||(make -C ruri static)
yoshinon.o:
	@[ -e yoshinon/yoshinon ]||(make -C yoshinon)
nekoasc.o:
	@[ -e nekoasc/nekoasc ]||(make -C nekoasc static-bionic)
libk2v.o:
	@[ -e libk2v/libk2v.so ]||(cd libk2v && cc -fPIC -shared -fstack-protector-all -fstack-clash-protection -mshstk  -D_FORTIFY_SOURCE=3 -Wno-unused-result -O2 -std=gnu99 -Wno-gnu-zero-variadic-macro-arguments -o libk2v.so src/k2v.c -z noexecstack -z now && strip libk2v.so && cc -std=gnu99 -c -o libk2v.o src/k2v.c && ar -r libk2v.a libk2v.o)
k2sh.o:
	@[ -e libk2v/k2sh ]||(make -C libk2v)
interface.o:
	@[ -e interface/build/interface ]||(cd interface && mkdir build && cd build && cmake .. && make)

install-bin:
	@cp rootfstool/rootfstool out
	@mv ruri/ruri out
	@mv yoshinon/yoshinon out
	@mv nekoasc/nekoasc out
	@mv interface/build/interface out
install-lib: libk2v/libk2v.so
	@mv libk2v/libk2v.so ../out/lib/moe-container-manager
	@mv libk2v/libk2v.a ../out/lib/moe-container-manager

.PHONY: clean

clean: out
	@rm -rf out ruri/ruri yoshinon/yoshinon nekoasc/nekoasc interface/build libk2v/libk2v*
