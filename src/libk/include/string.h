#ifndef __STRING_H__
	#define __STRING_H__

#include <stddef.h>

/* Memory operations */
void *memset(void *ptr, int value, size_t num);
void *memcpy(void *destination, const void *source, size_t num);
void *memmove(void *destination, const void *source, size_t num);

#endif
