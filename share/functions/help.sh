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

function script_help() {
  col=$(($(($(stty size | awk '{print $2}'))) / 2 - 25))
  logo="\033[1;38;2;254;228;208m
\033[${col}G         ●●●●● ●●●●● ●●●●  ●   ● ●   ● ●   ●
\033[${col}G           ●   ●     ●   ● ●● ●● ●   ●  ● ●
\033[${col}G           ●   ●●●●  ●●●●  ● ● ● ●   ●   ●
\033[${col}G           ●   ●     ●  ●  ●   ● ●   ●  ● ●
\033[${col}G           ●   ●●●●● ●   ● ●   ●  ●●●  ●   ●



\033[${col}G ●●●   ●●●  ●   ● ●●●●●   ●    ●●●  ●   ● ●●●●● ●●●●
\033[${col}G●   ● ●   ● ●●  ●   ●    ● ●    ●   ●●  ● ●     ●   ●
\033[${col}G●     ●   ● ● ● ●   ●   ●   ●   ●   ● ● ● ●●●●  ●●●●
\033[${col}G●   ● ●   ● ●  ●●   ●   ●●●●●   ●   ●  ●● ●     ●  ●
\033[${col}G ●●●   ●●●  ●   ●   ●   ●   ●  ●●●  ●   ● ●●●●● ●   ●

"
  printf "$logo"
  SIZE=$(stty size | awk '{print $2}')
  let SIZE=$(($SIZE - 16))
  echo "//"
  echo
  echo -e "\e[30;1;48;2;254;228;208;38;2;0;0;0mTERMUX-CONTAINER$(yes " " | sed $SIZE'q' | tr -d '\n')\033[0m"
  echo
  echo -e "${COLOR}//"
  echo
  echo -e "$(po_getmsg "Usage:")"
  echo -e " $(po_getmsg "container                       #Start container console.")"
  echo -e " $(po_getmsg "container -h                    #Show this page.")"
  echo -e " $(po_getmsg "container cp [Name:Path] [Path] #Copy files,like docker cp.")"
  echo -e " $(po_getmsg "container -i [Image File]       #Import an image.")"
  echo -e " $(po_getmsg "container -E                    #Easy mode.")"
  echo -e " $(po_getmsg "container -e [Function]         #Exec function in this script *NOT for user.")"
}
# Help page for container-console.
function console_help() {
  # Usage:
  # console_help
  # I hope you can understand...
  echo -e "${COLOR}$(po_getmsg "Usage:")"
  echo "  $(po_getmsg "help                       :Show this page.")"
  echo "  $(po_getmsg "exit                       :Exit console.")"
  echo "  $(po_getmsg "new                        :Create a new container.")"
  echo "  $(po_getmsg "search [all/OS] (Arch)     :Search for images.")"
  echo "  $(po_getmsg "pull [OS] [Version] (Arch) :Download image,just save.")"
  echo "  $(po_getmsg "rmi [OS] [Version] (Arch)  :Remove an image.")"
  echo "  $(po_getmsg "cp [Name:Path] [Path]      :Copy files,like docker cp.")"
  echo "  $(po_getmsg "ls                         :List containers and images.")"
  echo "  $(po_getmsg "rm [Name]                  :Remove a container.")"
  echo "  $(po_getmsg "login [Name]               :Login to the container.")"
  echo "  $(po_getmsg "import [Image File]        :Import an image.")"
  echo "  $(po_getmsg "export [Name]              :Export a container as an image.")"
  echo "  $(po_getmsg "info                       :Show version && system info.")"
}
