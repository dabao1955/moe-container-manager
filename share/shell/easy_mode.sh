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

##############
##TODO
##Easy_register
function easy_create() {
  trap "exit" SIGINT
  WIDTH=$(($(stty size | awk '{print $2}') - 8))
  if yoshinon --title "[] RUN MODE" --yes-button "chroot" --no-button "proot" --yesno "if your phone is rooted,it is recommand to run container with chroot mode\nIf not ,please choose proot\n\nPlease choose your run mode:" 12 $WIDTH; then
    TYPE=chroot
  else
    TYPE=proot
  fi
  LIST="1 alpine 2 archlinux 3 centos 4 debian 5 fedora 6 kali 7 manjaro 8 opensuse 9 parrot 10 ubuntu"
  LIST2="alpine archlinux centos debian fedora kali manjaro opensuse parrot ubuntu"
  NUMBER=$(yoshinon --title "[] OS" --menu "Choose the OS to install:" 15 $WIDTH 6 $LIST 3>&1 1>&2 2>&3)
  OS=$(echo $LIST2 | awk "{print \$$NUMBER}")
  unset LIST LIST2 NUMBER
  if [[ ${OS} != "parrot" ]] && [[ ${OS} != "manjaro" ]]; then
    NUMBER=0
    for VERSION in $(curl -sL http://images.linuxcontainers.org/images/$OS | grep "href" | sed -E 's@<a (href)@\n\1@g' | awk -F 'href=' '{print $2}' | cut -d '"' -f 2 | cut -d "/" -f 1 | grep -v '\.\.'); do
      NUMBER=$(($NUMBER + 1))
      LIST+="$NUMBER $VERSION "
      LIST2+="$VERSION "
    done
    unset VERSION NUMBER
    NUMBER=$(yoshinon --title "[] VERSION" --menu "Choose the version to install:" 15 $WIDTH 6 $LIST 3>&1 1>&2 2>&3)
    VERSION=$(echo $LIST2 | awk "{print \$$NUMBER}")
  fi
  get_cpu_arch
  if [[ ! -e $PREFIX/var/container/${OS}-${VERSION}-${CPU_ARCH}.tar.xz ]]; then
    PULL_ROOTFS ${OS} ${VERSION} ${CPU_ARCH}
  fi
  if [[ -e /home/${TYPE}-${OS}-${VERSION}_${CPU_ARCH} ]]; then
    echo -e "Error: container already installed"
    return 1
  fi
  if [[ ${TYPE} == "chroot" ]]; then
    [[ -e $PREFIX/etc/container/chroot ]] || mkdir -p $PREFIX/etc/container/chroot
    echo -e "#This file was automatically created by moe-container-manager.\n#Do not edit this file if you don't know what you are doing !" >>$PREFIX/etc/container/chroot/container-${TYPE}-${OS}-${VERSION}_${CPU_ARCH}.conf
    echo -e "OS=${OS}\nCONTAINER_DIR=/home/${TYPE}-${OS}-${VERSION}_${CPU_ARCH}\nENABLE_UNSHARE=${ENABLE_UNSHARE}\nPRIVAGE_LEVEL=1\nCROSS_ARCH=null\nMOUNT_SDCARD=${MOUNT_SDCARD}" >>$PREFIX/etc/container/chroot/container-${TYPE}-${OS}-${VERSION}_${CPU_ARCH}.conf
    sudo container -e CREATE_CHROOT_CONTAINER ${OS}-${VERSION}-${CPU_ARCH}.tar.xz /home/${TYPE}-${OS}-${VERSION}_${CPU_ARCH}
  else
    export CROSSARCH=null
    CREATE_PROOT_CONTAINER ${OS}-${VERSION}-${CPU_ARCH}.tar.xz /home/${TYPE}-${OS}-${VERSION}_${CPU_ARCH} ${CROSS_ARCH}
    [[ -e $PREFIX/etc/container/proot ]] || mkdir -p $PREFIX/etc/container/proot
    echo -e "#This file was automatically created by moe-container-manager.\n#Do not edit this file if you don't know what you are doing !" >>$PREFIX/etc/container/proot/container-${TYPE}-${OS}-${VERSION}_${CPU_ARCH}.conf
    echo -e "OS=${OS}\nCONTAINER_DIR=/home/${TYPE}-${OS}-${VERSION}_${CPU_ARCH}\nCROSS_ARCH=${CROSSARCH}\nMOUNT_SDCARD=${MOUNT_SDCARD}" >>$PREFIX/etc/container/proot/container-${TYPE}-${OS}-${VERSION}_${CPU_ARCH}.conf
  fi
}
function easy_remove() {
  trap "exit" SIGINT
  WIDTH=$(($(stty size | awk '{print $2}') - 8))
  NUMBER=0
  if [[ -e $PREFIX/etc/container/proot ]]; then
    for CONTAINER in $(ls $PREFIX/etc/container/proot); do
      NAME=${CONTAINER#container-}
      NAME=${NAME%%.conf}
      NUMBER=$(($NUMBER + 1))
      LIST+="$NUMBER $NAME(proot) "
      LIST2+="$NAME "
    done
  fi
  if [[ -e $PREFIX/etc/container/chroot ]]; then
    for CONTAINER in $(ls $PREFIX/etc/container/chroot); do
      NAME=${CONTAINER#container-}
      NAME=${NAME%%.conf}
      NUMBER=$(($NUMBER + 1))
      LIST+="$NUMBER $NAME(chroot) "
      LIST2+="$NAME "
    done
  fi
  unset CONTAINER NUMBER
  if [[ $LIST == "" ]]; then
    yoshinon --title "[] ERROR" --msgbox "No container created!" 7 $WIDTH
    return 1
  fi
  NUMBER=$(yoshinon --title "[] CONTAINER" --menu "Choose the container to remove:" 15 $WIDTH 6 $LIST 3>&1 1>&2 2>&3)
  CONTAINER=$(echo $LIST2 | awk "{print \$$NUMBER}")
  REMOVE_CONTAINER "$CONTAINER"
}
function easy_run() {
  trap "exit" SIGINT
  WIDTH=$(($(stty size | awk '{print $2}') - 8))
  NUMBER=0
  if [[ -e $PREFIX/etc/container/proot ]]; then
    for CONTAINER in $(ls $PREFIX/etc/container/proot); do
      NAME=${CONTAINER#container-}
      NAME=${NAME%%.conf}
      NUMBER=$(($NUMBER + 1))
      LIST+="$NUMBER $NAME(proot) "
      LIST2+="$NAME "
    done
  fi
  if [[ -e $PREFIX/etc/container/chroot ]]; then
    for CONTAINER in $(ls $PREFIX/etc/container/chroot); do
      NAME=${CONTAINER#container-}
      NAME=${NAME%%.conf}
      NUMBER=$(($NUMBER + 1))
      LIST+="$NUMBER $NAME(chroot) "
      LIST2+="$NAME "
    done
  fi
  unset CONTAINER NUMBER
  if [[ $LIST == "" ]]; then
    yoshinon --title "[] ERROR" --msgbox "No container created!" 7 $WIDTH
    return 1
  fi
  NUMBER=$(yoshinon --title "[] CONTAINER" --menu "Choose the container to run:" 15 $WIDTH 6 $LIST 3>&1 1>&2 2>&3)
  CONTAINER=$(echo $LIST2 | awk "{print \$$NUMBER}")
  export BE_SILENT=true
  RUN_CONTAINER $CONTAINER
}
function easy_backup() {
  trap "exit" SIGINT
  WIDTH=$(($(stty size | awk '{print $2}') - 8))
  NUMBER=0
  if [[ -e $PREFIX/etc/container/proot ]]; then
    for CONTAINER in $(ls $PREFIX/etc/container/proot); do
      NAME=${CONTAINER#container-}
      NAME=${NAME%%.conf}
      NUMBER=$(($NUMBER + 1))
      LIST+="$NUMBER $NAME(proot) "
      LIST2+="$NAME "
    done
  fi
  if [[ -e $PREFIX/etc/container/chroot ]]; then
    for CONTAINER in $(ls $PREFIX/etc/container/chroot); do
      NAME=${CONTAINER#container-}
      NAME=${NAME%%.conf}
      NUMBER=$(($NUMBER + 1))
      LIST+="$NUMBER $NAME(chroot) "
      LIST2+="$NAME "
    done
  fi
  unset CONTAINER NUMBER
  if [[ $LIST == "" ]]; then
    yoshinon --title "[] ERROR" --msgbox "No container created!" 7 $WIDTH
    return 1
  fi
  NUMBER=$(yoshinon --title "[] CONTAINER" --menu "Choose the container to backup:" 15 $WIDTH 6 $LIST 3>&1 1>&2 2>&3)
  CONTAINER=$(echo $LIST2 | awk "{print \$$NUMBER}")
  EXPORT_CONTAINER $CONTAINER
}

function easy_restore() {
  #TODO
  return 0
}
function easy_mode() {
  trap "exit" SIGINT
  WIDTH=$(($(stty size | awk '{print $2}') - 8))
  OPTION=$(yoshinon --title "[] moe-container-manager" --menu "Choose an operation:" 15 $WIDTH 6 1 "install" 2 "remove" 3 "run" 3>&1 1>&2 2>&3)
  case $OPTION in
  1) EASY_INSTALL ;;
  2) EASY_REMOVE ;;
  3) EASY_RUN ;;
  esac
}
