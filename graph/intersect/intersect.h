#ifndef __INTERSECT__H__
#define __INTERSECT__H__

typedef struct Point
{
    float x;
    float y;
} Point;

int is_intersected(Point* l1, Point* l2);

#endif /* __INTERSECT__H__ */
