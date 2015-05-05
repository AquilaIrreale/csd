#ifndef __STRING_H__
	#define __STRING_H__

#include <stddef.h>

/* Memory operations */
void *memset(void *ptr, int value, size_t num);
void *memcpy(void *destination, const void *source, size_t num);
void *memmove(void *destination, const void *source, size_t num);
int   memcmp(const void *ptr1, const void *ptr2, size_t num);
void *memchr(const void *ptr, int value, size_t num);

/* String operations */
size_t strlen(const char *string);
size_t strcspn(const char *str1, const char *str2);

char *strcat(char *destination, const char *source);
char *strncat(char *destination, const char *source, size_t num);
char *strcpy(char *destination, const char *source);
char *strncpy(char *destination, const char *source, size_t num);

#endif


