#include <stddef.h>

char *strcat(char *destination, const char *source, size_t num) {
	size_t d;
	size_t i;
	for (d = 0; destination[d] != '\0'; d++);
	for (i = 0; i < num && source[i] != '\0'; i++, d++) {
		destination[d] = source[i];
	}
	destination[d] = '\0';
	return destination;
}


