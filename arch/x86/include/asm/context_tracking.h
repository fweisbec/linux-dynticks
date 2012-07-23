#ifndef _ASM_X86_CONTEXT_TRACKING_H
#define _ASM_X86_CONTEXT_TRACKING_H

#include <linux/context_tracking.h>
#include <asm/ptrace.h>

static inline void exception_enter(struct pt_regs *regs)
{
	user_exit();
}

static inline void exception_exit(struct pt_regs *regs)
{
#ifdef CONFIG_CONTEXT_TRACKING
	if (user_mode(regs))
		user_enter();
#endif
}

#endif
