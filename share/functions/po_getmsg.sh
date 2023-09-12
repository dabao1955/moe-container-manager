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
#
# i18n.
function po_getmsg() {
  # Since termux does not support multiple languages,
  # the *.mo files seems not works.
  # So termux-container directly uses the *.po files
  # for translation.
  # NOTE:
  # This function only supports the *.po files created with --no-wrap option.
  # Usage:
  # po_getmsg "message"
  PO_FILE="$PREFIX/share/termux-container/lang/container-${TERMUX_CONTAINER_LANGUAGE}.po"
  if [[ ! -e ${PO_FILE} ]]; then
    printf "$@"
    return 1
  fi
  msg=$(grep -A 1 "\"$@\"" ${PO_FILE} | tail -1)
  if [[ ${msg} == "" ]]; then
    printf "$@"
    return 1
  fi
  msg=${msg#msgstr\ }
  msg=${msg#\"}
  msg=${msg%\"}
  printf "${msg}"
}
