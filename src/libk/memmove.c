#include <stddef.h>
#include <stdint.h>

void *memmove(void *destination, const void *source, size_t num)
{
	size_t i;
	if (destination < source) {
		for (i = 0; i < num; i++) {
			((uint8_t *)destination)[i] = ((uint8_t *)source)[i];
		}
	} else {
		for (i = num -1;; i--) {
			((uint8_t *)destination)[i] = ((uint8_t *)source)[i];
			if (i == 0) {
				break;
			}
		}
	}

	return destination;
}


