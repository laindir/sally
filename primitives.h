#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include "arch.h"

enum word
{
	W_MODE,
	W_LIT,
	W_ADD,
	W_XOR,
	W_AND,
	W_OR,
	W_INVERT,
	W_EQU,
	W_LT,
	W_SWAP,
	W_DUP,
	W_DROP,
	W_OVER,
	W_DECR,
	W_TOR,
	W_FROMR,
	W_LSHIFT,
	W_RSHIFT,
	W_ZRET,
	W_CALL,
	W_RET,
	W_PRINT,
	W_PRINTC,
	W_NUMWORDS
};

struct dictentry
{
	enum word opcode;
	char *text;
	void (*code)(void);
};

struct dictentry dictionary[W_NUMWORDS];

#endif
