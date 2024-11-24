# About rurienv:
.rurienv is a config file in container, to make it safe, it's immutable by default, and as container do not have cap_linux_immutable by default, you are not able to edit or remove it in container unless you use `-k cap_linux_immutable` or `-p` to run container.      
It will record the following config:      
* The capabilty to drop.
* Set NO_NEW_PRIVS bit.
* Enable built-in seccomp profile.
* PID owning unshare namespace.
* Container ID.
* Just chroot, do not create runtime dirs.
* Work directory.
* Do not show warnings.
* User to run the container.
* Extra mountpoint.
* Extra read-only mountpoint.
* Environment variable.
# Its behavior:
1. Cover drop_caplist, no_new_privs, enable_seccomp, no_warnings as the config first time when init container. This can only be disabled if you don't use .rurienv file. If you want to change one of these config,you should use -U to unmount container and restart it with new args/configs.           
2. Cover user and work_dir settings if they are not set in cmdline arguments.      
3. Store container_id to set the container process into the same cgroup.      
4. Store ns_pid to make sure unshare container in the same namespace. If ruri detected ns_pid, it will automatically enable unshare and join the namespace.            
5. Store extra_mountpoint and extra_ro_mountpoint for umount container.      