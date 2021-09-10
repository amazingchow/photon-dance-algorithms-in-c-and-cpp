#include "kmp.h"

int
kmp(const char *s, const char *p) {
    int i = 0, j = 0;
    int s_len = strlen(s);
    int p_len = strlen(p);

    int *next = (int *)malloc(sizeof(int) * p_len);
    memset(next, 0, sizeof(int) * p_len);

    get_next(p, next);

    while (i < s_len && j < p_len) {
        if (j == -1 || s[i] == p[j]) {
            i++;
            j++;
        } else {
            j = next[j];
        }
    }

    if (j == p_len) {
        return i - j;
    }

    return -1;
}

void
get_next(const char *p, int *next) {
    int i = 0, j = -1;
    int p_len = strlen(p);

    next[0] = -1;
    while (i < p_len) {
        if (j == -1 || p[i] == p[j]) {
            i++;
            j++;
            next[i] = j;
        } else {
            j = next[j];
        }
    }
}
