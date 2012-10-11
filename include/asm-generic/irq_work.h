#ifndef __ASM_GENERIC_ATOMIC_H
#define __ASM_GENERIC_ATOMIC_H

/*
 * Lame architectures will get the timer tick callback
 */
static inline void arch_irq_work_raise(void) { }

#endif
