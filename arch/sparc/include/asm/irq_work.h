#ifndef ___ASM_SPARC_IRQ_H
#define ___ASM_SPARC_IRQ_H

extern void __arch_irq_work_raise(void);
#define arch_irq_work_raise __arch_irq_work_raise

#include <asm-generic/irq_work.h>
#endif
