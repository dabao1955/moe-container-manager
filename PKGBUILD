# Maintainer: dabao1955 <dabao1955@163.com>

pkgname=moe-container-mamager

pkgver=0.0.1

pkgrel=1

pkgdesc=""

arch=(any)

url="https://github.com/dabao1955/moe-container-manager"

license=('Apache-2.0')

groups=()

depends=()

makedepends=()

optdepends=()

provides=()

conflicts=()

replaces=()

backup=()

options=()

install=

changelog=

source=($pkgname-$pkgver.tar.gz)

noextract=()

md5sums=() #autofill using updpkgsums

build() {

  cd "$pkgname-$pkgver"

  ./configure --prefix=/usr

  make

}

package() {

  cd "$pkgname-$pkgver"

  make DESTDIR="$pkgdir/" install

}
