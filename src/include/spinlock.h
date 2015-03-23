#ifndef __SPINLOCK_H__
#define __SPINLOCK_H__

#include "arm.h"
#include "type.h"

struct spinlock {
	uint locked;

	char *name;
	// cpu
	// pcs
};

#endif
