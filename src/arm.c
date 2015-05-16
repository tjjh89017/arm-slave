#include "arm.h"
#include "type.h"
#include "memlayout.h"
#include "proc.h"

// TODO fix it
extern struct cpu *cpu;

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

int interrupt_enabled()
{
	int v;
	asm("mrs %[v], cpsr" : [v]"=r"(v) : :);

	return !(v & DIS_INT);
}

void pushcli()
{
	int enabled = interrupt_enabled();

	cli();

	// TODO now we only support 1 cpu, we have to support multi-core
	if(cpu->ncli++ == 0){
		cpu->intena = enabled;
	}
}

void popcli()
{
	if(interrupt_enabled()){
		// TODO need an error msg or Kernel panic output
	}

	// TODO support multi-core
	if(--cpu->ncli < 0){
		// TODO need panic
	}

	if(cpu->ncli == 0 && cpu->intena){
		sti();
	}
}
