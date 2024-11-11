#!/bin/bash
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
# Show warning.
echo -e "\033[33mWarning: please reboot your device before removing the container."
echo "I am not responsible for anything that may happen to your device by using this script !!!"
# Remove container.
echo -e "\n\n"
echo "Press CTRL-C to cancel this script"
echo "Or press yes to remove this container\n"
read -p "=>" i
if [[ i != "yes" ]]; then
  echo "exit"
  exit 0
fi
# Kill proot.
killall -9 proot
# Remove.
echo "This is the last chance to regret it"
echo "Press CTRL-C to cancel this script"
echo "Or press enter to continue\n"
read i
rm -rf ${CONTAINER_DIR}
