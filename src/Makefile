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
all: ruri yoshinin container-console pkc container install
ruri.o:
	@[ -e ruri/ruri ]||(make -C ruri static)
yoshinon.o:
	@[ -e yoshinon/yoshinon ]||(make -C yoshinon)
container-console.o:
	@[ -e container-console/build/container-console ]||(cd container-console&&make)
pkc.o:
	@[ -e pkc/build/pkc ]||(cd pkc&&mkdir build&&cd build&&cmake ..&&make)
container.o:
	@sed -i "s/MOE_CONTAINER_MANAGER_COMMIT_ID=\"\"/TERMUX_CONTAINER_COMMIT_ID=\"`git log --oneline|head -1|cut -d " " -f 1`\"/" container/container
install:
	@cp rootfstool/rootfstool out
	@mv ruri/ruri out
	@mv yoshinon/yoshinon out
	@mv pkc/build/pkc out
	@cp container/container out
	@cp container-console/container-console out

gettext:
	xgettext -o container.pot -L Shell --keyword=po_getmsg --no-wrap container/container
	msginit -i container.pot -l zh_CN.UTF-8 --no-wrap -o container.po
	rm container.pot
	mv container.po ../lang/container-newlang.po

.PHONY: clean

clean: out
	rm -rf out ruri/ruri yoshinon/yoshinon container-console/build pkc/build
