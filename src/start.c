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

void start()
{
	uint32 vectbl;
	_puts("booting...\n");
	
	// set pgd
	set_bootpgd(0, 0, INIT_KERNEL_MAP, 0);
	set_bootpgd(KERNEL_BASE, 0, INIT_KERNEL_MAP, 0);

	vectbl = phys_to_virt_wo(VEC_TBL & PGD_MASK);
	if(vectbl <= (uint32)&end){
		_puts("error: vector table overlaps kernel\n");
	}

	set_bootpgd(VEC_TBL, 0, 1 << PGD_SHIFT, 0);
	set_bootpgd(KERNEL_BASE + DEV_BASE, DEV_BASE, DEV_MEM_SIZE, 1);

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
}
