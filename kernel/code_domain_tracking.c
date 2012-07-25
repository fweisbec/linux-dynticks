#include <linux/code_domain.h>
#include <linux/rcupdate.h>
#include <linux/sched.h>
#include <linux/kernel_stat.h>

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
		if (accounting_vtime())
			account_system_vtime(current);
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
		if (accounting_vtime())
			account_user_vtime(current);
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
