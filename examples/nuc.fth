: rot ( a b c -- b c a ) >r swap r> swap ret ;
: -rot ( a b c -- c a b ) swap >r swap r> ret ;
: 2/mod ( a b -- r q ) dup 1 and swap rshift ret ;
: mulstep ( p a b -- p+?b a/2 2b ) dup lshift >r >r 2/mod -rot 1- invert r> and + swap r> ret ;
: halfmul mulstep mulstep mulstep mulstep ret ;
: * ( a b -- p ) 0 -rot halfmul halfmul drop drop ret ;
: fact ( n -- n! ) 1 swap zret swap drop dup 1- fact * ret ;
