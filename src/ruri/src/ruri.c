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
/*
 * This file was the main.c of ruri.
 */
// Do some checks before chroot(2),called by main().
static void check_container(const struct RURI_CONTAINER *_Nonnull container)
{
	/*
	 * It's called by main() to check if container config is correct.
	 * It will also check the running environment.
	 * Note that it can only do basic checks,
	 * and we can't know if the config can really run a container properly.
	 */
	// Check if container directory is given.
	if (container->container_dir == NULL) {
		ruri_error("{red}Error: container directory is not set or does not exist QwQ\n");
	}
	// Refuse to use `/` for container directory.
	if (strcmp(container->container_dir, "/") == 0) {
		ruri_error("{red}Error: `/` is not allowed to use as a container directory QwQ\n");
	}
	// Check if we are running with root privileges.
	if (geteuid() != 0 && !(container->rootless)) {
		ruri_error("{red}Error: this program should be run with root privileges QwQ\n");
	}
	// rootless container should not be run with root privileges.
	if (container->rootless && (geteuid() == 0 || getuid() == 0 || getgid() == 0 || getegid() == 0)) {
		ruri_error("{red}Error: rootless container should not be run with root privileges QwQ\n");
	}
	// `--arch` and `--qemu-path` should be set at the same time.
	if ((container->cross_arch == NULL) != (container->qemu_path == NULL)) {
		ruri_error("{red}Error: --arch and --qemu-path should be set at the same time QwQ\n");
	}
}
static void parse_cgroup_settings(const char *_Nonnull str, struct RURI_CONTAINER *_Nonnull container)
{
	/*
	 * Parse and set cgroup limit.
	 * The format should be like `cpuset=1` or `memory=1M`.
	 * We will not check if the config is vaild.
	 */
	char buf[16] = { '\0' };
	char *limit = NULL;
	// Get limit type.
	for (size_t i = 0; i < 16; i++) {
		// Avoid overflow.
		if (i >= strlen(str)) {
			break;
		}
		if (str[i] == '=') {
			limit = strdup(&(str[i + 1]));
			break;
		}
		buf[i] = str[i];
		buf[i + 1] = '\0';
	}
	if (limit == NULL) {
		ruri_error("{red}Error: cgroup limit should be like `cpuset=1` or `memory=1M`\n");
	}
	if (strcmp("cpuset", buf) == 0) {
		container->cpuset = limit;
	} else if (strcmp("memory", buf) == 0) {
		container->memory = limit;
	} else if (strcmp("cpupercent", buf) == 0) {
		container->cpupercent = atoi(limit);
		if (container->cpupercent < 1 || container->cpupercent > 100) {
			ruri_error("{red}Error: cpupercent should be in range 1-100\n");
		}
	} else {
		ruri_error("{red}Unknown cgroup option %s\n", str);
	}
}
static void parse_args(int argc, char **_Nonnull argv, struct RURI_CONTAINER *_Nonnull container)
{
	/*
	 * 100% shit-code here.
	 * At least it works...
	 * It has cognitive complexity of 120+, be happy reading~
	 * If the code is hard to write,
	 * it should be hard to read nya~
	 */
	// Check if arguments are given.
	if (argc <= 1) {
		cfprintf(stderr, "{red}Error: too few arguments QwQ{clear}\n");
		ruri_show_helps();
		exit(114);
	}
	// Init configs.
	bool fork_exec = false;
	bool dump_config = false;
	char *output_path = NULL;
	cap_value_t keep_caplist_extra[CAP_LAST_CAP + 1] = { INIT_VALUE };
	cap_value_t drop_caplist_extra[CAP_LAST_CAP + 1] = { INIT_VALUE };
	cap_value_t cap = INIT_VALUE;
	bool privileged = false;
	bool use_config_file = false;
	ruri_init_config(container);
	// A very large and shit-code for() loop.
	// At least it works fine...
	for (int index = 1; index < argc; index++) {
		/**** Deprecated options. ****/
		if (strcmp(argv[index], "-K") == 0) {
			cprintf("{yellow}%s option has been deprecated.{clear}\n", argv[index]);
			exit(EXIT_SUCCESS);
		}
		if (strcmp(argv[index], "-T") == 0) {
			cprintf("{yellow}%s option has been deprecated.{clear}\n", argv[index]);
			exit(EXIT_SUCCESS);
		}
		/**** For other options ****/
		// As an easter egg.
		if (strcmp(argv[index], "AwA") == 0) {
			ruri_AwA();
			exit(EXIT_SUCCESS);
		}
		// Show version info.
		if (strcmp(argv[index], "-v") == 0 || strcmp(argv[index], "--version") == 0) {
			ruri_show_version_info();
			exit(EXIT_SUCCESS);
		}
		// Show version code, very useless right now.
		if (strcmp(argv[index], "-V") == 0 || strcmp(argv[index], "--version-code") == 0) {
			ruri_show_version_code();
			exit(EXIT_SUCCESS);
		}
		// Show help page.
		if (strcmp(argv[index], "-h") == 0 || strcmp(argv[index], "--help") == 0) {
			ruri_show_helps();
			exit(EXIT_SUCCESS);
		}
		// Show help page and example usage.
		if (strcmp(argv[index], "-H") == 0 || strcmp(argv[index], "--show-examples") == 0) {
			ruri_show_examples();
			exit(EXIT_SUCCESS);
		}
		// Show neofeth-like ruri version info.
		if (strcmp(argv[index], "-F") == 0 || strcmp(argv[index], "--ruri-fetch") == 0) {
			ruri_fetch();
			exit(EXIT_SUCCESS);
		}
		// Umount a container.
		if (strcmp(argv[index], "-U") == 0 || strcmp(argv[index], "--umount") == 0) {
			index += 1;
			struct stat st;
			if (stat(argv[index], &st) != 0) {
				ruri_error("{red}Container directory or config does not exist QwQ\n");
			}
			if (S_ISDIR(st.st_mode)) {
				char *container_dir = realpath(argv[index], NULL);
				ruri_umount_container(container_dir);
				free(container_dir);
				exit(EXIT_SUCCESS);
			} else if (S_ISREG(st.st_mode)) {
				ruri_read_config(container, argv[index]);
				ruri_umount_container(container->container_dir);
				exit(EXIT_SUCCESS);
			} else {
				ruri_error("{red}Error: unknown file type QwQ\n");
			}
			exit(114);
		}
		// Show process status of a container.
		if (strcmp(argv[index], "-P") == 0 || strcmp(argv[index], "--ps") == 0) {
			index += 1;
			struct stat st;
			if (stat(argv[index], &st) != 0) {
				ruri_error("{red}Container directory or config does not exist QwQ\n");
			}
			if (S_ISDIR(st.st_mode)) {
				char *container_dir = realpath(argv[index], NULL);
				ruri_container_ps(container_dir);
				exit(EXIT_SUCCESS);
			} else if (S_ISREG(st.st_mode)) {
				ruri_read_config(container, argv[index]);
				ruri_container_ps(container->container_dir);
				exit(EXIT_SUCCESS);
			} else {
				ruri_error("{red}Error: unknown file type QwQ\n");
			}
			exit(114);
		}
		// Correct a container config.
		if (strcmp(argv[index], "-C") == 0 || strcmp(argv[index], "--correct-config") == 0) {
			index += 1;
			if (argv[index] != NULL) {
				ruri_correct_config(argv[index]);
				exit(EXIT_SUCCESS);
			}
			exit(114);
		}
		/**** For running a container ****/
		// Just make clang-tidy happy.
		if (argv[index] == NULL) {
			ruri_error("{red}Failed to parse arguments.\n");
		}
		// Use config file.
		if (strcmp(argv[index], "-c") == 0 || strcmp(argv[index], "--config") == 0) {
			if (index == argc - 1) {
				ruri_error("{red}Please specify a config file !\n{clear}");
			}
			index++;
			ruri_read_config(container, argv[index]);
			use_config_file = true;
			index++;
		}
		// Dump config.
		if (strcmp(argv[index], "-D") == 0 || strcmp(argv[index], "--dump-config") == 0) {
			dump_config = true;
		}
		// Output file.
		else if (strcmp(argv[index], "-o") == 0 || strcmp(argv[index], "--output") == 0) {
			index++;
			if (index == argc - 1) {
				ruri_error("{red}Please specify the output file\n{clear}");
			}
			output_path = argv[index];
		}
		// Fork to exec.
		else if (strcmp(argv[index], "-f") == 0 || strcmp(argv[index], "--fork") == 0) {
			fork_exec = true;
		}
		// Set hostname.
		else if (strcmp(argv[index], "-t") == 0 || strcmp(argv[index], "--hostname") == 0) {
			if (index == argc - 1) {
				ruri_error("{red}Please specify the hostname !\n{clear}");
			}
			index++;
			container->hostname = strdup(argv[index]);
		}
		// Set no_new_privs bit.
		else if (strcmp(argv[index], "-n") == 0 || strcmp(argv[index], "--no-new-privs") == 0) {
			container->no_new_privs = true;
		}
		// Do not store .rurienv file.
		else if (strcmp(argv[index], "-N") == 0 || strcmp(argv[index], "--no-rurienv") == 0) {
			container->use_rurienv = false;
		}
		// Unmask dirs in /proc and /sys.
		else if (strcmp(argv[index], "-A") == 0 || strcmp(argv[index], "--unmask-dirs") == 0) {
			container->unmask_dirs = true;
		}
		// User.
		else if (strcmp(argv[index], "-E") == 0 || strcmp(argv[index], "--user") == 0) {
			if (index == argc - 1) {
				ruri_error("{red}Please specify the user\n{clear}");
			}
			index++;
			container->user = strdup(argv[index]);
		}
		// Simulate architecture.
		else if (strcmp(argv[index], "-a") == 0 || strcmp(argv[index], "--arch") == 0) {
			if (index == argc - 1) {
				ruri_error("{red}Please specify the arch\n{clear}");
			}
			index++;
			container->cross_arch = strdup(argv[index]);
		}
		// Path of QEMU.
		else if (strcmp(argv[index], "-q") == 0 || strcmp(argv[index], "--qemu-path") == 0) {
			index++;
			if (index == argc - 1) {
				ruri_error("{red}Please specify the path of qemu binary\n{clear}");
			}
			container->qemu_path = strdup(argv[index]);
		}
		// Enable built-in seccomp profile.
		else if (strcmp(argv[index], "-s") == 0 || strcmp(argv[index], "--enable-seccomp") == 0) {
			container->enable_seccomp = true;
		}
		// Run unshare container.
		else if (strcmp(argv[index], "-u") == 0 || strcmp(argv[index], "--unshare") == 0) {
			container->enable_unshare = true;
		}
		// Run privileged container.
		else if (strcmp(argv[index], "-p") == 0 || strcmp(argv[index], "--privileged") == 0) {
			privileged = true;
		}
		// Run rootless container.
		else if (strcmp(argv[index], "-r") == 0 || strcmp(argv[index], "--rootless") == 0) {
			container->rootless = true;
		}
		// Do not show warnings.
		else if (strcmp(argv[index], "-w") == 0 || strcmp(argv[index], "--no-warnings") == 0) {
			container->no_warnings = true;
		}
		// Just chroot.
		else if (strcmp(argv[index], "-j") == 0 || strcmp(argv[index], "--just-chroot") == 0) {
			container->just_chroot = true;
		}
		// Force bind-mount host /dev/, /sys/ and /proc/.
		else if (strcmp(argv[index], "-S") == 0 || strcmp(argv[index], "--host-runtime") == 0) {
			container->mount_host_runtime = true;
		}
		// Mount / as read-only.
		else if (strcmp(argv[index], "-R") == 0 || strcmp(argv[index], "--read-only") == 0) {
			container->ro_root = true;
		}
		// No network.
		else if (strcmp(argv[index], "-x") == 0 || strcmp(argv[index], "--no-network") == 0) {
			container->enable_unshare = true;
			container->no_network = true;
		}
		// cgroup limit.
		else if (strcmp(argv[index], "-l") == 0 || strcmp(argv[index], "--limit") == 0) {
			index++;
			if ((argv[index] != NULL)) {
				parse_cgroup_settings(argv[index], container);
			} else {
				ruri_error("{red}Unknown cgroup option\n");
			}
		}
		// Work dir.
		else if (strcmp(argv[index], "-W") == 0 || strcmp(argv[index], "--work-dir") == 0) {
			index++;
			if (index < argc) {
				container->work_dir = strdup(argv[index]);
			} else {
				ruri_error("{red}Unknown work directory\n");
			}
		}
		// Set extra env.
		else if (strcmp(argv[index], "-e") == 0 || strcmp(argv[index], "--env") == 0) {
			index++;
			if ((argv[index] != NULL) && (argv[index + 1] != NULL)) {
				for (int i = 0; i < MAX_ENVS; i++) {
					if (container->env[i] == NULL) {
						container->env[i] = strdup(argv[index]);
						index++;
						container->env[i + 1] = strdup(argv[index]);
						container->env[i + 2] = NULL;
						break;
					}
					// Max 512 envs.
					if (i == (MAX_ENVS - 1)) {
						ruri_error("{red}Too many envs QwQ\n");
					}
				}
			} else {
				ruri_error("{red}Error: unknown env QwQ\n");
			}
		}
		// Set extra mountpoints.
		else if (strcmp(argv[index], "-m") == 0 || strcmp(argv[index], "--mount") == 0) {
			index++;
			if ((argv[index] != NULL) && (argv[index + 1] != NULL)) {
				if (strcmp(argv[index], "/") == 0) {
					ruri_error("{red}/ is not allowed to use as a mountpoint QwQ\n");
				}
				for (int i = 0; i < MAX_MOUNTPOINTS; i++) {
					if (container->extra_mountpoint[i] == NULL) {
						container->extra_mountpoint[i] = realpath(argv[index], NULL);
						if (container->extra_mountpoint[i] == NULL) {
							ruri_error("{red}mountpoint does not exist QwQ\n");
						}
						index++;
						container->extra_mountpoint[i + 1] = strdup(argv[index]);
						if (strcmp(argv[index], "/") == 0) {
							free(container->extra_mountpoint[i]);
							free(container->extra_mountpoint[i + 1]);
							container->extra_mountpoint[i] = NULL;
							container->extra_mountpoint[i + 1] = NULL;
							if (container->rootfs_source == NULL) {
								container->rootfs_source = realpath(argv[index - 1], NULL);
							} else {
								ruri_error("{red}You can only mount one source to / QwQ\n");
							}
						}
						container->extra_mountpoint[i + 2] = NULL;
						break;
					}
					// Max 512 mountpoints.
					if (i == (MAX_MOUNTPOINTS - 1)) {
						ruri_error("{red}Too many mountpoints QwQ\n");
					}
				}
			} else {
				ruri_error("{red}Error: unknown mountpoint QwQ\n");
			}
		}
		// Set extra read-only mountpoints.
		else if (strcmp(argv[index], "-M") == 0 || strcmp(argv[index], "--ro-mount") == 0) {
			index++;
			if ((argv[index] != NULL) && (argv[index + 1] != NULL)) {
				for (int i = 0; i < MAX_MOUNTPOINTS; i++) {
					if (container->extra_ro_mountpoint[i] == NULL) {
						container->extra_ro_mountpoint[i] = realpath(argv[index], NULL);
						if (container->extra_ro_mountpoint[i] == NULL) {
							ruri_error("{red}mountpoint does not exist QwQ\n");
						}
						index++;
						container->extra_ro_mountpoint[i + 1] = strdup(argv[index]);
						container->extra_ro_mountpoint[i + 2] = NULL;
						if (strcmp(argv[index], "/") == 0) {
							free(container->extra_ro_mountpoint[i]);
							free(container->extra_ro_mountpoint[i + 1]);
							container->extra_ro_mountpoint[i] = NULL;
							container->extra_ro_mountpoint[i + 1] = NULL;
							if (container->rootfs_source == NULL) {
								container->rootfs_source = realpath(argv[index - 1], NULL);
								container->ro_root = true;
							} else {
								ruri_error("{red}You can only mount one source to / QwQ\n");
							}
						}
						break;
					}
					// Max 512 mountpoints.
					if (i == (MAX_MOUNTPOINTS - 1)) {
						ruri_error("{red}Too many mountpoints QwQ\n");
					}
				}
			} else {
				ruri_error("{red}Error: unknown mountpoint QwQ\n");
			}
		}
		// Extra capabilities to keep.
		else if (strcmp(argv[index], "-k") == 0 || strcmp(argv[index], "--keep") == 0) {
			index++;
			if (argv[index] != NULL) {
				// We both support capability name and number,
				// because in the fulture, there might be new capabilities that
				// we can not use the name to match it in current libcap.
				if (atoi(argv[index]) != 0) {
					ruri_add_to_caplist(keep_caplist_extra, atoi(argv[index]));
				} else if (cap_from_name(argv[index], &cap) == 0) {
					ruri_add_to_caplist(keep_caplist_extra, cap);
					ruri_log("{base}Keep capability: %s\n", argv[index]);
				} else {
					ruri_error("{red}or: unknown capability `%s`\nQwQ{clear}\n", argv[index]);
				}
			} else {
				ruri_error("{red}Missing argument\n");
			}
		}
		// Extra capabilities to drop.
		else if (strcmp(argv[index], "-d") == 0 || strcmp(argv[index], "--drop") == 0) {
			index++;
			if (argv[index] != NULL) {
				if (atoi(argv[index]) != 0) {
					ruri_add_to_caplist(drop_caplist_extra, atoi(argv[index]));
				} else if (cap_from_name(argv[index], &cap) == 0) {
					ruri_add_to_caplist(drop_caplist_extra, cap);
				} else {
					ruri_error("{red}Error: unknown capability `%s`\nQwQ{clear}\n", argv[index]);
				}
			} else {
				ruri_error("{red}Missing argument\n");
			}
		}
		// If use_config_file is true.
		// The first unrecognized argument will be treated as command to exec in container.
		else if (use_config_file) {
			// Arguments after container_dir will be read as command to exec in container.
			if (index < argc) {
				for (int i = 0; i < argc; i++) {
					if (index < argc && i < MAX_COMMANDS) {
						container->command[i] = strdup(argv[index]);
						container->command[i + 1] = NULL;
						index++;
					} else {
						break;
					}
				}
			} else {
				container->command[0] = NULL;
			}
		}
		// If use_config_file is false.
		// The first unrecognized argument will be treated as container directory.
		// If this argument is CONTAINER_DIR.
		else if (({
				 // We use a GNU extension here.
				 container->container_dir = realpath(argv[index], NULL);
				 container->container_dir;
			 }) != NULL) {
			index++;
			// Arguments after container_dir will be read as command to exec in container.
			if (index < argc) {
				for (int i = 0; i < argc; i++) {
					if (index < argc && i < MAX_COMMANDS) {
						container->command[i] = strdup(argv[index]);
						container->command[i + 1] = NULL;
						index++;
					} else {
						break;
					}
				}
			} else {
				container->command[0] = NULL;
			}
		}
		// For unknown arguments, yeah I didn't forgot it...
		else {
			ruri_show_helps();
			ruri_error("{red}Error: unknown option `%s`\nNote that only existing directory can be detected as CONTAINER_DIR\n", argv[index]);
		}
	}
	// Build the caplist to drop.
	ruri_build_caplist(container->drop_caplist, privileged, drop_caplist_extra, keep_caplist_extra);
	// Dump config.
	if (dump_config) {
		// Check if container directory is given.
		if (container->container_dir == NULL) {
			ruri_error("{red}Error: container directory is not set or does not exist QwQ\n");
		}
		// Refuse to use `/` for container directory.
		if (strcmp(container->container_dir, "/") == 0) {
			ruri_error("{red}Error: `/` is not allowed to use as a container directory QwQ\n");
		}
		char *config = ruri_container_info_to_k2v(container);
		if (output_path == NULL) {
			cprintf("%s", config);
			exit(EXIT_SUCCESS);
		}
		unlink(output_path);
		remove(output_path);
		int fd = open(output_path, O_CREAT | O_CLOEXEC | O_RDWR, S_IRUSR | S_IRGRP | S_IROTH | S_IWGRP | S_IWUSR | S_IWOTH);
		if (fd < 0) {
			ruri_error("{red}Error: failed to open output file QwQ\n");
		}
		write(fd, config, strlen(config));
		free(config);
		close(fd);
		exit(EXIT_SUCCESS);
	}
	// Enable unshare automatically if we got a ns_pid.
	pid_t ns_pid = ruri_get_ns_pid(container->container_dir);
	if (ns_pid > 0) {
		container->enable_unshare = true;
	}
	// Fork before running chroot container.
	// So the chroot container can have a parent process called ruri.
	if (fork_exec && !container->enable_unshare && !container->rootless) {
		pid_t pid = fork();
		if (pid > 0) {
			waitpid(pid, NULL, 0);
			exit(EXIT_SUCCESS);
		}
	}
}
static bool ruri_rootless_mode_detected(char *_Nonnull container_dir)
{
	struct RURI_CONTAINER *container = ruri_read_info(NULL, container_dir);
	if (container->rootless && container->ns_pid > 0) {
		free(container);
		return true;
	}
	free(container);
	return false;
}
static void detect_suid_or_capability(void)
{
	struct stat st;
	if (stat("/proc/self/exe", &st) == 0) {
		if (((st.st_mode & S_ISUID) || (st.st_mode & S_ISGID)) && (geteuid() == 0 || getegid() == 0)) {
			ruri_warning("{red}Warning: SUID or SGID bit detected on ruri, this is unsafe desu QwQ\n");
		}
	}
	cap_t caps = cap_get_file("/proc/self/exe");
	if (caps == NULL) {
		return;
	}
	char *caps_str = cap_to_text(caps, NULL);
	if (caps_str == NULL) {
		return;
	}
	if (strlen(caps_str) > 0) {
		ruri_warning("{red}Warning: capabilities detected on ruri, this is unsafe desu QwQ\n");
	}
	cap_free(caps);
	cap_free(caps_str);
}
// The real main() function.
int ruri(int argc, char **argv)
{
	// Detect SUID or capability.
	detect_suid_or_capability();
	// Exit when we get error reading configs.
	k2v_stop_at_warning = true;
	// Set process name.
	prctl(PR_SET_NAME, "ruri");
	// Catch coredump signal.
	ruri_register_signal();
// Warning for dev/debug build.
#ifdef RURI_DEBUG
	cprintf("{red}Warning: this is a dev/debug build, do not use it in production{clear}\n");
#endif
	// Info of container to run.
	struct RURI_CONTAINER *container = (struct RURI_CONTAINER *)malloc(sizeof(struct RURI_CONTAINER));
	// Parse arguments.
	parse_args(argc, argv, container);
	// Detect rootless mode.
	if (ruri_rootless_mode_detected(container->container_dir)) {
		container->rootless = true;
	}
	// Check container and the running environment.
	check_container(container);
	// unset $LD_PRELOAD.
	unsetenv("LD_PRELOAD");
	// Log.
	char *info = ruri_container_info_to_k2v(container);
	ruri_log("{base}Container config:{cyan}\n%s", info);
	free(info);
	// Run container.
	if ((container->enable_unshare) && !(container->rootless)) {
		// Unshare container.
		ruri_run_unshare_container(container);
	} else if ((container->rootless)) {
		// Rootless container.
		ruri_run_rootless_container(container);
	} else {
		// Common chroot container.
		ruri_run_chroot_container(container);
	}
	return 0;
}
//  ██╗ ██╗  ███████╗   ████╗   ███████╗
// ████████╗ ██╔════╝ ██╔═══██╗ ██╔════╝
// ╚██╔═██╔╝ █████╗   ██║   ██║ █████╗
// ████████╗ ██╔══╝   ██║   ██║ ██╔══╝
// ╚██╔═██╔╝ ███████╗ ╚██████╔╝ ██║
//  ╚═╝ ╚═╝  ╚══════╝  ╚═════╝  ╚═╝
