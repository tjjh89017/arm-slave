#ifndef __PROC_H__
#define __PROC_H__

#include "arm.h"
#include "type.h"

struct cpu {
	uchar id;
	
	// depth of pushcli nesting
	int ncli;
	// were interrupts enabled before pushcli?
	int intena;
};

#endif
