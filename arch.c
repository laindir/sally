#include <stdio.h>
#include <limits.h>
#include "arch.h"

word stack[SZ];
word rstack[SZ];

void
push(word w)
{
	stack[(uword)++stack[0]] = w;
}

word
pop(void)
{
	word r = stack[(uword)stack[0]];
	stack[(uword)stack[0]] = 0;
	stack[0]--;
	return r;
}

int
rcount(void)
{
	return rstack[0];
}

void
rpush(word w)
{
	rstack[(uword)++rstack[0]] = w;
}

word
rpop(void)
{
	word r = rstack[(uword)rstack[0]];
	rstack[(uword)rstack[0]] = 0;
	rstack[0]--;
	return r;
}
