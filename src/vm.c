#include "arm.h"
#include "mmu.h"
#include "vm.h"
#include "type.h"
#include "spinlock.h"

// define at kernel.ld
extern char data[];

pde_t *kernel_pde;

// mem alloc
struct run {
	struct run *next;
};

struct {
	struct spinlock lock;
	struct run *freelist;
} kernel_mem;

void init_vm()
{
	initlock(&kernel_mem.lock, "vm");
	kernel_mem.freelist = NULL;
}

static void _kernel_mem_free(char *v)
{
	struct run *r = (struct run*)v;
	r->next = kernel_mem.freelist;
	kernel_mem.freelist = r;
}

void kernel_mem_freerange(uint32 low, uint32 high)
{
	while(low < hi){
		_kernel_mem_free((char*)low);
		low += PTE_SIZE;
	}
}
