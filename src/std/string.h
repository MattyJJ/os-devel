#ifndef __STRING_H
#define __STRING_H

#include <std/stddef.h>

size_t strlen(const char *str);
char *strcpy(char *dest, const char *src);
int strcmp(const char *a, const char *b);
int strncmp(const char *a, const char *b, size_t n);
char *strchar(const char *src, int c);

char *strcat(char *dest, const char *src);
char *strncat(char *dest, const char *src, size_t n);

#endif
