#ifndef __PANIC_H
#define __PANIC_H

[[noreturn]] void _panic(const char *msg, const char *file, int line,
                         const char *func);

#define panic(msg) _panic((msg), __FILE__, __LINE__, __func__)

#endif
