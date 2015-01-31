#include "arm.h"
#include "type.h"
#include "mmu.h"
#include "memlayout.h"
#include "device/versatile_pb.h"

#define __DEBUG__

void _uart_putc(int c)
{
	volatile uint8 *uart0 = (uint8*)UART0;
	*uart0 = c;
}

void _puts(char *s)
{
	for(; *s != '\0'; s++){
		_uart_putc(*s);
	}
}

void _putint(char *prefix, uint val, char * suffix)
{
	char *arr = "0123456789abcdef";
	int index = 0;

	if(prefix){
		_puts(prefix);
	}

	for(index = sizeof(val) * 8 - 4; index >= 0; index -= 4){
		_uart_putc(arr[(val >> index) & 0x0f]);
	}

	if(suffix){
		_puts(suffix);
	}
}

extern uint32 _kernel_pgd;
extern uint32 _user_pgd;
extern void *end;
extern void jump_svcstack();

uint32 *kernel_pgd = &_kernel_pgd;
uint32 *user_pgd = &_user_pgd;

void set_bootpgd(uint32 virt, uint32 phys, uint len, int dev_mem)
{
	uint32 pgd;
	int index;

	// convert all address into index
	virt = PGD_INDEX(virt);
	phys = PGD_INDEX(phys);
	len  = PGD_INDEX(len);

	for(index = 0; index < len; index++){
		pgd = phys << PGD_SHIFT;

		if(!dev_mem){
			/*
			 * normal memory mapping, kernel-only, cachable, bufferable
			 */
			pgd |= (AP_KO << 10) | PE_CACHE | PE_BUF | KPGD_TYPE;
		}
		else{
			/*
			 * device memory, non-cachable, non-bufferable
			 */
			pgd |= (AP_KO << 10) | KPGD_TYPE;
		}
		
		// use different page table for user/kernel space
		if(virt < NUM_UPGD){
			user_pgd[virt] = pgd;
		}
		else{
			kernel_pgd[virt] = pgd;
		}

		virt++;
		phys++;
	}
}

static void _flush_TLB()
{
	int val = 0;
	asm("mcr p15, 0, %[v], c8, c7, 0" : : [v]"r"(val) : );
}

void load_bootpgd(uint32 *k_pgd, uint32 *u_pgd)
{
	int ret;
	int val;

	/*
	 * We skip ARM version checking
	 */


	/*
	 * Set all domain into checking permission mode
	 * TODO domain need to use for multi-user in the future
	 */
	val = 0x55555555;
	asm("mcr p15, 0, %[v], c3, c0, 0" : : [v]"r"(val) : );

	/*
	 * Using 2 TTB
	 * TTB0 for user
	 * TTB1 for kernel
	 * 0x00000000 - 0x80000000 for user
	 * N = 1
	 */
	val = 32 - UADDR_BITS;
	asm("mcr p15, 0, %[v], c2, c0, 2" : : [v]"r"(val) : );

	/*
	 * Set kernel PGD
	 */
	val = (uint)k_pgd | 0x00;
	asm("mcr p15, 0, %[v], c2, c0, 1" : : [v]"r"(val) : );

	/*
	 * Set user PGD
	 */
	val = (uint)u_pgd | 0x00;
	asm("mcr p15, 0, %[v], c2, c0, 0" : : [v]"r"(val) : );

	/*
	 * Enable paging
	 */
	asm("mrc p15, 0, %[v], c1, c0, 0" : [v]"=r"(val) : : );
	val |= 0x80300d;
	asm("mcr p15, 0, %[v], c1, c0, 0" : : [v]"r"(val) : );

	_flush_TLB();
}

void start()
{
	uint32 vectbl;
	_puts("booting...\n");
	
	// set pgd
	set_bootpgd(0, 0, INIT_KERNEL_MAP, 0);
	set_bootpgd(KERNEL_BASE, 0, INIT_KERNEL_MAP, 0);

	vectbl = phys_to_virt_wo(VECTOR_TABLE & PGD_MASK);
	if(vectbl <= (uint32)&end){
		_puts("error: vector table overlaps kernel\n");
	}

	set_bootpgd(VECTOR_TABLE, 0, 1 << PGD_SHIFT, 0);
	set_bootpgd(KERNEL_BASE + DEVICE_BASE, DEVICE_BASE, DEVICE_MEM_SIZE, 1);

#ifdef __DEBUG__
	
	// before enable MMU phys address works
	int i = 0;
	for(i = 0; i < 0x4000 / 4; i++){
		if(kernel_pgd[i]){
			_putint("kernel: ", i, " ");
			_putint(NULL, kernel_pgd[i], "\n");
		}
	}
	for(i = 0; i < 0x1000 / 4; i++){
		if(user_pgd[i]){
			_putint("user:   ", i, " ");
			_putint(NULL, user_pgd[i], "\n");
		}
	}
#endif

	/*
	 * Load PGD, and enable paging
	 */
	load_bootpgd(kernel_pgd, user_pgd);

	/*
	 * set stack top to SVC stck
	 */
	jump_svcstack();
}
