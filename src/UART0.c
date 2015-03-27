#include "arm.h"
#include "type.h"
#include "mmu.h"
#include "memlayout.h"
#include "device/versatile_pb.h"

// TODO only for debugging
// UART
void UART0_putc(int c)
{
	volatile uint8 *uart0 = (uint8*)(KERNEL_BASE + UART0);
	*uart0 = c;
}

void UART0_puts(char *s)
{
	for(; *s != '\0'; s++){
		UART0_putc(*s);
	}
}

void UART0_putint(char *prefix, uint val, char *suffix)
{
	char *arr = "0123456789abcdef";
	int index = 0;

	if(prefix){
		UART0_puts(prefix);
	}

	for(index = sizeof(val) * - 4; index >= 0; index -= 4){
		UART0_putc(arr[(val >> index) & 0x0f]);
	}

	if(suffix){
		UART0_puts(suffix);
	}
}
