BASEINCLUDE ?= /home/xucheeng/Downloads/os/linux-4.18.5

mytest-objs := my_test.o 

obj-m	:=   mytest.o
all : 
	$(MAKE) -C $(BASEINCLUDE) M=$(PWD) modules;
	cp mytest.ko /home/xucheeng/Downloads/os/ramdisk/mnt
	cd /home/xucheeng/Downloads/os/ramdisk \
		&& find . -print0 | cpio --null -ov --format=newc | gzip -9 > ../initramfs_mnt.img
clean:
	$(MAKE) -C $(BASEINCLUDE) SUBDIRS=$(PWD) clean;
	rm -f *.ko;


