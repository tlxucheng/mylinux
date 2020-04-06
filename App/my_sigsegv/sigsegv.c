#ifndef _GNU_SOURCE
	#define _GNU_SOURCE
#endif
#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <ucontext.h>

struct user_regs_struct {
	unsigned long	r15;
	unsigned long	r14;
	unsigned long	r13;
	unsigned long	r12;
	unsigned long	bp;
	unsigned long	bx;
	unsigned long	r11;
	unsigned long	r10;
	unsigned long	r9;
	unsigned long	r8;
	unsigned long	ax;
	unsigned long	cx;
	unsigned long	dx;
	unsigned long	si;
	unsigned long	di;
	unsigned long	orig_ax;
	unsigned long	ip;
	unsigned long	cs;
	unsigned long	flags;
	unsigned long	sp;
	unsigned long	ss;
	unsigned long	fs_base;
	unsigned long	gs_base;
	unsigned long	ds;
	unsigned long	es;
	unsigned long	fs;
	unsigned long	gs;
};

#define ELF_NGREG (sizeof(struct user_regs_struct) / sizeof(long))


/* 纯C环境下，定义宏NO_CPP_DEMANGLE */
#if (!defined(__cplusplus)) && (!defined(NO_CPP_DEMANGLE))
# define NO_CPP_DEMANGLE
#endif

#ifndef NO_CPP_DEMANGLE
# include <cxxabi.h>
# ifdef __cplusplus
	using __cxxabiv1::__cxa_demangle;
# endif
#endif

#if (defined HAS_ULSLIB)
# include <uls/logger.h>
# define sigsegv_outp(x)	sigsegv_outp(, gx)
#else
# define sigsegv_outp(x, ...) 	fprintf(stderr, x"\n", ##__VA_ARGS__)
#endif

#if (defined (__x86_64__))
# define REGFORMAT   "%016llx"	
#elif (defined (__i386__))
# define REGFORMAT   "%08x"
#elif (defined (__arm__))
# define REGFORMAT   "%lx"
#endif

static void print_reg(const ucontext_t *uc) 
{
#if (defined (__x86_64__)) || (defined (__i386__))
	int i;
	for (i = 0; i < NGREG; i++) {
		sigsegv_outp("reg[%02d]: 0x"REGFORMAT, i, uc->uc_mcontext.gregs[i]);
	}

#elif (defined (__arm__))
	sigsegv_outp("reg[%02d]		= 0x"REGFORMAT, 0, uc->uc_mcontext.arm_r0);
	sigsegv_outp("reg[%02d]		= 0x"REGFORMAT, 1, uc->uc_mcontext.arm_r1);
	sigsegv_outp("reg[%02d]		= 0x"REGFORMAT, 2, uc->uc_mcontext.arm_r2);
	sigsegv_outp("reg[%02d]		= 0x"REGFORMAT, 3, uc->uc_mcontext.arm_r3);
	sigsegv_outp("reg[%02d]		= 0x"REGFORMAT, 4, uc->uc_mcontext.arm_r4);
	sigsegv_outp("reg[%02d]		= 0x"REGFORMAT, 5, uc->uc_mcontext.arm_r5);
	sigsegv_outp("reg[%02d]		= 0x"REGFORMAT, 6, uc->uc_mcontext.arm_r6);
	sigsegv_outp("reg[%02d]		= 0x"REGFORMAT, 7, uc->uc_mcontext.arm_r7);
	sigsegv_outp("reg[%02d]		= 0x"REGFORMAT, 8, uc->uc_mcontext.arm_r8);
	sigsegv_outp("reg[%02d]		= 0x"REGFORMAT, 9, uc->uc_mcontext.arm_r9);
	sigsegv_outp("reg[%02d]		= 0x"REGFORMAT, 10, uc->uc_mcontext.arm_r10);
	sigsegv_outp("FP		= 0x"REGFORMAT, uc->uc_mcontext.arm_fp);
	sigsegv_outp("IP		= 0x"REGFORMAT, uc->uc_mcontext.arm_ip);
	sigsegv_outp("SP		= 0x"REGFORMAT, uc->uc_mcontext.arm_sp);
	sigsegv_outp("LR		= 0x"REGFORMAT, uc->uc_mcontext.arm_lr);
	sigsegv_outp("PC		= 0x"REGFORMAT, uc->uc_mcontext.arm_pc);
	sigsegv_outp("CPSR		= 0x"REGFORMAT, uc->uc_mcontext.arm_cpsr);
	sigsegv_outp("Fault Address	= 0x"REGFORMAT, uc->uc_mcontext.fault_address);
	sigsegv_outp("Trap no		= 0x"REGFORMAT, uc->uc_mcontext.trap_no);
	sigsegv_outp("Err Code	= 0x"REGFORMAT, uc->uc_mcontext.error_code);
	sigsegv_outp("Old Mask	= 0x"REGFORMAT, uc->uc_mcontext.oldmask);
#endif
}

