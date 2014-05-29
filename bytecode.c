#include <stdio.h>
#include <limits.h>

typedef char word;
typedef unsigned char uword;
#define SZ 1 << 8
#define MSZ 1 << 16

word stack[SZ];
word rstack[SZ];
word mem[MSZ];
int ip;
int bound;

void
push(word w)
{
	stack[(uword)++stack[0]] = w;
}

word
pop()
{
	word r = stack[(uword)stack[0]];
	stack[(uword)stack[0]] = 0;
	stack[0]--;
	return r;
}

void
rpush(word w)
{
	rstack[(uword)++rstack[0]] = w;
}

word
rpop()
{
	word r = rstack[(uword)rstack[0]];
	rstack[(uword)rstack[0]] = 0;
	rstack[0]--;
	return r;
}

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

enum word
{
	W_LIT = 1
};

void call(void);
void ret(void);

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
	call,
	ret,
	print,
	printc
};

#define addr(h,l) ((h<<(sizeof(word)*CHAR_BIT))|(l))
#define hi(addr) (addr>>(sizeof(word)*CHAR_BIT))
#define lo(addr) (((1<<(sizeof(word)*CHAR_BIT))-1)&(addr))

void
call(void)
{
	word a = pop();
	word b = pop();
	word c;
	word d;
	if(rstack[0] >= 2)
	{
		c = rpop();
		d = rpop();
		rpush(d);
		rpush(c);
		if(ip != addr(c,d))
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
	while(rstack[0] && ip < bound)
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

int
main(void)
{
	int c;
	int immediate = 1;
	while((c = getchar()) != EOF)
	{
		if(c == W_LIT && (c = getchar()) != EOF)
		{
			if(immediate)
			{
				push(c);
			}
			else
			{
				mem[bound++] = W_LIT;
				mem[bound++] = c;
			}
		}
		else if(c == 0)
		{
			immediate = !immediate;
		}
		else if(!immediate)
		{
			mem[bound++] = c;
		}
		else
		{
			dictionary[c]();
		}
	}
	return 0;
}
