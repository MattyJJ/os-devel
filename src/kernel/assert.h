#ifndef __ASSERT_H
#define __ASSERT_H

#include <kernel/panic.h>

#define ASSERT(x)                                                              \
    do {                                                                       \
        if (!(x)) {                                                            \
            panic("Assertion failed: " #x);                                    \
        }                                                                      \
    } while (0)
#endif
