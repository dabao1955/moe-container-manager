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
all: ruri.o yoshinon.o interface.o libk2v.o install
ruri.o:
	@[ -e ruri/ruri ]||($(MAKE) -C ruri static)
yoshinon.o:
	@[ -e yoshinon/yoshinon ]||(cd yoshinon && mkdir build && cd build && cmake .. && $(MAKE))
libk2v.o:
	@[ -e libk2v/build/k2sh ]||(cd libk2v && mkdir build && cd build && cmake .. && $(MAKE) && make install)
interface.o:
	@[ -e interface/build/interface ]||(cd interface && mkdir build && cd build && cmake .. && $(MAKE) && make install)

install:
	@cp rootfstool/rootfstool out
	@mv ruri/ruri out

.PHONY: clean
clean: out
	@rm -rf out ruri/ruri yoshinon/build nekoasc/nekoasc nekoasc/out interface/build libk2v/build
