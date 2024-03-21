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

# You need to set the following variable(s)
# before running this script:
#
# $CONTAINER_DIR
# $EXTRA_ARGS

# A simple proot script.
function run_proot_container() {
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
  # Files extracted from Redmi 10X 5G, I hope it works.
  COMMAND+=" --mount=/usr/share/moe-container/proc/buddyinfo:/proc/buddyinfo"
  COMMAND+=" --mount=/usr/share/moe-container/proc/cgroups:/proc/cgroups"
  COMMAND+=" --mount=/usr/share/moe-container/proc/consoles:/proc/consoles"
  COMMAND+=" --mount=/usr/share/moe-container/proc/crypto:/proc/crypto"
  COMMAND+=" --mount=/usr/share/moe-container/proc/devices:/proc/devices"
  COMMAND+=" --mount=/usr/share/moe-container/proc/diskstats:/proc/diskstats"
  COMMAND+=" --mount=/usr/share/moe-container/proc/execdomains:/proc/execdomains"
  COMMAND+=" --mount=/usr/share/moe-container/proc/fb:/proc/fb"
  COMMAND+=" --mount=/usr/share/moe-container/proc/filesystems:/proc/filesystems"
  COMMAND+=" --mount=/usr/share/moe-container/proc/interrupts:/proc/interrupts"
  COMMAND+=" --mount=/usr/share/moe-container/proc/iomem:/proc/iomem"
  COMMAND+=" --mount=/usr/share/moe-container/proc/ioports:/proc/ioports"
  COMMAND+=" --mount=/usr/share/moe-container/proc/kallsyms:/proc/kallsyms"
  COMMAND+=" --mount=/usr/share/moe-container/proc/key-users:/proc/key-users"
  COMMAND+=" --mount=/usr/share/moe-container/proc/keys:/proc/keys"
  COMMAND+=" --mount=/usr/share/moe-container/proc/kpageflags:/proc/kpageflags"
  COMMAND+=" --mount=/usr/share/moe-container/proc/loadavg:/proc/loadavg"
  COMMAND+=" --mount=/usr/share/moe-container/proc/locks:/proc/locks"
  COMMAND+=" --mount=/usr/share/moe-container/proc/misc:/proc/misc"
  COMMAND+=" --mount=/usr/share/moe-container/proc/modules:/proc/modules"
  COMMAND+=" --mount=/usr/share/moe-container/proc/pagetypeinfo:/proc/pagetypeinfo"
  COMMAND+=" --mount=/usr/share/moe-container/proc/partitions:/proc/partitions"
  COMMAND+=" --mount=/usr/share/moe-container/proc/sched_debug:/proc/sched_debug"
  COMMAND+=" --mount=/usr/share/moe-container/proc/softirqs:/proc/softirqs"
  COMMAND+=" --mount=/usr/share/moe-container/proc/stat:/proc/stat"
  COMMAND+=" --mount=/usr/share/moe-container/proc/timer_list:/proc/timer_list"
  COMMAND+=" --mount=/usr/share/moe-container/proc/uptime:/proc/uptime"
  COMMAND+=" --mount=/usr/share/moe-container/proc/version:/proc/version"
  COMMAND+=" --mount=/usr/share/moe-container/proc/vmallocinfo:/proc/vmallocinfo"
  COMMAND+=" --mount=/usr/share/moe-container/proc/vmstat:/proc/vmstat"
  COMMAND+=" --mount=/usr/share/moe-container/proc/zoneinfo:/proc/zoneinfo"
  # Mount termux's tmpdir.
  COMMAND+=" --mount=$PREFIX/tmp:/tmp"
  # Mount container_dir.
  COMMAND+=" --mount=${CONTAINER_DIR}:/"
  # Extra args.
  COMMAND+=" ${EXTRA_ARGS}"
  if [[ ! $1 ]]; then
    COMMAND+=" /bin/su - root"
  else
    COMMAND+=" $@"
  fi
  # Yes, this can exec the command.
  ${COMMAND}
}
function main() {
  while [[ $1 ]]; do
    case $1 in
    "--root-dir" | "-r")
      shift
      export CONTAINER_DIR="$1"
      shift
      continue
      ;;
    "--extra-args" | "-e")
      shift
      export EXTRA_ARGS="$1"
      shift
      continue
      ;;
    *)
      if [[ ${CONTAINER_DIR} ]]; then
        run_proot_container $@
        exit 0
      else
        echo -e "\033[31mUnknow option $1, usage:"
        echo -e "proot_start.sh <-r [container_dir]> [-e \"extra args\"] [COMMAND...ARGS...]\033[0m"
        exit 1
      fi
      ;;
    esac
    shift
  done

  if [[ ${CONTAINER_DIR} ]]; then
    run_proot_container
  else
    echo -e "\033[31mcontainer_dir is not set!\033[0m"
  fi
}
# The `main` function.
main $@
