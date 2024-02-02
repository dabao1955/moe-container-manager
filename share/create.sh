#!/bin/bash

pv $ROOTFS | tar -xJf - -C ${CONTAINER_DIR}
# Fix permission of su.
# proot do not need this
chown root:root ${CONTAINER_DIR}/bin/su
chmod 777 ${CONTAINER_DIR}/bin/su
# Create mountpoints.
[[ -e ${CONTAINER_DIR}/dev ]] || mkdir ${CONTAINER_DIR}/dev
[[ -e ${CONTAINER_DIR}/proc ]] || mkdir ${CONTAINER_DIR}/proc
[[ -e ${CONTAINER_DIR}/sys ]] || mkdir ${CONTAINER_DIR}/sys
[[ -e ${CONTAINER_DIR}/sdcard ]] || mkdir ${CONTAINER_DIR}/sdcard
# Fix dns problem.
rm -f ${CONTAINER_DIR}/etc/resolv.conf >>/dev/null 2>&1
echo nameserver 8.8.8.8 >>${CONTAINER_DIR}/etc/resolv.conf
echo nameserver 114.114.114.114 >>${CONTAINER_DIR}/etc/resolv.conf
# Fix network problem.
cp $PREFIX/share/termux-container/group_add.sh ${CONTAINER_DIR}/tmp
chmod 777 ${CONTAINER_DIR}/tmp/group_add.sh

if [[ ${NEW_USER} != "" && ${PASSWORD} != "" ]]; then
  sed -i "s/NEW_USER=\"\"/NEW_USER=${NEW_USER}/" ${CONTAINER_DIR}/tmp/group_add.sh
  sed -i "s/PASSWORD=\"\"/PASSWORD=${PASSWORD}/" ${CONTAINER_DIR}/tmp/group_add.sh
fi
unset LD_PRELOAD
COMMAND="proot --link2symlink --sysvipc -0 -r ${CONTAINER_DIR} -b /dev -b /sys -b /proc -w /root"
if [[ ${CROSS_ARCH} != "null" ]]; then
  COMMAND+=" -q qemu-${CROSS_ARCH}"
fi
${COMMAND} /tmp/group_add.sh
