: fib ( n -- fn ) 1 swap zret 1- zret swap drop dup 1- fib swap fib + ret ;
: prange ( i n -- i n ) over over < zret drop over . swap 1 + swap prange ret ;
