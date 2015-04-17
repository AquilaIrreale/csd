#include <stddef.h>

char *strcpy(char *destination, const char *source)
{
	size_t i;
	for (i = 0; source[i] != '\0'; i++) {
		destination[i] = source[i];
	}
	destination[i] = '\0';
	return destination;
}


