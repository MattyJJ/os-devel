#include <kernel/vga.h>

#include <std/memory.h>
#include <std/stdio.h>
#include <std/string.h>

static uint16_t *const vga_buffer = (uint16_t *)0xB8000;
static uint8_t cursor_x = 0;
static uint8_t cursor_y = 0;
static uint8_t current_fg = 7;
static uint8_t current_bg = 0;

static void update_cursor(void) {
    uint16_t pos = cursor_y * VGA_WIDTH + cursor_x;
    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t)(pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t)(pos >> 8));
}

static void scroll(void) {
    memmove(vga_buffer, vga_buffer + VGA_WIDTH,
            VGA_WIDTH * (VGA_HEIGHT - 1) * 2);
    uint16_t blank = ' ' | ((current_bg << 4 | current_fg) << 8);
    for (int i = (VGA_HEIGHT - 1) * VGA_WIDTH; i < VGA_WIDTH * VGA_HEIGHT; i++)
        vga_buffer[i] = blank;
    cursor_y = VGA_HEIGHT - 1;
}

void vga_init(void) {
    vga_clear();
    vga_set_color(VGA_WHITE, VGA_BLACK);
    update_cursor();
}

void vga_clear(void) {
    uint16_t blank = ' ' | ((current_bg << 4 | current_fg) << 8);
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++)
        vga_buffer[i] = blank;
    cursor_x = cursor_y = 0;
}

void vga_set_color(uint8_t fg, uint8_t bg) {
    current_fg = fg & 0xF;
    current_bg = bg & 0xF;
}

void vga_putc(char c) {
    if (c == '\n') {
        cursor_x = 0;
        if (++cursor_y >= VGA_HEIGHT)
            scroll();
    } else if (c == '\r') {
        cursor_x = 0;
    } else if (c == '\b') {
        if (cursor_x)
            cursor_x--;
        vga_putc(' ');
        if (cursor_x)
            cursor_x--;
    } else if (c >= ' ') {
        vga_buffer[cursor_y * VGA_WIDTH + cursor_x] =
            c | ((current_bg << 4 | current_fg) << 8);
        if (++cursor_x >= VGA_WIDTH) {
            cursor_x = 0;
            if (++cursor_y >= VGA_HEIGHT)
                scroll();
        }
    }
    update_cursor();
}

void vga_write(const char *data, size_t len) {
    for (size_t i = 0; i < len; i++)
        vga_putc(data[i]);
}
