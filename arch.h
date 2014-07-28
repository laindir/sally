#ifndef ARCH_H
#define ARCH_H

#include <limits.h>

typedef char word;
typedef unsigned char uword;

void push(word w);

word pop(void);

int rcount(void);

void rpush(word w);

word rpop(void);

#define addr(h,l) ((h<<(sizeof(word)*CHAR_BIT))|(l))
#define hi(addr) (addr>>(sizeof(word)*CHAR_BIT))
#define lo(addr) (((1<<(sizeof(word)*CHAR_BIT))-1)&(addr))

#define SZ (1 << 8)
#define MSZ (1 << 16)

word mem[MSZ];
int ip;
int bound;

#endif
