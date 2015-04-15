#include <stddef.h>
#include <stdint.h>

void *memchr(const void *ptr, int value, size_t num)
{
	uint8_t c = (uint8_t)value;
	uint8_t *p = (uint8_t *)ptr;

	size_t i;
	for (i = 0; i < num; i++) {
		if (p[i] == c) {
			return &p[i];
		}
	}

	return NULL;
}
