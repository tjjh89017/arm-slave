#ifndef __ARM_H__
#define __ARM_H__

#ifndef __ASSEMBLER__

#endif


// cpsr|spsr intrrupt mode
#define NO_INT      0xc0
#define DIS_INT     0x80

// ARM 7 mode
#define MODE_MASK   0x1f
#define USR_MODE    0x10
#define FIQ_MODE    0x11
#define IRQ_MODE    0x12
#define SVC_MODE    0x13
#define ABT_MODE    0x17
#define UND_MODE    0x1b
#define SYS_MODE    0x1f

#ifndef __ASSEMBLER__

void cli();
void sti();
void pushcli();
void popcli();

#endif

#endif
