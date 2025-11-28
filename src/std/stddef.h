#ifndef __STDDEF_H
#define __STDDEF_H

typedef __typeof__(sizeof(int)) size_t;
typedef __typeof__((char *)0 - (char *)0) ptrdiff_t;

#define NULL ((void *)0)

#define offsetof(t, m) ((size_t)&((t *)0)->m)

#endif
