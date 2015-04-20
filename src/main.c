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

void kmain()
{
	UART0_puts("kmain:\n");
	cpu = &cpus[0];

	pushcli();
	popcli();
}
