#ifndef FCC_LIB_H
#define FCC_LIB_H

#include "stddef.h"

// Funciones de runtime básicas
void _fcc_init();
void _fcc_exit(int code);

// Helpers para memoria (básicos)
void* memset(void *s, int c, size_t n);
void* memcpy(void *dest, const void *src, size_t n);
int memcmp(const void *s1, const void *s2, size_t n);

// Strings básicas
size_t strlen(const char *s);
char* strcpy(char *dest, const char *src);
int strcmp(const char *s1, const char *s2);

#endif
