#include "arm.h"
#include "memlayout.h"

# To make sure the section be the first in kernel
.section ".text.boot"

.global _start

_start:
	mov sp, #0x8000

	ldr r1, =boot_data_start
	ldr r2, =boot_data_end
	mov r3, #0x00

# clear boot bss section
1:
	cmp r1, r2
	stmltia r1!, {r3}
	blt 1b

	# switch to SVC mode and disable interrupt
	msr cpsr_cxsf, #(SVC_MODE | NO_INT)
	
	# using user mode stack for boot
	ldr sp, =svc_stack

	bl start

	# use wfe sleep rather than busy wait
	#but RPI1 ARM1176 donesn't support it
	b .
	#wfe

# switch to kernel address
.global jump_svcstack
jump_svcstack:
	mov r0, sp
	add r0, r0, #KERNEL_BASE
	mov sp, r0
	mov pc, lr
