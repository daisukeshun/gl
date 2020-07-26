#include "u_strcpy.h"

void u_copyToNewString(GLchar ** dest, const GLchar * string)
{
	*dest = (GLchar *)malloc(strlen(string));
	memset(*dest, '\0', strlen(string));
	strcpy(*dest, string);
}

