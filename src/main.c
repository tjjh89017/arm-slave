#include "arm.h"
#include "type.h"
#include "proc.h"
#include "memlayout.h"
#include "mmu.h"

struct cpu cpus[NCPU];
struct *cpu;

void kmain()
{
	cpu = &cpus[0];

}
