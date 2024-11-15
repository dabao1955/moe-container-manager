// SPDX-License-Identifier: MIT
/*
 *
 * This file is part of ruri, with ABSOLUTELY NO WARRANTY.
 *
 * MIT License
 *
 * Copyright (c) 2022-2024 Moe-hacker
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 *
 */
#include "include/ruri.h"
void show_version_info(void)
{
	/*
	 * Just show version info and license.
	 * Version info is defined in macro RURI_VERSION.
	 * RURI_COMMIT_ID is defined as -D option of compiler.
	 */
	cprintf("\n");
	cprintf("{base}      ●●●●  ●   ● ●●●●   ●●●\n");
	cprintf("{base}      ●   ● ●   ● ●   ●   ●\n");
	cprintf("{base}      ●●●●  ●   ● ●●●●    ●\n");
	cprintf("{base}      ●  ●  ●   ● ●  ●    ●\n");
	cprintf("{base}      ●   ●  ●●●  ●   ●  ●●●\n");
	cprintf("{base}    Revamp, Until Reach Ideal\n");
	cprintf("{base}  Licensed under the MIT License\n");
	cprintf("{base}    <https://mit-license.org>\n");
	cprintf("{base}Copyright (C) 2022-2024 Moe-hacker\n\n");
	cprintf("{base}%s%s%s", "ruri version .....:  ", RURI_VERSION, "\n");
#if defined(RURI_COMMIT_ID)
	cprintf("{base}%s%s%s", "ruri commit id ...:  ", RURI_COMMIT_ID, "\n");
#endif
#if defined(LIBCAP_MAJOR) && defined(LIBCAP_MINOR)
	cprintf("{base}%s%d%s%d%s", "libcap ...........:  ", LIBCAP_MAJOR, ".", LIBCAP_MINOR, "\n");
#endif
#if defined(SCMP_VER_MAJOR) && defined(SCMP_VER_MINOR) && defined(SCMP_VER_MICRO)
	cprintf("{base}%s%d%s%d%s%d%s", "libseccomp .......:  ", SCMP_VER_MAJOR, ".", SCMP_VER_MINOR, ".", SCMP_VER_MICRO, "\n");
#endif
	cprintf("{base}%s%d%s%d%s", "libk2v ...........:  ", LIBK2V_MAJOR, ".", LIBK2V_MINOR, "\n");
	cprintf("{base}%s%d%s%d%s", "cprintf ..........:  ", CPRINTF_MAJOR, ".", CPRINTF_MINOR, "\n");
	cprintf("{base}%s%s\n", "Compiler version .:  ", __VERSION__);
	cprintf("{base}%s%s\n", "Build date .......:  ", __TIMESTAMP__);
	cprintf("{base}\nThere is NO WARRANTY, to the extent permitted by law\n");
	cprintf("{clear}\n");
}
// For `ruri -V`.
void show_version_code(void)
{
	/*
	 * The version code is not standard now,
	 * so in fact it's very useless.
	 * Maybe it can be useful one day...
	 */
	cprintf("%s\n", RURI_VERSION);
}
// For `ruri -h`.
void show_helps(void)
{
	/*
	 * Help page of ruri.
	 * I think you can understand...
	 */
	cprintf("{base}ruri %s\n\n", RURI_VERSION);
	cprintf("{base}Lightweight, User-friendly Linux-container Implementation\n");
	cprintf("\n");
	cprintf("{base}Usage:\n");
	cprintf("{base}  ruri [OPTIONS]...\n");
	cprintf("{base}  ruri [ARGS]... [CONTAINER_DIRECTORY]... [COMMAND [ARGS]...]\n");
	cprintf("\n");
	cprintf("{base}OPTIONS:\n");
	cprintf("{base}  -v, --version ...............................: Show version info\n");
	cprintf("{base}  -V, --version-code ..........................: Show version code\n");
	cprintf("{base}  -h, --help ..................................: Show helps\n");
	cprintf("{base}  -H, --show-examples .........................: Show commandline examples\n");
	cprintf("{base}  -U, --umount [container_dir] ................: Umount a container\n");
	cprintf("{base}  -P, --ps [container_dir] ....................: Show process status of the container(*)\n");
	cprintf("\n");
	cprintf("{base}ARGS:\n");
	cprintf("{base}  -D, --dump-config ...........................: Dump the config\n");
	cprintf("{base}  -o, --output [config file] ..................: Set output file of `-D` option\n");
	cprintf("{base}  -c, --config [config file] ..................: Use config file\n");
	cprintf("{base}  -a, --arch [arch] ...........................: Simulate architecture via binfmt_misc/QEMU (**)\n");
	cprintf("{base}  -q, --qemu-path [path] ......................: Specify the path of QEMU\n");
	cprintf("{base}  -u, --unshare ...............................: Enable unshare feature\n");
	cprintf("{base}  -n, --no-new-privs ..........................: Set NO_NEW_PRIVS flag\n");
	cprintf("{base}  -N, --no-rurienv ............................: Do not use .rurienv file\n");
	cprintf("{base}  -s, --enable-seccomp ........................: Enable built-in Seccomp profile\n");
	cprintf("{base}  -p, --privileged ............................: Run privileged container\n");
	cprintf("{base}  -r, --rootless ..............................: Run rootless container\n");
	cprintf("{base}  -k, --keep [cap] ............................: Keep the specified capability(***)\n");
	cprintf("{base}  -d, --drop [cap] ............................: Drop the specified capability\n");
	cprintf("{base}  -e, --env [env] [value] .....................: Set environment variables to its value (****)\n");
	cprintf("{base}  -m, --mount [dir/dev/img/file] [target] .....: Mount dir/block-device/image/file to target (*****)\n");
	cprintf("{base}  -M, --ro-mount [dir/dev/img/file] [target] ..: Mount dir/block-device/image/file as read-only\n");
	cprintf("{base}  -S, --host-runtime ..........................: Bind-mount /dev/, /sys/ and /proc/ from host\n");
	cprintf("{base}  -R, --read-only .............................: Mount / as read-only\n");
	cprintf("{base}  -l, --limit [cpuset=cpu/memory=mem] .........: Set cpuset/memory limit(******)\n");
	cprintf("{base}  -w, --no-warnings ...........................: Disable warnings\n");
	cprintf("{base}  -f, --fork ..................................: fork() before exec the command(*******)\n");
	cprintf("{base}  -j, --just-chroot ...........................: Just chroot, do not create the runtime dirs\n");
	cprintf("{base}  -W, --work-dir [dir] ........................: Set the work directory in container\n");
	cprintf("{base}  -A, --unmask-dirs ...........................: Unmask dirs in /proc and /sys\n");
	cprintf("\n");
	cprintf("{base}Note:\n");
	cprintf("{base}(*)      : Will not work for unshare container without PID ns support\n");
	cprintf("{base}(**)     : `-a` option also need `-q` is set\n");
	cprintf("{base}(***)    : cap can both be value or name (e.j. cap_chown == 0)\n");
	cprintf("{base}(****)   : Will not work if [COMMAND [ARGS]...] is like `/bin/su -`\n");
	cprintf("{base}(*****)  : You can use `-m/-M [source] /` to mount other source as root\n");
	cprintf("{base}(******) : Each `-l` option can only set one of the cpuset/memory limits\n");
	cprintf("{base}           for example: `ruri -l memory=1M -l cpuset=1 /test`\n");
	cprintf("{base}(*******): This option is totally useless\n");
	cprintf("{base}{clear}\n");
}
// For `ruri -H`.
void show_examples(void)
{
	/*
	 * Command line examples.
	 * I think you can understand...
	 */
	cprintf("\n");
	cprintf("{base}# Quickly setup a container(with rootfstool):\n");
	cprintf("  {green}git {yellow}clone {purple}https://github.com/Moe-hacker/rootfstool\n");
	cprintf("  {green}cd {purple}rootfstool\n");
	cprintf("  {green}./rootfstool {yellow}download {blue}-d {purple}alpine {blue}-v {purple}edge\n");
	cprintf("  {green}mkdir {purple}/tmp/alpine\n");
	cprintf("  {green}sudo tar {blue}-xvf {purple}rootfs.tar.xz {blue}-C {purple}/tmp/alpine\n");
	cprintf("{base}# Run chroot container:\n");
	cprintf("  {green}sudo ruri {purple}/tmp/alpine\n");
	cprintf("{base}# Very simple as you can see.\n");
	cprintf("{base}# About the capabilities:\n");
	cprintf("{base}# Run privileged chroot container:\n");
	cprintf("  {green}sudo ruri {blue}-p {purple}/tmp/alpine\n");
	cprintf("{base}# If you want to run privileged chroot container,\n");
	cprintf("{base}# but you don't want to give the container cap_sys_chroot privileges:\n");
	cprintf("  {green}sudo ruri {blue}-p -d \033[36mcap_sys_chroot {purple}/tmp/alpine\n");
	cprintf("{base}# If you want to run chroot container with common privileges,\n");
	cprintf("{base}# but you want cap_sys_admin to be kept:\n");
	cprintf("  {green}sudo ruri {blue}-k \033[36mcap_sys_admin {purple}/tmp/alpine\n");
	cprintf("{base}# About unshare:\n");
	cprintf("{base}# Unshare container's capability options are same with chroot.\n");
	cprintf("{base}# Run unshare container:\n");
	cprintf("  {green}sudo ruri {blue}-u {purple}/tmp/alpine\n");
	cprintf("{base}# Umount the container:\n");
	cprintf("  {green}sudo ruri {blue}-U {purple}/tmp/alpine\n");
	cprintf("{clear}\n");
}
