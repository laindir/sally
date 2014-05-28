: rot >r swap r> swap ;
: -rot swap >r swap r> ;
: 2/mod dup 1 and swap rshift ;
: mulstep dup lshift >r >r 2/mod -rot 1- invert r> and + swap r> ;
: halfmul mulstep mulstep mulstep mulstep ;
: * 0 -rot halfmul halfmul drop drop ;
