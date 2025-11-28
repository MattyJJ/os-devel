#include <std/stdio.h>

#include <kernel/vga.h>

#include <std/convert.h>

static void putchar(char c) { vga_putc(c); }

static int swrite_uint(char *dest, unsigned long n, int base) {
    char buf[32];
    utoa(n, buf, base);
    int len = 0;
    while (buf[len]) {
        dest[len] = buf[len];
        len++;
    }
    return len;
}

static int swrite_int(char *dest, long n) {
    int len = 0;
    if (n < 0) {
        dest[len++] = '-';
        n = -n;
    }
    len += swrite_uint(dest + len, (unsigned long)n, 10);
    return len;
}

int vsprintf(char *str, const char *fmt, va_list args) {
    char *s = str;
    const char *f = fmt;

    while (*f) {
        if (*f != '%') {
            *s++ = *f++;
            continue;
        }

        f++;

        switch (*f) {
        case 'd':
        case 'i': {
            long val = va_arg(args, int);
            s += swrite_int(s, val);
            break;
        }
        case 'u': {
            unsigned long val = va_arg(args, unsigned int);
            s += swrite_uint(s, val, 10);
            break;
        }
        case 'x': {
            unsigned long val = va_arg(args, unsigned int);
            s += swrite_uint(s, val, 16);
            break;
        }
        case 'X': {
            unsigned long val = va_arg(args, unsigned int);
            s += swrite_uint(s, val, 16);
            break;
        }
        case 'o': {
            unsigned long val = va_arg(args, unsigned int);
            s += swrite_uint(s, val, 8);
            break;
        }
        case 'c': {
            *s++ = (char)va_arg(args, int);
            break;
        }
        case 's': {
            char *str = va_arg(args, char *);
            if (!str)
                str = "(null)";
            while (*str) {
                *s++ = *str++;
            }
            break;
        }
        case 'p': {
            void *ptr = va_arg(args, void *);
            *s++ = '0';
            *s++ = 'x';
            s += swrite_uint(s, (unsigned long)ptr, 16);
            break;
        }
        case '%': {
            *s++ = '%';
            break;
        }
        default:
            *s++ = '%';
            *s++ = *f;
            break;
        }
        f++;
    }

    *s = '\0';
    return s - str;
}

int sprintf(char *str, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    int result = vsprintf(str, fmt, args);
    va_end(args);
    return result;
}

int printf(const char *fmt, ...) {
    char buffer[1024];
    va_list args;
    va_start(args, fmt);
    int result = vsprintf(buffer, fmt, args);
    va_end(args);

    for (int i = 0; buffer[i]; i++) {
        putchar(buffer[i]);
    }

    return result;
}
