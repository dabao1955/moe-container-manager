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
static void mount_cgroup_v1(void)
{
	/*
	 * Mount Cgroup v1 memory and cpuset controller.
	 * Nothing to return because if this function run failed,
	 * that means cgroup is fully not supported on the device.
	 */
	mkdir("/sys/fs/cgroup", S_IRUSR | S_IWUSR);
	// Maybe needless.
	umount2("/sys/fs/cgroup", MNT_DETACH | MNT_FORCE);
	// Mount /sys/fs/cgroup as tmpfs.
	mount("tmpfs", "/sys/fs/cgroup", "tmpfs", MS_NOSUID | MS_NODEV | MS_NOEXEC | MS_RELATIME, NULL);
	// We only need cpuset and memory cgroup.
	mkdir("/sys/fs/cgroup/memory", S_IRUSR | S_IWUSR);
	mkdir("/sys/fs/cgroup/cpuset", S_IRUSR | S_IWUSR);
	mount("none", "/sys/fs/cgroup/memory", "cgroup", MS_NOSUID | MS_NODEV | MS_NOEXEC | MS_RELATIME, "memory");
	mount("none", "/sys/fs/cgroup/cpuset", "cgroup", MS_NOSUID | MS_NODEV | MS_NOEXEC | MS_RELATIME, "cpuset");
	log("{base}Tried to mount cgroup v1\n");
}
static bool is_cgroupv2_supported(void)
{
	/*
	 * Check if cgroup v2 supports cpuset and memory controller.
	 * Return true if cgroup.controllers contains "cpuset" and "memory".
	 */
	bool found_cpuset = false;
	bool found_memory = false;
	mkdir("/sys/fs/cgroup/ruri", S_IRUSR | S_IWUSR);
	// Check if we have a controlable cgroup for cpuset and memory.
	int fd = open("/sys/fs/cgroup/ruri/cgroup.controllers", O_RDONLY | O_CLOEXEC);
	if (fd < 0) {
		return false;
	}
	char buf[128] = { '\0' };
	ssize_t len = read(fd, buf, sizeof(buf));
	buf[len] = '\0';
	if (strstr(buf, "cpuset") != NULL) {
		found_cpuset = true;
	}
	if (strstr(buf, "memory") != NULL) {
		found_memory = true;
	}
	close(fd);
	if (found_cpuset && found_memory) {
		return true;
	}
	return false;
}
static int mount_cgroup_v2(void)
{
	/*
	 * We will mount cgroup2 cpuset and memory controller.
	 * If the device does not support, return -1,
	 * or we just return 0.
	 */
	mkdir("/sys/fs/cgroup", S_IRUSR | S_IWUSR);
	// Maybe needless.
	umount2("/sys/fs/cgroup", MNT_DETACH | MNT_FORCE);
	// I love cgroup2, because it's easy to mount and control.
	int ret = mount("none", "/sys/fs/cgroup", "cgroup2", MS_NOSUID | MS_NODEV | MS_NOEXEC | MS_RELATIME, NULL);
	if (ret != 0) {
		return ret;
	}
	// But if it's not suppored, umount the controller and back to v1.
	if (!is_cgroupv2_supported()) {
		log("{base}Cgroup v2 is not supported, back to v1\n");
		umount2("/sys/fs/cgroup", MNT_DETACH | MNT_FORCE);
		return -1;
	}
	log("{base}Tried to mount cgroup v2\n");
	return 0;
}
static int mount_cgroup(void)
{
	/*
	 * Return the type of cgroup (1/2).
	 * Use cgroupv2 by default if supported.
	 */
	// It's better to use cgroupv2.
	if (mount_cgroup_v2() == 0) {
		return 2;
	}
	// But on some devices, we have to use v1, as v2 is not supported.
	mount_cgroup_v1();
	// Note that if even v1 is not supported, we will go ahead, but cgroup will not work.
	return 1;
}
static void set_cgroup_v1(const struct CONTAINER *_Nonnull container)
{
	/*
	 * We creat a new cgroup name as the same of container_id,
	 * add pid to the cgroup, and set limit.
	 * We will do this even if cpu and memory limit are both NULL,
	 * because this function will only set the limit when we init the container,
	 * but if the container is still running, we need to join its cgroup,
	 * which is already created.
	 * If the container is running, after read_info(), container_id will be unified,
	 * and container->memory/container->cpuset will be cleared, because it should only
	 * be set when init the container.
	 */
	pid_t pid = getpid();
	char buf[128] = { '\0' };
	char cpuset_cgroup_path[PATH_MAX] = { '\0' };
	char memory_cgroup_path[PATH_MAX] = { '\0' };
	sprintf(cpuset_cgroup_path, "/sys/fs/cgroup/cpuset/%d", container->container_id);
	sprintf(memory_cgroup_path, "/sys/fs/cgroup/memory/%d", container->container_id);
	mkdir(cpuset_cgroup_path, S_IRUSR | S_IWUSR);
	mkdir(memory_cgroup_path, S_IRUSR | S_IWUSR);
	usleep(2000);
	int fd = -1;
	if (container->memory != NULL) {
		// Set memory limit.
		char memory_cgroup_limit_path[PATH_MAX] = { '\0' };
		sprintf(memory_cgroup_limit_path, "/sys/fs/cgroup/memory/%d/memory.limit_in_bytes", container->container_id);
		fd = open(memory_cgroup_limit_path, O_RDWR | O_CLOEXEC);
		if (fd < 0 && !container->no_warnings) {
			warning("{yellow}Set memory limit failed{clear}\n");
			goto cpuset;
		}
		sprintf(buf, "%s\n", container->memory);
		if (write(fd, buf, strlen(buf)) < 0 && !container->no_warnings) {
			warning("{yellow}Set memory limit failed{clear}\n");
		}
		close(fd);
	}
	char memory_cgroup_procs_path[PATH_MAX] = { '\0' };
	sprintf(memory_cgroup_procs_path, "/sys/fs/cgroup/memory/%d/cgroup.procs", container->container_id);
	// Add pid to container_id memory cgroup.
	fd = open(memory_cgroup_procs_path, O_RDWR | O_CLOEXEC);
	if (fd < 0 && !container->no_warnings) {
		warning("{yellow}Set memory limit failed{clear}\n");
		goto cpuset;
	}
	sprintf(buf, "%d\n", pid);
	write(fd, buf, strlen(buf));
	close(fd);
cpuset:
	if (container->cpuset != NULL) {
		// Set cpuset limit.
		char cpuset_cgroup_mems_path[PATH_MAX] = { '\0' };
		sprintf(cpuset_cgroup_mems_path, "/sys/fs/cgroup/cpuset/%d/cpuset.mems", container->container_id);
		fd = open(cpuset_cgroup_mems_path, O_RDWR | O_CLOEXEC);
		if (fd < 0 && !container->no_warnings) {
			warning("{yellow}Set cpuset limit failed{clear}\n");
			// Do not keep the apifs mounted.
			umount2("/sys/fs/cgroup", MNT_DETACH | MNT_FORCE);
			return;
		}
		write(fd, "0\n", strlen("0\n"));
		close(fd);
		char cpuset_cgroup_cpus_path[PATH_MAX] = { '\0' };
		sprintf(cpuset_cgroup_cpus_path, "/sys/fs/cgroup/cpuset/%d/cpuset.cpus", container->container_id);
		fd = open(cpuset_cgroup_cpus_path, O_RDWR | O_CLOEXEC);
		if (fd < 0 && !container->no_warnings) {
			warning("{yellow}Set cpuset limit failed{clear}\n");
			// Do not keep the apifs mounted.
			umount2("/sys/fs/cgroup", MNT_DETACH | MNT_FORCE);
			return;
		}
		sprintf(buf, "%s\n", container->cpuset);
		if (write(fd, buf, strlen(buf)) < 0 && !container->no_warnings) {
			warning("{yellow}Set cpu limit failed{clear}\n");
		}
		close(fd);
	}
	char cpuset_cgroup_procs_path[PATH_MAX] = { '\0' };
	sprintf(cpuset_cgroup_procs_path, "/sys/fs/cgroup/cpuset/%d/cgroup.procs", container->container_id);
	// Add pid to container_id cpuset cgroup.
	fd = open(cpuset_cgroup_procs_path, O_RDWR | O_CLOEXEC);
	if (fd < 0 && !container->no_warnings) {
		warning("{yellow}Set cpuset limit failed{clear}\n");
		// Do not keep the apifs mounted.
		umount2("/sys/fs/cgroup", MNT_DETACH | MNT_FORCE);
		return;
	}
	sprintf(buf, "%d\n", pid);
	write(fd, buf, strlen(buf));
	close(fd);
	// Do not keep the apifs mounted.
	umount2("/sys/fs/cgroup", MNT_DETACH | MNT_FORCE);
}
static void set_cgroup_v2(const struct CONTAINER *_Nonnull container)
{
	/*
	 * See comment of set_cgroup_v1().
	 */
	pid_t pid = getpid();
	char buf[128] = { '\0' };
	char cgroup_path[PATH_MAX] = { '\0' };
	sprintf(cgroup_path, "/sys/fs/cgroup/%d", container->container_id);
	mkdir(cgroup_path, S_IRUSR | S_IWUSR);
	usleep(2000);
	char cgroup_procs_path[PATH_MAX] = { '\0' };
	sprintf(cgroup_procs_path, "/sys/fs/cgroup/%d/cgroup.procs", container->container_id);
	// Add pid to container_id cgroup.
	int fd = open(cgroup_procs_path, O_RDWR | O_CLOEXEC);
	if (fd < 0 && !container->no_warnings) {
		warning("{yellow}Set cgroup.procs failed{clear}\n");
		// Do not keep the apifs mounted.
		umount2("/sys/fs/cgroup", MNT_DETACH | MNT_FORCE);
		return;
	}
	sprintf(buf, "%d\n", pid);
	write(fd, buf, strlen(buf));
	close(fd);
	if (container->memory != NULL) {
		// Set memory limit.
		char cgroup_memlimit_path[PATH_MAX] = { '\0' };
		sprintf(cgroup_memlimit_path, "/sys/fs/cgroup/%d/memory.high", container->container_id);
		fd = open(cgroup_memlimit_path, O_RDWR | O_CLOEXEC);
		if (fd < 0 && !container->no_warnings) {
			warning("{yellow}Set memory limit failed{clear}\n");
			// Do not keep the apifs mounted.
			umount2("/sys/fs/cgroup", MNT_DETACH | MNT_FORCE);
			return;
		}
		sprintf(buf, "%s\n", container->memory);
		if (write(fd, buf, strlen(buf)) < 0 && !container->no_warnings) {
			warning("{yellow}Set memory limit failed{clear}\n");
		}
		close(fd);
	}
	if (container->cpuset != NULL) {
		// Set cpuset limit.
		char cgroup_cpuset_path[PATH_MAX] = { '\0' };
		sprintf(cgroup_cpuset_path, "/sys/fs/cgroup/%d/cpuset.cpus", container->container_id);
		fd = open(cgroup_cpuset_path, O_RDWR | O_CLOEXEC);
		if (fd < 0 && !container->no_warnings) {
			warning("{yellow}Set cpu limit failed{clear}\n");
			// Do not keep the apifs mounted.
			umount2("/sys/fs/cgroup", MNT_DETACH | MNT_FORCE);
			return;
		}
		sprintf(buf, "%s\n", container->cpuset);
		if (write(fd, buf, strlen(buf)) < 0 && !container->no_warnings) {
			warning("{yellow}Set cpu limit failed{clear}\n");
		}
		close(fd);
	}
	// Do not keep the apifs mounted.
	umount2("/sys/fs/cgroup", MNT_DETACH | MNT_FORCE);
}
void set_limit(const struct CONTAINER *_Nonnull container)
{
	/*
	 * Mount cgroup controller and set limit.
	 * Nothing to return, only warnings to show if cgroup is not supported.
	 */
	// Mount cgroup controller and get the type of cgroup.
	int cgtype = mount_cgroup();
	// For cgroup v1.
	if (cgtype == 1) {
		set_cgroup_v1(container);
	}
	// For cgroup v2.
	else {
		set_cgroup_v2(container);
	}
}
