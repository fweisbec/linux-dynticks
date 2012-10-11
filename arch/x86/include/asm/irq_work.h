#ifndef _ASM_X86_IRQ_WORK_H
#define _ASM_X86_IRQ_WORK_H

#ifndef CONFIG_X86_LOCAL_APIC
#include <asm-generic/irq_work.h>
# else
extern void arch_irq_work_raise(void);
#endif

#endif
