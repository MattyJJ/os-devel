#include <kernel/kalloc.h>

#define HEAP_SIZE (1024 * 512)

static uint8_t heap_buffer[HEAP_SIZE];

static arena heap_region;

void kheap_init() {
    heap_region.data = heap_buffer;
    heap_region.capacity = sizeof(heap_buffer);
    heap_region.offset = 0;
}

static size_t align_forward(size_t p, size_t a) {
    size_t m = a - 1;
    return (p + m) & ~m;
}

static void *heap_alloc_align(arena *region, size_t size, size_t align) {
    size_t off = align_forward(region->offset, align);
    size_t next = off + size;
    if (next > region->capacity)
        return 0;
    void *ptr = region->data + off;
    region->offset = next;
    return ptr;
}

void *kmalloc(size_t size) { return heap_alloc_align(&heap_region, size, 8); }
void kfree(void *ptr) { (void)ptr; }
