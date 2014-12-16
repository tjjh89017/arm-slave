#ifndef __MEMLAYOUT_H__
#define __MEMLAYOUT_H__

#define EXTMEM 0x20000
#define KERNEL_BASE 0xc0000000
#define KERNEL_LINK (KERNEL_BASE + EXTMEM)

#define INIT_KERNEL_MAP 0x100000

#define virt_to_phys(a) (((uint)(a)) - KERNEL_BASE)
#define phys_to_virt(a) (((void*)(a)) + KERNEL_BASE)

#define virt_to_phys_wo(x) ((x) - KERNEL_BASE)
#define phys_to_virt_wo(x) ((x) + KERNEL_BASE)

#endif
