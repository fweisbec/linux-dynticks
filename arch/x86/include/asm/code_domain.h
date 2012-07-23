#ifndef _ASM_X86_CODE_DOMAIN_H
#define _ASM_X86_CODE_DOMAIN_H

#include <linux/code_domain.h>
#include <asm/ptrace.h>

static inline void exception_enter(struct pt_regs *regs)
{
	user_exit();
}

static inline void exception_exit(struct pt_regs *regs)
{
#ifdef CONFIG_CODE_DOMAIN_TRACKING
	if (user_mode(regs))
		user_enter();
#endif
}

#endif
