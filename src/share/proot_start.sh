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

# These values will be automatically set.
# If you don't know what you are doing,
# do not edit them.
CONTAINER_DIR=[CONTAINER_DIR]
MOUNT_SDCARD=[MOUNT_SDCARD]
CROSS_ARCH=[CROSS_ARCH]

export PREFIX=/usr

# A simple proot script.
unset LD_PRELOAD
COMMAND="proot"
COMMAND+=" --link2symlink"
COMMAND+=" --kill-on-exit"
COMMAND+=" --sysvipc"
COMMAND+=" -0"
COMMAND+=" -r ${CONTAINER_DIR}"
COMMAND+=" -b /dev"
COMMAND+=" -b /sys"
COMMAND+=" -b /proc"
COMMAND+=" -w /root"
if [[ ${CROSS_ARCH} != "null" ]]; then
  COMMAND+=" -q qemu-${CROSS_ARCH}"
fi
# Files extracted from Redmi 10X 5G, I hope it works.
COMMAND+=" --mount=$PREFIX/share/moe-container-manager/proc/buddyinfo:/proc/buddyinfo"
COMMAND+=" --mount=$PREFIX/share/moe-container-manager/proc/cgroups:/proc/cgroups"
COMMAND+=" --mount=$PREFIX/share/moe-container-manager/proc/consoles:/proc/consoles"
COMMAND+=" --mount=$PREFIX/share/moe-container-manager/proc/crypto:/proc/crypto"
COMMAND+=" --mount=$PREFIX/share/moe-container-manager/proc/devices:/proc/devices"
COMMAND+=" --mount=$PREFIX/share/moe-container-manager/proc/diskstats:/proc/diskstats"
COMMAND+=" --mount=$PREFIX/share/moe-container-manager/proc/execdomains:/proc/execdomains"
COMMAND+=" --mount=$PREFIX/share/moe-container-manager/proc/fb:/proc/fb"
COMMAND+=" --mount=$PREFIX/share/moe-container-manager/proc/filesystems:/proc/filesystems"
COMMAND+=" --mount=$PREFIX/share/moe-container-manager/proc/interrupts:/proc/interrupts"
COMMAND+=" --mount=$PREFIX/share/moe-container-manager/proc/iomem:/proc/iomem"
COMMAND+=" --mount=$PREFIX/share/moe-container-manager/proc/ioports:/proc/ioports"
COMMAND+=" --mount=$PREFIX/share/moe-container-manager/proc/kallsyms:/proc/kallsyms"
COMMAND+=" --mount=$PREFIX/share/moe-container-manager/proc/key-users:/proc/key-users"
COMMAND+=" --mount=$PREFIX/share/moe-container-manager/proc/keys:/proc/keys"
COMMAND+=" --mount=$PREFIX/share/moe-container-manager/proc/kpageflags:/proc/kpageflags"
COMMAND+=" --mount=$PREFIX/share/moe-container-manager/proc/loadavg:/proc/loadavg"
COMMAND+=" --mount=$PREFIX/share/moe-container-manager/proc/locks:/proc/locks"
COMMAND+=" --mount=$PREFIX/share/moe-container-manager/proc/misc:/proc/misc"
COMMAND+=" --mount=$PREFIX/share/moe-container-manager/proc/modules:/proc/modules"
COMMAND+=" --mount=$PREFIX/share/moe-container-manager/proc/pagetypeinfo:/proc/pagetypeinfo"
COMMAND+=" --mount=$PREFIX/share/moe-container-manager/proc/partitions:/proc/partitions"
COMMAND+=" --mount=$PREFIX/share/moe-container-manager/proc/sched_debug:/proc/sched_debug"
COMMAND+=" --mount=$PREFIX/share/moe-container-manager/proc/softirqs:/proc/softirqs"
COMMAND+=" --mount=$PREFIX/share/moe-container-manager/proc/stat:/proc/stat"
COMMAND+=" --mount=$PREFIX/share/moe-container-manager/proc/timer_list:/proc/timer_list"
COMMAND+=" --mount=$PREFIX/share/moe-container-manager/proc/uptime:/proc/uptime"
COMMAND+=" --mount=$PREFIX/share/moe-container-manager/proc/version:/proc/version"
COMMAND+=" --mount=$PREFIX/share/moe-container-manager/proc/vmallocinfo:/proc/vmallocinfo"
COMMAND+=" --mount=$PREFIX/share/moe-container-manager/proc/vmstat:/proc/vmstat"
COMMAND+=" --mount=$PREFIX/share/moe-container-manager/proc/zoneinfo:/proc/zoneinfo"
# Mount termux's tmpdir.
COMMAND+=" --mount=$PREFIX/tmp:/tmp"
if [[ ! $1 ]]; then
  COMMAND+=" /bin/su - root"
else
  COMMAND+=" $@"
fi
# Yes, this can exec the command.
${COMMAND}
