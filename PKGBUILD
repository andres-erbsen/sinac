# $Id: pkgbuild-mode.el,v 1.23 2007/10/20 16:02:14 juergen Exp $
# Maintainer: Andres Erbsen <andres.erbsen@gmail.com>
pkgname=sinac
pkgver=0.2.0
pkgrel=1
pkgdesc="A cleaner/simpler alternative to xautolock for screen locking."
url="http://www.suckless.org/pipermail/dwm/2007-December/004691.html"
arch=('i686' 'x86_64')
license=('GPL')
depends=(libxss)
makedepends=(xproto scrnsaverproto)
source=(sinac.c)
md5sums=('f5438636a1c40e2384485ef26d575960')

build() {
  cd $srcdir
  gcc -O3 sinac.c -lX11 -lXss -lXext -o sinac
  install -d $pkgdir/usr/bin/
  install sinac $pkgdir/usr/bin/
}
