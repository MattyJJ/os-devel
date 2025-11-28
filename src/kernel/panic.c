#include <kernel/panic.h>

#include <kernel/vga.h>

#include <std/stdio.h>

[[noreturn]] void _panic(const char *msg, const char *file, int line,
                         const char *func) {
    vga_set_color(VGA_RED, VGA_BLACK);

    printf("%s:%d %s(): %s\n", file, line, func, msg);

    for (;;)
        __asm__ volatile("hlt");
}
