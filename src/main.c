#include "arm.h"
#include "type.h"
#include "proc.h"
#include "memlayout.h"
#include "mmu.h"

// TODO fix it, find a better place
#define NCPU 4
struct cpu cpus[NCPU];
struct *cpu;

void kmain()
{
	cpu = &cpus[0];

}
