CROSSCOMPILE := arm-none-eabi-

QEMU = qemu-system-arm
# -s for start gdbserver, -S for pause at startup
GDBSERVER = -s -S

CC = $(CROSSCOMPILE)gcc
# TODO fix it!
AS = $(CROSSCOMPILE)gcc
LD = $(CROSSCOMPILE)ld
OBJCOPY = $(CROSSCOMPILE)objcopy

CFLAGS = -march=armv6 -fno-pic -static -fno-builtin -fno-strict-aliasing -Wall -O2
CFLAGS += -I. -Iinclude/
CFLAGS += -g
LDFLAGS = -L./
ASFLAGS = -march=armv6 -Iinclude/

PROG = kernel.elf
OBJS = \
	   string.o \
	   \
	   boot.o \
	   start.o \
	   arm.o \
	   main.o \
	   \
	   UART0.o

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.S
	$(AS) $(ASFLAGS) -c -o $@ $<


all: $(PROG)

$(PROG): $(OBJS)
	$(LD) -T kernel.ld -o $(PROG) -O2 -nostdlib $(OBJS)

clean:
	rm -f $(OBJS) $(PROG)

qemu: $(PROG)
	@clear
	@echo "Press Ctrl-A and then X to terminate QEMU session\n"
	$(QEMU) $(GDBSERVER) -M versatilepb -m 128 -cpu arm1176 -nographic -kernel kernel.elf
