#!/bin/bash

qemu-system-x86_64 -kernel /home/xucheeng/Downloads/os/linux-4.18.5/arch/x86/boot/bzImage \
-initrd /home/xucheeng/Downloads/os/initramfs_mnt.img
