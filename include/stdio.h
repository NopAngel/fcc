#ifndef FCC_STDIO_H
#define FCC_STDIO_H

#include "stddef.h"

#define EOF (-1)

// File descriptor para stdout/stdin/stderr
#define STDIN_FILENO  0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

// Prototipos de funciones básicas
int printf(const char *format, ...);
int putchar(int c);
int puts(const char *s);
int getchar(void);

// Funciones de sistema que usaremos internamente
int fcc_write(int fd, const void *buf, size_t count);
size_t fcc_strlen(const char *s);

#endif
