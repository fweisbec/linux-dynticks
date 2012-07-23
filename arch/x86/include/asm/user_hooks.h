#ifndef _ASM_X86_USER_HOOKS_H
#define _ASM_X86_USER_HOOKS_H

#include <linux/user_hooks.h>
#include <asm/ptrace.h>

static inline void exception_enter(struct pt_regs *regs)
{
	user_exit();
}

static inline void exception_exit(struct pt_regs *regs)
{
#ifdef CONFIG_USER_HOOKS
	if (user_mode(regs))
		user_enter();
#endif
}

#endif
