#include <linux/user_hooks.h>
#include <linux/rcupdate.h>
#include <linux/sched.h>
#include <linux/kernel_stat.h>


DEFINE_PER_CPU(struct user_hooks, user_hooks) = {
#ifdef CONFIG_USER_HOOKS_FORCE
	.hooking = true,
#endif
};

void user_enter(void)
{
	unsigned long flags;
	struct user_hooks *uh;

	WARN_ON_ONCE(!current->mm);
	local_irq_save(flags);
	uh = &__get_cpu_var(user_hooks);
	if (uh->hooking && !uh->in_user) {
		uh->in_user = true;
		if (accounting_vtime())
			account_system_vtime(current);
		rcu_user_enter();
	}
	local_irq_restore(flags);
}

void user_exit(void)
{
	unsigned long flags;
	struct user_hooks *uh;

	local_irq_save(flags);
	uh = &__get_cpu_var(user_hooks);
	if (uh->in_user) {
		uh->in_user = false;
		rcu_user_exit();
		if (accounting_vtime())
			account_user_vtime(current);
	}
	local_irq_restore(flags);
}

void user_hooks_switch(struct task_struct *prev,
		       struct task_struct *next)
{
	struct user_hooks *uh;

	uh = &__get_cpu_var(user_hooks);
	if (uh->hooking) {
		clear_tsk_thread_flag(prev, TIF_NOHZ);
		set_tsk_thread_flag(next, TIF_NOHZ);
	}
}
