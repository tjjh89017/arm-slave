CROSSCOMPILE := arm-none-eabi-

CC = $(CROSSCOMPILE)gcc
AS = $(CROSSCOMPILE)as
LD = $(CROSSCOMPILE)LD
OBJCOPY = $(CROSSCOMPILE)objcopy

CFLAGS = -march=armv6 -fno-pic -static -fno-builtin -fno-strict-aliasing -Wall -O2
CFLAGS += -I. -Iinclude/
LDFLAGS = -L./
ASFLAGS = -march=armv6

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
	$(CC) -T kernel.ld -o kernel.elf -O2-nostdlib $(OBJS)
	$(OBJCOPY) kernel.elf -O binary kernel.bin
