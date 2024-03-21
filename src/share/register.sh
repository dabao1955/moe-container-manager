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
read -p "Enter the path of container >" CONTAINER_DIR
if [[ $1 == -r ]]; then
  read -p "Choose the backend:\n[1] ruri [2] proot >" BACKEND
  if [[ $BACKEND == "1" ]]; then
    BACKEND="ruri"
  else
    BACKEND="proot"
  fi
else
  BACKEND="proot"
fi
read -p "Name the container >" NAME

#check

if [[ $BACKEND == "ruri" ]]; then

fi
