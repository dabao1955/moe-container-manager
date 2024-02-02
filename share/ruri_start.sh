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
MOUNT_SDCARD=[MOUNT_SDCARD]
ENABLE_UNSHARE=[ENABLE_UNSHARE]
USE_DAEMON=[USE_DAEMON]
EXTRA_ARGS="[EXTRA_ARGS]"
# Start daemon.
unset LD_PRELOAD
if [[ ${USE_DAEMON} == "true" ]]; then
  ruri -T || ruri -D
fi
# Set args.
ARGS=${EXTRA_ARGS}
if [[ ${MOUNT_SDCARD} == "true" ]]; then
  ARGS+=" -m /sdcard /sdcard"
fi
if [[ ${ENABLE_UNSHARE} == "true" ]]; then
  ARGS+=" -u"
fi
# Run container.
LD_PRELOAD= sudo ruri ${ARGS} ${CONTAINER_DIR} $@