static void print_reg_by_name(const ucontext_t *uc)
{
    sigsegv_outp("reg[%02d_REG_RIP]: 0x"REGFORMAT, REG_RIP, uc->uc_mcontext.gregs[REG_RIP]);

    sigsegv_outp("reg[%02d_REG_RAX]: 0x"REGFORMAT, REG_RAX, uc->uc_mcontext.gregs[REG_RAX]);
    sigsegv_outp("reg[%02d_REG_RBX]: 0x"REGFORMAT, REG_RBX, uc->uc_mcontext.gregs[REG_RBX]);
    sigsegv_outp("reg[%02d_REG_RCX]: 0x"REGFORMAT, REG_RCX, uc->uc_mcontext.gregs[REG_RCX]);
    sigsegv_outp("reg[REG_RDX]: 0x"REGFORMAT, uc->uc_mcontext.gregs[REG_RDX]);
    sigsegv_outp("reg[REG_RSP]: 0x"REGFORMAT, uc->uc_mcontext.gregs[REG_RSP]);
    sigsegv_outp("reg[REG_RBP]: 0x"REGFORMAT, uc->uc_mcontext.gregs[REG_RBP]);
    sigsegv_outp("reg[REG_RSI]: 0x"REGFORMAT, uc->uc_mcontext.gregs[REG_RSI]);
    sigsegv_outp("reg[REG_R8]: 0x"REGFORMAT, uc->uc_mcontext.gregs[REG_R8]);
    sigsegv_outp("reg[REG_R9]: 0x"REGFORMAT, uc->uc_mcontext.gregs[REG_R9]);
    sigsegv_outp("reg[REG_R10]: 0x"REGFORMAT, uc->uc_mcontext.gregs[REG_R10]);
    sigsegv_outp("reg[REG_R11]: 0x"REGFORMAT, uc->uc_mcontext.gregs[REG_R11]);
    sigsegv_outp("reg[REG_R12]: 0x"REGFORMAT, uc->uc_mcontext.gregs[REG_R12]);
    sigsegv_outp("reg[REG_R13]: 0x"REGFORMAT, uc->uc_mcontext.gregs[REG_R13]);
    sigsegv_outp("reg[REG_R14]: 0x"REGFORMAT, uc->uc_mcontext.gregs[REG_R14]);
    sigsegv_outp("reg[REG_R15]: 0x"REGFORMAT, uc->uc_mcontext.gregs[REG_R15]);

    return;
}

