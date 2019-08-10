BASEINCLUDE ?= /home/xucheeng/Downloads/os/linux-4.18.5

testkthread-objs := test_kthread.o 

obj-m	:=   testkthread.o
all : 
	$(MAKE) -C $(BASEINCLUDE) M=$(PWD) modules;

clean:
	$(MAKE) -C $(BASEINCLUDE) SUBDIRS=$(PWD) clean;
	rm -f *.ko;


