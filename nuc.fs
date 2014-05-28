: rot >r swap r> swap ;
: -rot swap >r swap r> ;
: 2/mod dup 1 and swap rshift ;
: mulstep -rot 2/mod swap 1- invert rot dup lshift -rot and >r swap rot r> + ;
: halfmul mulstep mulstep mulstep mulstep ;
: * 0 halfmul halfmul -rot drop drop ;
