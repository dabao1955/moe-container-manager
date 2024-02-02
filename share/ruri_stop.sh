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
EXTRA_MOUNTPOINTS="[EXTRA_MOUNTPOINTS]"
sudo ruri -U ${CONTAINER_DIR}
for i in ${EXTRA_MOUNTPOINTS}
do
sudo unmount -lvf $i
done
echo -e "\033[33mPlease reboot your device if you need to remove the container.\033[0m"
