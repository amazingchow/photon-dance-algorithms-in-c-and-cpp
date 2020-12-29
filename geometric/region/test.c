#include <stdio.h>
#include "region.h"

int main(int argc, char const *argv[])
{
    Point2D target1 = {x: 20, y: 20};
    Point2D target2 = {x: 15, y: 5};
    Point2D target3 = {x: 5, y: 15};
    Point2D target4 = {x: 105, y: 115};
    Point2D target5 = {x: 115, y: 105};
    Point2D hotspot[]  = {{x: 10, y: 10}, {x: 10, y: 110}, {x: 110, y: 110}, {x: 110, y: 10}};

    printf("%d\n", is_target_point_inside_hotspot(target1, hotspot, 4));
    printf("%d\n", is_target_point_inside_hotspot(target2, hotspot, 4));
    printf("%d\n", is_target_point_inside_hotspot(target3, hotspot, 4));
    printf("%d\n", is_target_point_inside_hotspot(target4, hotspot, 4));
    printf("%d\n", is_target_point_inside_hotspot(target5, hotspot, 4));

    return 0;
}
