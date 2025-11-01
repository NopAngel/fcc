#include "stdio.h"


static int sys_write(int fd, const void *buf, size_t count) {
    long ret;
    asm volatile (
        "mov $1, %%rax\n"    // sys_write = 1
        "syscall"
        : "=a" (ret)
        : "D" (fd), "S" (buf), "d" (count)
        : "rcx", "r11", "memory"
    );
    return (int)ret;
}

// strlen simple
size_t fcc_strlen(const char *s) {
    size_t len = 0;
    while (s[len]) len++;
    return len;
}

// write for FCC
int fcc_write(int fd, const void *buf, size_t count) {
    return sys_write(fd, buf, count);
}

// putchar - write a character
int putchar(int c) {
    char ch = (char)c;
    return fcc_write(STDOUT_FILENO, &ch, 1) == 1 ? c : EOF;
}

// puts - write a string + newline
int puts(const char *s) {
    size_t len = fcc_strlen(s);
    int ret1 = fcc_write(STDOUT_FILENO, s, len);
    int ret2 = fcc_write(STDOUT_FILENO, "\n", 1);
    return (ret1 >= 0 && ret2 == 1) ? 0 : EOF;
}

// printf basic
int printf(const char *format, ...) {
    char buffer[512];
    char *p = buffer;
    

    char *arg_ptr = (char*)&format + sizeof(char*);
    
    for (int i = 0; format[i]; i++) {
        if (format[i] == '%' && format[i+1]) {
            i++;
            switch (format[i]) {
                case 'd': {  // int
                    int num = *(int*)arg_ptr;
                    arg_ptr += sizeof(int);
                    
                    if (num == 0) {
                        *p++ = '0';
                    } else {
                        if (num < 0) {
                            *p++ = '-';
                            num = -num;
                        }
                        
                        char num_buf[32];
                        int digits = 0;
                        while (num > 0) {
                            num_buf[digits++] = '0' + (num % 10);
                            num /= 10;
                        }
                        
                        
                        for (int j = digits - 1; j >= 0; j--) {
                            *p++ = num_buf[j];
                        }
                    }
                    break;
                }
                case 's': {  // String
                    char *str = *(char**)arg_ptr;
                    arg_ptr += sizeof(char*);
                    
                    while (str && *str) {
                        *p++ = *str++;
                    }
                    break;
                }
                case 'c': {  // Character
                    char ch = *(char*)arg_ptr;
                    arg_ptr += sizeof(int);  // chars 
                    *p++ = ch;
                    break;
                }
                case '%': {  // % literal
                    *p++ = '%';
                    break;
                }
                default: {   
                    *p++ = '%';
                    *p++ = format[i];
                    break;
                }
            }
        } else {
            *p++ = format[i];
        }
    }
    
    *p = '\0';
    int written = fcc_write(STDOUT_FILENO, buffer, p - buffer);
    return written >= 0 ? written : EOF;
}

// getchar basic (placeholder)
int getchar(void) {
    // EOF RETURN
    return EOF;
}
