<p align="center">May The Force Be With You</p>

<p align="center">(>_×)</p>         

-----------  

<p align="center">
<img src="https://stars.medv.io/dabao1954/moe-container-manager.svg", title="commits" width="50%"/>

</p>
![](https://img.shields.io/github/license/dabao1955/moe-container-manager?style=for-the-badge&color=fee4d0&logo=apache&logoColor=fee4d0)

![](https://img.shields.io/github/repo-size/dabao1955/moe-container-manager?style=for-the-badge&color=fee4d0&logo=files&logoColor=fee4d0)

![](https://img.shields.io/github/last-commit/dabao1955/moe-container-manager?style=for-the-badge&color=fee4d0&logo=codeigniter&logoColor=fee4d0)

![](https://img.shields.io/badge/language-shell\&c-green?style=for-the-badge&color=fee4d0&logo=sharp&logoColor=fee4d0)


# What is this？
container manager for chroot and proot, based on moe-hacker/termux-container
# Quick start

### WARNING:      

- It is not finished and something is broken.(such as proot)
- Your warranty is now void.
- I am not responsible for anything that may happen to your device by using this script.
- You do it at your own risk and take the responsibility upon yourself.


### for Debian/Ubuntu
```
sudo apt install libcap-dev build-essential clang -y
cd moe-container-manager
make
make install
```

### for Arch Linux
```
sudo pacman -Syy p7zip unzip zip git wget curl nano proot axel pv gawk gettext git clang make libcap
cd moe-container-manager
make
make install
```

### for Other Linux
install libcap,clang and make。
```
cd moe-container-manager
make
make install
```
### build deb package
```
sudo apt install libcap-dev build-essential clang -y
cd moe-container-manager
dpkg-buildpackage -b -us -uc
```

### build archlinux pkgs(Experimental features)
```
sudo pacman -Syy p7zip unzip zip git wget curl nano proot axel pv gawk gettext git clang make libcap
cd moe-container-manager
makepkg
```
# Usage:     
See `container -h` and `help` in container console.
