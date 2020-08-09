#include "u_read.h"
char * u_read(const char * path) // !!! this function allocate memory. Dont forget use free()
{
	FILE * descr = fopen(path, "r");

	if(descr == NULL)
	{
		printf("File %s was not read\n", path);
		return NULL;
	}

	fseek(descr, 0L, SEEK_END);
	size_t size = ftell(descr);
	char * text = (char*)malloc(size);

	fseek(descr, 0L, SEEK_SET);
	fread((void*)text, size, 1, descr);
	text[size - 1] = '\0';

	fclose(descr);
	return text;
}
