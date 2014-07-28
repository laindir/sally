#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include "arch.h"

void lit(void);

void add(void);

void xor(void);

void and(void);

void or(void);

void invert(void);

void equ(void);

void lt(void);

void swap(void);

void dup(void);

void drop(void);

void over(void);

void decr(void);

void tor(void);

void fromr(void);

void lshift(void);

void rshift(void);

void print(void);

void printc(void);

enum word
{
	W_LIT = 1
};

void zret(void);
void call(void);
void ret(void);

void (*dictionary[23])(void);

#endif
