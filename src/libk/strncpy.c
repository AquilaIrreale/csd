#include <stddef.h>

char *strncpy(char *destination, const char *source, size_t num)
{
	size_t i;
	for (i = 0; i < num && source[i] != '\0'; i++) {
		destination[i] = source[i];
	}
	destination[i] = '\0';
	return destination;
}


