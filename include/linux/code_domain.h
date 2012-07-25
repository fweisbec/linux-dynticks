#ifndef _LINUX_CODE_DOMAIN_TRACKING_H
#define _LINUX_CODE_DOMAIN_TRACKING_H

#ifdef CONFIG_CODE_DOMAIN_TRACKING
#include <linux/sched.h>

struct code_domain_tracking {
	/*
	 * When tracking_active is false, hooks are not
	 * set to minimize overhead: TIF flags are cleared
	 * and calls to user_enter/exit are ignored. This
	 * may be further optimized using static keys.
	 */
	bool tracking_active;
	enum {
		IN_KERNEL = 0,
		IN_USER,
	} state;
};

DECLARE_PER_CPU(struct code_domain_tracking, code_domain);

static inline bool code_domain_in_user(void)
{
	return __this_cpu_read(code_domain.state) == IN_USER;
}

static inline bool code_domain_tracking_active(void)
{
	return __this_cpu_read(code_domain.tracking_active);
}

extern void user_enter(void);
extern void user_exit(void);
extern void code_domain_task_switch(struct task_struct *prev,
				    struct task_struct *next);
#else
static inline void user_enter(void) { }
static inline void user_exit(void) { }
static inline void code_domain_task_switch(struct task_struct *prev,
					   struct task_struct *next) { }
#endif /* !CONFIG_CODE_DOMAIN_TRACKING */

#endif
