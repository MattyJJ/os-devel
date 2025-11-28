#include <kernel/assert.h>
#include <kernel/kalloc.h>
#include <kernel/panic.h>
#include <kernel/vga.h>

#include <std/stdio.h>
#include <std/string.h>

static void kernel_init(void) {
    vga_init();
    printf("[ INIT ] VGA Initiliazed.\n");

    printf("[ INIT ] Initializing KHeap.\n");
    kheap_init();
}

static void kernel_run(void) {
    printf("[ OK ] Running main loop\n");

    printf("Hello, %s!\n", "World");

    while (1)
        __asm__ volatile("hlt");
}

static void kernel_destroy(void) { printf("\n[ BYE ] Shutting down..."); }

__attribute__((noreturn)) void kernel_entry(void) {
    kernel_init();
    kernel_run();

    kernel_destroy();
    __builtin_unreachable();
}
