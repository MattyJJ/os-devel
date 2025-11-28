#include <std/memory.h>

#include <std/stdint.h>

void *memcpy(void *dest, const void *src, size_t n) {
    uint8_t *d = (uint8_t *)dest;
    const uint8_t *s = (const uint8_t *)src;

    for (size_t i = 0; i < n; i++) {
        d[i] = s[i];
    }

    return dest;
}

void *memset(void *dest, int c, size_t n) {
    uint8_t *d = (uint8_t *)dest;
    uint8_t byte = (uint8_t)c;

    for (size_t i = 0; i < n; i++) {
        d[i] = byte;
    }

    return dest;
}

int memcmp(const void *s1, const void *s2, size_t n) {
    const uint8_t *p1 = s1;
    const uint8_t *p2 = s2;

    for (size_t i = 0; i < n; i++) {
        if (p1[i] != p2[i])
            return (int)p1[i] - (int)p2[i];
    }

    return 0;
}

void *memmove(void *dest, const void *src, size_t numBytes) {
    const uint8_t *s = (const uint8_t *)src;
    uint8_t *d = (uint8_t *)dest;

    if (numBytes == 0 || dest == src)
        return dest;

    if (d < s || d >= s + numBytes) {
        for (size_t i = 0; i < numBytes; ++i)
            d[i] = s[i];
    } else {
        for (size_t i = numBytes; i > 0; --i)
            d[i - 1] = s[i - 1];
    }

    return dest;
}
