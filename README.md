#sally

A bytecode compiler (awk) and interpreter (c) for a Forth like language.

The more I play with lex and yacc, the more I see the appeal of stack based
languages. This one started out as a pure Forth, but began diverging when I
added control flow. I opted for a primitive return-if-zero rather than more
conventional if-then-else or looping constructs, since the primitive is much
easier to implement in the compiler--no need to do look-ahead or behind for
jump addresses, since the only possible jump targets are words.

##(Anti)Features

* 8 bit word size. Should be relatively simple to increase this.
* The interpreter does tail recursion optimization at runtime.
* The entire compiler is 3 functions and 3 awk rules
* It's possible to run the interpreter interactively by passing stdin through
the compiler

##Roadmap

None.

This is a toy language for me to learn the bare basics of compilation. It is
Turing complete, but so are a lot of things that shouldn't be used in
production.
