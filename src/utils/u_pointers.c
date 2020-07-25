#include "u_pointers.h"

void del(void * ptr)
{
   	free(ptr); 
	ptr = 0;
}
