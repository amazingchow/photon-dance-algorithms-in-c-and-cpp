#include <stdio.h>
#include "kmp.h"

int main(int argc, char const *argv[])
{
    const char* s = "oopabcabcabcabcefgmn";
    const char* p = "abcabcabcefg";

    printf("matched index i = %d\n", kmp(s, p));

    return 0;
}
