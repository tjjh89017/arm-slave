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

void start()
{
	_puts("booting...\n");
}
