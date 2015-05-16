#include "arm.h"
#include "type.h"
#include "proc.h"
#include "memlayout.h"
#include "mmu.h"
#include "device/versatile_pb.h"

// TODO fix it, find a better place
#define NCPU 4
struct cpu cpus[NCPU];
struct cpu *cpu;

extern void *end;

void kmain()
{
	UART0_puts("\nkmain:\n\n");
	cpu = &cpus[0];

	UART0_puts("init_vm\n");
	init_vm();

	UART0_puts("kernel_mem_freerange\n");
	uint vector_table = phys_to_virt_wo(VECTOR_TABLE & PGD_MASK);
	kernel_mem_freerange(align_up(&end, PTE_SIZE), vector_table);
	kernel_mem_freerange(vector_table + PTE_SIZE, phys_to_virt_wo(INIT_KERNEL_MAP));

	UART0_puts("end\n");
}
