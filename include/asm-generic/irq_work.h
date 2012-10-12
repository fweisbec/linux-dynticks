#ifndef __ASM_GENERIC_ATOMIC_H
#define __ASM_GENERIC_ATOMIC_H

/*
 * Lame architectures will get the timer tick callback
 */
#ifndef arch_irq_work_raise
static inline void arch_irq_work_raise(void) { }
#endif

/*
 * Unless told otherwise, consider the arch doesn't implement irq work
 * using self IPIs but through another way like defaulting to the hook
 * on the sched tick.
 */
#ifndef arch_irq_work_has_ipi
static inline bool arch_irq_work_has_ipi(void)
{
	return false;
}
#endif

#endif
