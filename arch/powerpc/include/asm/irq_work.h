#ifndef _ASM_POWERPC_IRQ_WORK_H
#define _ASM_POWERPC_IRQ_WORK_H

extern void __arch_irq_work_raise(void);
#define arch_irq_work_raise __arch_irq_work_raise

#include <asm-generic/irq_work.h>
#endif
