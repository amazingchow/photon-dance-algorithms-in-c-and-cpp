#include <stdio.h>
#include "intersect.h"

int main(int argc, char const *argv[])
{
    Point2D l1[] = {{x: 10, y: 10}, {x: 110, y: 110}};
    Point2D l2[] = {{x: 30, y: 50}, {x: 70, y: 20}};
    Point2D l3[] = {{x: 40, y: 30}, {x: 70, y: 20}};

    printf("%d\n", is_two_lines_intersected(l1, l2));
    printf("%d\n", is_two_lines_intersected(l1, l3));

    return 0;
}
