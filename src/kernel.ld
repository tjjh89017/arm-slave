OUTPUT_ARCH(arm)
ENTRY(_start)

ENTRY_SVC_STACK_SIZE = 0x1000;

SECTIONS
{
	. = 0x10000;
	.start_section : {
		boot.o(.text .text.*)
		start.o(.text .text.*)

		boot.o(.rodata .rodata.*)
		start.o(.rodata .rodata.*)

		boot.o(.data .data.*)
		start.o(.data .data.*)

		PROVIDE(boot_data_start = .);
		PROVIDE(boot_bss_start = .);

		boot.o(.bss .bss.* COMMON)
		start.o(.bss .bss.* COMMON)

		. = ALIGN(0x1000);
		PROVIDE(boot_bss_end = .);

		/* define a stack for boot */
		. += ENTRY_SVC_STACK_SIZE;
		PROVIDE(svc_stack = .);

		. = ALIGN(0x4000);
		/* for kernel page table */
		PROVIDE(_kernel_pgd = .);
		. += 0x4000;

		/* for user page table */
		PROVIDE(_user_pgd = .);
		. += 0x1000;

		PROVIDE(boot_data_end = .);
	}

	. = ALIGN(0x1000);

	PROVIDE(data_start = .);
	.data : {
		*(.data .data.*)
	}
	PROVIDE(data_end = .);
	PROVIDE(bss_start = .);
	.bss : {
		*(.bss .bss.* COMMON)
	}
	PROVIDE(bss_end = .);

	. = ALIGN(0x1000);
	PROVIDE(end = .);
}
