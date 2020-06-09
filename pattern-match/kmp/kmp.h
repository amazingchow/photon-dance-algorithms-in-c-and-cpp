#ifndef __KMP__H__
#define __KMP__H__

#include <malloc.h>
#include <stdio.h>
#include <string.h>

void get_next(const char * p, int * next);
int kmp(const char * s, const char * p);

#endif /* __KMP__H__ */
