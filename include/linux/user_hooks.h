#ifndef _LINUX_USER_HOOKS_H
#define _LINUX_USER_HOOKS_H

#ifdef CONFIG_USER_HOOKS
#include <linux/sched.h>

extern void user_enter(void);
extern void user_exit(void);
extern void user_hooks_switch(struct task_struct *prev,
			      struct task_struct *next);
#else
static inline void user_enter(void) { }
static inline void user_exit(void) { }
static inline void user_hooks_switch(struct task_struct *prev,
				     struct task_struct *next) { }
#endif /* !CONFIG_USER_HOOKS */

#endif
