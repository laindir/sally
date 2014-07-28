#include <stdio.h>
#include <limits.h>
#include "primitives.h"
#include "arch.h"

int
main(void)
{
	int c;
	int immediate = 1;
	while((c = getchar()) != EOF)
	{
		if(c == W_LIT && (c = getchar()) != EOF)
		{
			if(immediate)
			{
				push(c);
			}
			else
			{
				mem[bound++] = W_LIT;
				mem[bound++] = c;
			}
		}
		else if(c == 0)
		{
			immediate = !immediate;
		}
		else if(!immediate)
		{
			mem[bound++] = c;
		}
		else
		{
			dictionary[c]();
		}
	}
	return 0;
}
