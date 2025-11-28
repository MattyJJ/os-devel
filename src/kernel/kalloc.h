#ifndef __ALLOC_H
#define __ALLOC_H

#include <std/stddef.h>
#include <std/stdint.h>

typedef struct {
    size_t capacity;
    size_t offset;
    uint8_t *data;
} arena;

void kheap_init();
void *kmalloc(size_t size);
void kfree(void *ptr);

#endif
