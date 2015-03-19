#include <type.h>
#include <arm.h>

void* memset(void *dst, int v, int n)
{
	uint8 *p = (uint*)dst;
	uint8 c = (uint)v;

	int i = 0;
	for(i = 0; i < n; i++)
		*p++ = c;

	return dst;
}
