#include <stddef.h>
#include <stdint.h>

/* General purpose function
 * used to fill portions of memory with
 * a repeated 8-bit value
 */
void *memset(void *ptr, int value, size_t num)
{
	size_t i;
	for (i = 0; i < num; i++) {
		((uint8_t *)ptr)[i] = (uint8_t)value;
	}

	return ptr;
}


