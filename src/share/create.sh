#!/usr/bin/bash
# Copyright 2024 moe-hacker
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
function pull_rootfs() {
  # It will set the following variable(s):
  # $ROOTFS
  mkdir -p /usr/share/moe-container-manager/rootfs 2>&1 >/dev/null || true
  mirrorlist=$(rootfstool m)
  j=1
  for i in $mirrorlist; do
    arg+="[$j] $i "
    j=$((j + 1))
  done
  num=$(yoshinon --menu --cursorcolor "114;5;14" --title "MAMAGER-$VERSION" "Select a mirror" 12 25 4 $arg)
  num=$(echo $num | cut -d "[" -f 2 | cut -d "]" -f 1)
  distro=$(echo $mirrorlist | cut -d " " -f $num)
  rootfslist=$(rootfstool l -m $MIRROR | awk '{print $2}')
  j=1
  arg=""
  for i in $rootfslist; do
    arg+="[$j] $i "
    j=$((j + 1))
  done
  num=$(yoshinon --menu --cursorcolor "114;5;14" --title "MAMAGER-$VERSION" "Select a distro" 12 25 4 $arg)
  num=$(echo $num | cut -d "[" -f 2 | cut -d "]" -f 1)
  distro=$(echo $rootfslist | cut -d " " -f $num)
  versionlist=$(rootfstool s -d $distro -m $MIRROR | awk '{print $4}')
  j=1
  arg=""
  for i in $versionlist; do
    arg+="[$j] $i "
    j=$((j + 1))
  done
  num=$(yoshinon --menu --cursorcolor "114;5;14" --title "MAMAGER-$VERSION" "Select the version" 12 25 4 $arg)
  num=$(echo $num | cut -d "[" -f 2 | cut -d "]" -f 1)
  version=$(echo $versionlist | cut -d " " -f $num)
  if [[ ! -e /usr/share/moe-container-manager/rootfs/$distro-$version.tar.xz ]]; then
    cd /usr/tmp
    rm rootfs.tar.xz*
    axel -n 16 $(rootfstool u -d $distro -v $version -m $MIRROR)
    mv rootfs.tar.xz /usr/share/moe-container-manager/rootfs/$distro-$version.tar.xz
  fi
  export ROOTFS=/usr/share/moe-container-manager/rootfs/$distro-$version.tar.xz
}
pv $ROOTFS | tar -xJf - -C ${CONTAINER_DIR}
