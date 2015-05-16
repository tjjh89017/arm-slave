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

void initlock(struct spinlock*, char*);
void acquire(struct spinlock*);
void release(struct spinlock*);
int holding(struct spinlock*);

#endif
