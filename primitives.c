#include <stdio.h>
#include "primitives.h"

static void
lit(void)
{
	push(mem[++ip]);
}

static void
add(void)
{
	push(pop() + pop());
}

static void
xor(void)
{
	push(pop() ^ pop());
}

static void
and(void)
{
	push(pop() & pop());
}

static void
or(void)
{
	push(pop() | pop());
}

static void
invert(void)
{
	push(~pop());
}

static void
equ(void)
{
	push(pop() == pop());
}

static void
lt(void)
{
	word a = pop();
	word b = pop();
	push(b < a);
}

static void
swap(void)
{
	word a = pop();
	word b = pop();
	push(a);
	push(b);
}

static void
dup(void)
{
	word a = pop();
	push(a);
	push(a);
}

static void
drop(void)
{
	(void)pop();
}

static void
over(void)
{
	word a = pop();
	word b = pop();
	push(b);
	push(a);
	push(b);
}

static void
decr(void)
{
	push(pop() - 1);
}

static void
tor(void)
{
	rpush(pop());
}

static void
fromr(void)
{
	push(rpop());
}

static void
lshift(void)
{
	push(pop() << 1);
}

static void
rshift(void)
{
	push(pop() >> 1);
}

static void
print(void)
{
	printf("%d\n", pop());
}

static void
printc(void)
{
	printf("%c", pop());
}

static void
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
		if(ip != addr(c,d) || mem[ip + 1] != W_RET)
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
		dictionary[(uword)mem[ip]].code();
		ip++;
	}
}

static void
ret(void)
{
	word a = rpop();
	word b = rpop();
	ip = addr(a,b);
}

static void
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

struct dictentry dictionary[W_NUMWORDS] = {
	{W_MODE, "Reserved by the interpreter to switch between compilation and execution", NULL},
	{W_LIT, "Reserved by the interpreter to indicate a following literal be pushed to the stack", lit},
	{W_ADD, "+", add},
	{W_XOR, "xor", xor},
	{W_AND, "and", and},
	{W_OR, "or", or},
	{W_INVERT, "invert", invert},
	{W_EQU, "=", equ},
	{W_LT, "<", lt},
	{W_SWAP, "swap", swap},
	{W_DUP, "dup", dup},
	{W_DROP, "drop", drop},
	{W_OVER, "over", over},
	{W_DECR, "1-", decr},
	{W_TOR, ">r", tor},
	{W_FROMR, "r>", fromr},
	{W_LSHIFT, "lshift", lshift},
	{W_RSHIFT, "rshift", rshift},
	{W_ZRET, "zret", zret},
	{W_CALL, "call", call},
	{W_RET, "ret", ret},
	{W_PRINT, ".", print},
	{W_PRINTC, ",", printc}
};
