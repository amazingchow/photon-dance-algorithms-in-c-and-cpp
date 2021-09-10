#ifndef __KMP__H__
#define __KMP__H__

#include <malloc.h>
#include <stdio.h>
#include <string.h>

int kmp(const char *s, const char *p);
void get_next(const char *p, int *next);

#endif /* __KMP__H__ */
