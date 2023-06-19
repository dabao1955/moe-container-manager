<p align="center">May The Force Be With You</p>

<p align="center">(>_×)</p>         

-----------  

<p align="center">

    <img src="https://stars.medv.io/dabao1954/moe-container-manager.svg", title="commits" width="50%"/>

</p>
![](https://img.shields.io/github/license/dabao1955/moe-container-manager?style=for-the-badge&color=fee4d0&logo=apache&logoColor=fee4d0)

![](https://img.shields.io/github/repo-size/dabao1955/moe-container-manager?style=for-the-badge&color=fee4d0&logo=files&logoColor=fee4d0)

![](https://img.shields.io/github/last-commit/dabao1955/moe-containermamager?style=for-the-badge&color=fee4d0&logo=codeigniter&logoColor=fee4d0)

![](https://img.shields.io/badge/language-shell\&c-green?style=for-the-badge&color=fee4d0&logo=sharp&logoColor=fee4d0)


# What is this？
container manager for chroot and proot, based on moe-hacker/termux-container
# Quick start

### for Debian/Ubuntu
```
sudo apt install libcap-dev build-essential clang -y
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
