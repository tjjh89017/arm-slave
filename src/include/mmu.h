#ifndef __MMU_H__
#define __MMU_H__

#include "type.h"

// align
#define align_up(size, al) (((uint)(size) + (uint)(al) - 1) & ~((uint)(al) - 1))
#define align_down(size, al) ((uint)(size) & ~((uint)(al) - 1))

// accesss permission AP
#define AP_NA    0x00 // no access
#define AP_KO    0x01 // kernel only
#define AP_KUR   0x02 // user write only
#define AP_KU    0x03 // access

// page entry other permission
#define PE_CACHE (1 << 3) // cachable
#define PE_BUF   (1 << 2) // bufferable

// page types
#define PE_TYPE_MASK 0x03 // mask for page type
#define KPGD_TYPE    0x02 // "section" type for kernel PGD
#define UPGD_TYPE    0x01 // "coarse page table" for user PGD
#define PTE_TYPE     0x02 // execuable user page

// 1st level
#define PGD_SHIFT 20
#define PGD_SIZE (1 << PGD_SHIFT)
#define PGD_MASK (PGD_SIZE - 1)
#define PGD_INDEX(v) ((uint)(v) >> PGD_SHIFT)

// 2nd level
#define PTE_SHIFT 12
#define PTE_SIZE (1 << PTE_SHIFT)

// user size
#define UADDR_BITS 28 // max user app memory 256MB
#define UADDR_SIZE (1 << UADDER_BITS)

#define NUM_UPGD (1 << (UADDR_BITS - PGD_SHIFT))
#define NUM_PTE (1 << (PGD_SHIFT - PTE_SHIFT))

#endif
