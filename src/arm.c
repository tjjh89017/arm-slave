#include "arm.h"
#include "type.h"
#include "memlayout.h"

void cli()
{
	uint v;
	// disable interrupt IRQ, but not FIQ, still allow FIQ
	asm("mrs %[v], cpsr" : [v]"=r"(v) : :);
	v |= DIS_INT;
	asm("msr cpsr_cxsf, %[v]" : :[v]"r"(v) :);
}

void sti()
{
	uint v;

	// enable interrupt IRQ, FIQ still
	asm("mrs %[v], cpsr" : [v]"=r"(v) : :);
	v &= ~DIS_INT;
	asm("msr cpsr_cxsf, %[v]" : : [v]"r"(v) :);
}
