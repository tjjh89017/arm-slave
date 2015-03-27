#include "arm.h"
#include "type.h"
#include "proc.h"
#include "memlayout.h"
#include "mmu.h"

// TODO fix it, find a better place
#define NCPU 4
struct cpu cpus[NCPU];
struct cpu *cpu;

void kmain()
{
	cpu = &cpus[0];

	volatile uint8 *uart0 = (uint8)(UART0 + KERNEL_BASE);
	*uart0 = 'k';

}
