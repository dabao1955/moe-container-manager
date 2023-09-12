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


all:
	[ -e ruri/ruri ]||(cd ruri&&make static)
	[ -e yoshinon/yoshinon ]||(cd yoshinon&&make)
	[ -e container-console/container-console ]||(cd container-console&&make)
	[ -e pkc/pkc ]||(cd pkc&&gcc -c pkc.c -o pkc)
	sed -i "s/TERMUX_CONTAINER_COMMIT_ID=\"\"/TERMUX_CONTAINER_COMMIT_ID=\"`git log --oneline|head -1|cut -d " " -f 1`\"/" container
	cp rootfstool/rootfstool out
	cp ruri/ruri out
	cp yoshinon/yoshinon out
	cp pkc/pkc out
format:
	shfmt -i 2 -w container
gettext:
	xgettext -o container.pot -L Shell --keyword=po_getmsg --no-wrap container
	msginit -i container.pot -l zh_CN.UTF-8 --no-wrap -o container.po
	rm container.pot
	mv container.po ../lang/container-newlang.po
.PHONY: clean

clean: out
	rm -rf out