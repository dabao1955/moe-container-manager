<p align="center">May The Force Be With You</p>

<p align="center">(>_×)</p>         

-----------  

<p align="center">
<img src="https://stars.medv.io/dabao1955/moe-container-manager.svg", title="commits" width="50%"/>

</p>

![](https://img.shields.io/github/license/dabao1955/moe-container-manager?style=for-the-badge&color=fee4d0&logo=apache&logoColor=fee4d0)

![](https://img.shields.io/github/repo-size/dabao1955/moe-container-manager?style=for-the-badge&color=fee4d0&logo=files&logoColor=fee4d0)

![](https://img.shields.io/github/last-commit/dabao1955/moe-container-manager?style=for-the-badge&color=fee4d0&logo=codeigniter&logoColor=fee4d0)

![](https://img.shields.io/badge/language-unknown-green?style=for-the-badge&color=fee4d0&logo=sharp&logoColor=fee4d0)

![](https://img.shields.io/badge/stability-unknown-fee4d0?style=for-the-badge&color=fee4d0&logo=frontendmentor&logoColor=fee4d0)

# What is this？

container manager for chroot and proot, based on moe-hacker/termux-container

# Quick start

### WARNING:      

- It is not finished and it doesn't work right now.
- Your warranty is now void.
- I am not responsible for anything that may happen to your device by using this script.
- You do it at your own risk and take the responsibility upon yourself.


### for Debian/Ubuntu
```
sudo apt install golang libcap-dev build-essential clang libseccomp-dev lld -y
cd moe-container-manager
make
make install
```

### for Arch Linux
```
sudo pacman -Syy p7zip golang unzip zip git wget curl nano proot axel pv gawk gettext git clang make libcap libseccomp go
cd moe-container-manager
make
make install
```

### for Other Linux
install libcap,clang,golang,libseccomp and make。
```
cd moe-container-manager
make
make install
```
### build deb package
```
sudo apt install libcap-dev golang build-essential clang libseccomp-dev -y
cd moe-container-manager
dpkg-buildpackage -b -us -uc
```

### build archlinux pkgs(Experimental features)
```
cd moe-container-manager
cd tools/pkgs
python3 makepkg.py
```
# Usage:     
See `container -h` and `help` in container console.


# License

This project follows the Apache-2.0 open source license agreement, and its sub-projects adopt its original agreement.

[![FOSSA Status](https://app.fossa.com/api/projects/git%2Bgithub.com%2Fdabao1955%2Fmoe-container-manager.svg?type=large)](https://app.fossa.com/projects/git%2Bgithub.com%2Fdabao1955%2Fmoe-container-manager?ref=badge_large)
