#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/slickos.kernel isodir/boot/slickos.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "slickos" {
	multiboot /boot/slickos.kernel
}
EOF
grub-mkrescue -o slickos.iso isodir
