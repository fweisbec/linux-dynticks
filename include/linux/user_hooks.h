#ifndef _LINUX_USER_HOOKS_H
#define _LINUX_USER_HOOKS_H

#ifdef CONFIG_USER_HOOKS
#include <linux/sched.h>
#include <linux/percpu.h>

struct user_hooks {
	bool hooking;
	bool in_user;
};

DECLARE_PER_CPU(struct user_hooks, user_hooks);

static inline bool in_user(void)
{
	return __get_cpu_var(user_hooks).in_user;
}

static inline bool user_hooks_hooking(void)
{
	return __get_cpu_var(user_hooks).hooking;
}

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
