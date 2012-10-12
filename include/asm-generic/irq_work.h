#ifndef __ASM_GENERIC_ATOMIC_H
#define __ASM_GENERIC_ATOMIC_H

/*
 * Lame architectures will get the timer tick callback
 */
#ifndef arch_irq_work_raise
static inline void arch_irq_work_raise(void) { }
#endif

/*
 * Unless told otherwise, consider the arch implements irq work
 * through a hook to the timer tick.
 */
#ifndef arch_irq_work_use_tick
static inline bool arch_irq_work_use_tick(void)
{
	return true;
}
#endif

#endif
