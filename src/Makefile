CROSSCOMPILE := arm-none-eabi-

QEMU = qemu-system-arm

CC = $(CROSSCOMPILE)gcc
# TODO fix it!
AS = $(CROSSCOMPILE)gcc
LD = $(CROSSCOMPILE)LD
OBJCOPY = $(CROSSCOMPILE)objcopy

CFLAGS = -march=armv6 -fno-pic -static -fno-builtin -fno-strict-aliasing -Wall -O2
CFLAGS += -I. -Iinclude/
LDFLAGS = -L./
ASFLAGS = -march=armv6 -Iinclude/

OBJS = \
	   boot.o \
	   start.o

KERNEL_OBJ = kernel.o

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.S
	$(AS) $(ASFLAGS) -c -o $@ $<


all: $(KERNEL_OBJ)

$(KERNEL_OBJ): $(OBJS)
	$(CC) -T kernel.ld -o kernel.elf -O2 -nostdlib $(OBJS)
	$(OBJCOPY) kernel.elf -O binary kernel.bin

qemu: kernel.elf
	@clear
	@echo "Press Ctrl-A and then X to terminate QEMU session\n"
	$(QEMU) -M versatilepb -m 128 -cpu arm1176  -nographic -kernel kernel.elf
