1. ����Linux�ں�
cd /home/xucheng/Downloads/test_kernel/linux-4.18.5
make defconfig
make

/bin/sh: bison: command not found
yum install bison

/bin/sh: flex: command not found
yum install flex

scripts/kconfig/conf  --syncconfig Kconfig
Makefile:936: *** "Cannot generate ORC metadata for CONFIG_UNWINDER_ORC=y, please install libelf-dev, libelf-devel or elfutils-libelf-devel".  Stop.
yum install elfutils-libelf-devel


scripts/extract-cert.c:21:25: fatal error: openssl/bio.h: No such file or directory
 #include <openssl/bio.h>
                         ^
compilation terminated.
make[1]: *** [scripts/extract-cert] Error 1
make: *** [scripts] Error 2

yum install openssl-devel


2. ���밲װqemu
/home/xucheng/Downloads/test_kernel/qemu-2.11.1
./configure
make -j4


ERROR: glib-2.22 gthread-2.0 is required to compile QEMU
yum install gtk2-devel 


3. ����debug�汾
[root@oracledb linux-4.18.5]# make menuconfig
*
* Unable to find the ncurses package.
* Install ncurses (ncurses-devel or libncurses-dev
* depending on your distribution).
*
make[1]: *** [scripts/kconfig/.mconf-cfg] Error 1
make: *** [menuconfig] Error 2
[root@oracledb linux-4.18.5]# yum install -y ncurses-devel

make menuconfig
����ѡ��kernel hackingѡ������Ժ����ѡ��compile-time checks and compile options�� Ȼ��ѡ��compile the kernel with debug info

��һ�ε�drive�ᱨ��
make -j8

�ڶ��������ϴ�LinuxԴ���ٱ���ɹ� 429M Aug 23 16:38 vmlinux
make bzImage -j4

gdb�޷���ס�����𣨳ɹ���
https://www.zhihu.com/question/270476360


gdb /usr/src/linux-4.6.2/vmlinux (�޸ĳ��Լ���vmlinux·��)

target remote:1234 (Ĭ�϶˿���1234������Զ������)

b start_kernel (���öϵ�)

c (continue ���е��ϵ㴦)





















