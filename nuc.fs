: rot >r swap r> swap ret ;
: -rot swap >r swap r> ret ;
: 2/mod dup 1 and swap rshift ret ;
: mulstep dup lshift >r >r 2/mod -rot 1- invert r> and + swap r> ret ;
: halfmul mulstep mulstep mulstep mulstep ret ;
: * 0 -rot halfmul halfmul drop drop ret ;
