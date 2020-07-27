#ifndef __REGION__H__
#define __REGION__H__

typedef struct Point
{
    float x;
    float y;
} Point;

int is_target_point_in_hotspot(Point target, Point* hotspot_points, int hotspot_point_num);
int is_point_in_polygon(Point target, Point* hotspot_points, int hotspot_point_num);
float max(float a, float b);
float min(float a, float b);

#endif /* __REGION__H__ */