static void print_call_link(const ucontext_t *uc) 
{
	int i = 0;
	Dl_info	dl_info;

#if (defined (__i386__))
	const void **frame_pointer = (const void **)uc->uc_mcontext.gregs[REG_EBP];
	const void *return_address = (const void *)uc->uc_mcontext.gregs[REG_EIP];
#elif (defined (__x86_64__))
	const void **frame_pointer = (const void **)uc->uc_mcontext.gregs[REG_RBP];
	const void *return_address = (const void *)uc->uc_mcontext.gregs[REG_RIP];
#elif (defined (__arm__))
/* sigcontext_t on ARM:
        unsigned long trap_no;
        unsigned long error_code;
        unsigned long oldmask;
        unsigned long arm_r0;
        ...
        unsigned long arm_r10;
        unsigned long arm_fp;
        unsigned long arm_ip;
        unsigned long arm_sp;
        unsigned long arm_lr;
        unsigned long arm_pc;
        unsigned long arm_cpsr;
        unsigned long fault_address;
*/
	const void **frame_pointer = (const void **)uc->uc_mcontext.arm_fp;
	const void *return_address = (const void *)uc->uc_mcontext.arm_pc;
#endif

	sigsegv_outp("\nStack trace:");
	while (return_address) {
		memset(&dl_info, 0, sizeof(Dl_info));
		if (!dladdr((void *)return_address, &dl_info))	break;
		const char *sname = dl_info.dli_sname;	
#if (!defined NO_CPP_DEMANGLE)
		int status;
		char *tmp = __cxa_demangle(sname, NULL, 0, &status);
		if (status == 0 && tmp) {
			sname = tmp;
		}
#endif
		/* No: return address <sym-name + offset> (filename) */
		sigsegv_outp("%02d: %p <%s + %lu> (%s)", ++i, return_address, sname, 
			(unsigned long)return_address - (unsigned long)dl_info.dli_saddr, 
													dl_info.dli_fname);
                char cmd[128] = {0};
                memset(cmd, 0x0, sizeof(cmd));
                snprintf(cmd, sizeof(cmd), "addr2line -e sigsegv %p", return_address);
                system(cmd);
#if (!defined NO_CPP_DEMANGLE)
		if (tmp)	free(tmp);
#endif
		if (dl_info.dli_sname && !strcmp(dl_info.dli_sname, "main")) break;

		if (!frame_pointer)	break;
#if (defined (__x86_64__)) || (defined (__i386__))
		return_address = frame_pointer[1];
		frame_pointer = (const void **)frame_pointer[0];
#elif (defined (__arm__))
		return_address = frame_pointer[-1];	
		frame_pointer = (const void **)frame_pointer[-3];
#endif
	}
	sigsegv_outp("Stack trace end.");
}

static void sigsegv_handler(int signo, siginfo_t *info, void *context)
{
	sigsegv_outp("Segmentation Fault!");
	sigsegv_outp("info.si_signo = %d", signo);
	if (info) {
		sigsegv_outp("info.si_errno = %d", info->si_errno);
		sigsegv_outp("info.si_code  = %d (%s)", info->si_code, 
			(info->si_code == SEGV_MAPERR) ? "SEGV_MAPERR" : "SEGV_ACCERR");
		sigsegv_outp("info.si_addr  = %p\n", info->si_addr);
	}

	if (context) {
		const ucontext_t *uc = (const ucontext_t *)context;

		print_reg(uc);
		print_reg_by_name(uc);
		print_call_link(uc);
	}

        signal(SIGSEGV, SIG_DFL);
	//_exit(0);
}

#define SETSIG(sa, signo, func, flags)	\
        do {                            \
            sa.sa_sigaction = func;  	\
            sa.sa_flags = flags;        \
            sigemptyset(&sa.sa_mask);   \
            sigaction(signo, &sa, NULL);\
        } while(0)


static void __attribute((constructor)) setup_sigsegv(void) 
{
	struct sigaction sa;

	SETSIG(sa, SIGSEGV, sigsegv_handler, SA_SIGINFO); 
}


#if 1
void func3(void)
{
	char *p = (char *)0x12345678;
	*p = 10;
}

void func2(void)
{
	func3();	
}

void func1(void)
{
	func2();
}

int main(int argc, const char *argv[])
{
    printf("%ld\n", ELF_NGREG);    

    func1();	
    exit(EXIT_SUCCESS);
}
#endif
