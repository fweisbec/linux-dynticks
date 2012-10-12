#ifndef _ASM_X86_IRQ_WORK_H
#define _ASM_X86_IRQ_WORK_H

#ifdef CONFIG_X86_LOCAL_APIC
extern void __arch_irq_work_raise(void);
#define arch_irq_work_raise __arch_irq_work_raise
#endif

#include <asm-generic/irq_work.h>

#endif
