# Copyright 2023 moe-hacker
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

# From Tmoe.
# In fact I don't think that there are any phones with amd64 CPUS and Android system now.
function get_cpu_arch() {
  # Usage:
  # get_cpu_arch
  # It will create a global variable ${CPU_ARCH}
  DPKG_ARCH=$(dpkg --print-architecture)
  case ${DPKG_ARCH} in
  armel) export CPU_ARCH="armel" ;;
  armv7* | armv8l | armhf | arm) export CPU_ARCH="armhf" ;;
  aarch64 | arm64* | armv8* | arm*) export CPU_ARCH="arm64" ;;
  i*86 | x86) export CPU_ARCH="i386" ;;
  x86_64 | amd64) export CPU_ARCH="amd64" ;;
  *) echo -e "\033[31m$(po_getmsg "Unknow cpu architecture for this device !")\033[0m" && exit 1 ;;
  esac
}
