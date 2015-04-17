#include <stddef.h>

char *strcpy(char *destination, const char *source)
{
	size_t i;
	for (i = 0; source[i] != '\0'; i++) {
		dest[i] = source[i];
	}
	dest[i] = '\0';
	return destination;
}


