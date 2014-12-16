#include "arm.h"
#include "type.h"

/* TODO need to find a place to put it */
#define UART0 0x101f1000
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
	char *arr = "0123456789ABCDEF";
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

void start()
{
	_puts("booting...\n");
}
