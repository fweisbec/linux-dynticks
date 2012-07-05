#ifdef CONFIG_RCU_USER_QS
# define ENTER_KERNEL callq rcu_user_exit
# define EXIT_KERNEL callq rcu_user_enter
#else
# define ENTER_KERNEL
# define EXIT_KERNEL
#endif
