#include "spinlock.h"
#include "arm.h"

void initlock(struct spinlock *lock, char *name)
{
	lock->name = name;
	lock->locked = 0;
}

void acquire(struct spinlock *lock)
{
	// TODO add SMP support
	pushcli();
	lock->locked = 1;
}

void release(struct spinlock *lock)
{
	// TODO add SMP support
	lock->locked = 0;
	popcli();
}

inline int holding(struct spinlock *lock)
{
	return lock->locked;
}
