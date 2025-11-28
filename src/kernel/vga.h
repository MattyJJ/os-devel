#ifndef __VGA_H
#define __VGA_H

#include <std/stddef.h>
#include <std/stdint.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_BUFFER ((uint16_t *)0xB8000)

#define VGA_BLACK 0
#define VGA_BLUE 1
#define VGA_GREEN 2
#define VGA_CYAN 3
#define VGA_RED 4
#define VGA_MAGENTA 5
#define VGA_BROWN 6
#define VGA_LIGHT_GRAY 7
#define VGA_DARK_GRAY 8
#define VGA_LIGHT_BLUE 9
#define VGA_LIGHT_GREEN 10
#define VGA_LIGHT_CYAN 11
#define VGA_LIGHT_RED 12
#define VGA_PINK 13
#define VGA_YELLOW 14
#define VGA_WHITE 15

void vga_init(void);
void vga_putc(char c);
void vga_write(const char *data, size_t len);
void vga_puts(const char *s);
void vga_writeln(const char *s);

void vga_clear(void);
void vga_set_color(uint8_t fg, uint8_t bg);

uint16_t vga_get_cursor(void);
void vga_set_cursor(uint16_t pos);
void vga_enable_cursor(void);
void vga_disable_cursor(void);

#endif
