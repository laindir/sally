#include <stdio.h>

typedef char word;
typedef unsigned char uword;
#define SZ 256

word stack[SZ];

void
push(word w)
{
	stack[(uword)++stack[0]] = w;
}

word
pop()
{
	return stack[(uword)stack[0]--];
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

void (*dictionary[])(void) = {
	NULL, /*0*/
	NULL, /*lit*/
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
	print,
	printc
};

int
main(void)
{
	int c;
	while((c = getchar()) != EOF)
	{
		if(c == W_LIT && (c = getchar()) != EOF)
		{
			push(c);
		}
		else
		{
			dictionary[c]();
		}
	}
	return 0;
}
