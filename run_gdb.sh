#!/bin/bash

qemu-system-x86_64 -append nokaslr \
-kernel /home/xucheng/Downloads/test_kernel/linux-4.18.5/arch/x86/boot/bzImage \
-initrd /home/xucheng/Downloads/test_kernel/initramfs_mnt.img -S -s
