#ifndef __STDIO_H
#define __STDIO_H

#include <std/stdarg.h>
#include <std/stddef.h>
#include <std/stdint.h>

static inline void outb(uint16_t port, uint8_t val) {
    __asm__ volatile("outb %0, %1" : : "a"(val), "Nd"(port));
}

static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    __asm__ volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

int vsprintf(char *str, const char *fmt, va_list args);
int sprintf(char *str, const char *fmt, ...);
int printf(const char *fmt, ...);

#endif
