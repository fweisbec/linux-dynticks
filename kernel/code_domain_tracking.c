#include <linux/code_domain.h>
#include <linux/rcupdate.h>
#include <linux/sched.h>
#include <linux/percpu.h>

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

DEFINE_PER_CPU(struct code_domain_tracking, code_domain) = {
#ifdef CONFIG_CODE_DOMAIN_TRACKING_FORCE
	.tracking_active = true,
#endif
};

void user_enter(void)
{
	unsigned long flags;

	WARN_ON_ONCE(!current->mm);
	local_irq_save(flags);
	if (__this_cpu_read(code_domain.tracking_active) &&
	    __this_cpu_read(code_domain.state) != IN_USER) {
		__this_cpu_write(code_domain.state, IN_USER);
		rcu_user_enter();
	}
	local_irq_restore(flags);
}

void user_exit(void)
{
	unsigned long flags;

	local_irq_save(flags);
	if (__this_cpu_read(code_domain.state) == IN_USER) {
		__this_cpu_write(code_domain.state, IN_KERNEL);
		rcu_user_exit();
	}
	local_irq_restore(flags);
}

void code_domain_task_switch(struct task_struct *prev,
			     struct task_struct *next)
{
	if (__this_cpu_read(code_domain.tracking_active)) {
		clear_tsk_thread_flag(prev, TIF_NOHZ);
		set_tsk_thread_flag(next, TIF_NOHZ);
	}
}
