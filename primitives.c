#include <stdio.h>
#include "primitives.h"

void
lit(void)
{
	push(mem[++ip]);
}

void
add(void)
{
	push(pop() + pop());
}

void
xor(void)
{
	push(pop() ^ pop());
}

void
and(void)
{
	push(pop() & pop());
}

void
or(void)
{
	push(pop() | pop());
}

void
invert(void)
{
	push(~pop());
}

void
equ(void)
{
	push(pop() == pop());
}

void
lt(void)
{
	word a = pop();
	word b = pop();
	push(b < a);
}

void
swap(void)
{
	word a = pop();
	word b = pop();
	push(a);
	push(b);
}

void
dup(void)
{
	word a = pop();
	push(a);
	push(a);
}

void
drop(void)
{
	(void)pop();
}

void
over(void)
{
	word a = pop();
	word b = pop();
	push(b);
	push(a);
	push(b);
}

void
decr(void)
{
	push(pop() - 1);
}

void
tor(void)
{
	rpush(pop());
}

void
fromr(void)
{
	push(rpop());
}

void
lshift(void)
{
	push(pop() << 1);
}

void
rshift(void)
{
	push(pop() >> 1);
}

void
print(void)
{
	printf("%d\n", pop());
}

void
printc(void)
{
	printf("%c", pop());
}

void (*dictionary[])(void) = {
	NULL, /*0*/
	lit,
	add,
	xor,
	and,
	or,
	invert,
	equ,
	lt,
	swap,
	dup,
	drop,
	over,
	decr,
	tor,
	fromr,
	lshift,
	rshift,
	zret,
	call,
	ret,
	print,
	printc
};

void
zret(void)
{
	word a = pop();
	if(a == 0)
	{
		ret();
	}
	else
	{
		push(a);
	}
}

void
call(void)
{
	word a = pop();
	word b = pop();
	word c;
	word d;
	if(rcount() >= 2)
	{
		c = rpop();
		d = rpop();
		rpush(d);
		rpush(c);
		if(ip != addr(c,d) || dictionary[(uword)mem[ip + 1]] != ret)
		{
			rpush(lo(ip));
			rpush(hi(ip));
		}
	}
	else
	{
		rpush(lo(ip));
		rpush(hi(ip));
	}
	ip = addr(a,b);
	while(rcount() && ip < bound)
	{
		dictionary[(uword)mem[ip]]();
		ip++;
	}
}

void
ret(void)
{
	word a = rpop();
	word b = rpop();
	ip = addr(a,b);
}
