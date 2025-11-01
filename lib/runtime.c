#include "fcc_lib.h"


void _start() {
    _fcc_init();
    

    extern int main();
    int result = main();
    
    _fcc_exit(result);
}


void _fcc_init() {
 
}


void _fcc_exit(int code) {
    // sys_exit in x86-64 Linux
    asm volatile (
        "mov $60, %%rax\n"  // sys_exit = 60
        "syscall"
        :
        : "D" (code)
        : "rax", "rcx", "r11"
    );
}

// memset basic
void* memset(void *s, int c, size_t n) {
    unsigned char *p = (unsigned char*)s;
    while (n--) *p++ = (unsigned char)c;
    return s;
}

// memcpy basic
void* memcpy(void *dest, const void *src, size_t n) {
    unsigned char *d = (unsigned char*)dest;
    const unsigned char *s = (const unsigned char*)src;
    while (n--) *d++ = *s++;
    return dest;
}

// memcmp basic
int memcmp(const void *s1, const void *s2, size_t n) {
    const unsigned char *p1 = (const unsigned char*)s1;
    const unsigned char *p2 = (const unsigned char*)s2;
    while (n--) {
        if (*p1 != *p2) return *p1 - *p2;
        p1++;
        p2++;
    }
    return 0;
}

// strlen basic
size_t strlen(const char *s) {
    size_t len = 0;
    while (s[len]) len++;
    return len;
}

// strcpy basic
char* strcpy(char *dest, const char *src) {
    char *d = dest;
    while ((*d++ = *src++));
    return dest;
}

// strcmp basic
int strcmp(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(unsigned char*)s1 - *(unsigned char*)s2;
}
