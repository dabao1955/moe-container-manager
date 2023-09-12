# Maintainer: dabao1955 <dabao1955@163.com>

pkgname=moe-container-manager

pkgver=0.0.1

pkgrel=1

pkgdesc="container manager for proot and chroot"

arch=(any)

url="https://github.com/dabao1955/moe-container-manager"

license=('Apache-2.0')

depends=(golang p7zip unzip zip git wget curl nano proot axel pv gawk gettext)

makedepends=(git clang make libcap)

source=(https://github.com/dabao1955/moe-container-manager/archive/refs/heads/main.zip)

noextract=()

md5sums=('SKIP')

build() {

  cd "$pkgname"

  make

}

package() {

  cd "$pkgname"

  make DESTDIR="$pkgdir/" 

  make DESTDIR="$pkgdir/" install

}
