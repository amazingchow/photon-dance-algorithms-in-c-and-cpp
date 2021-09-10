#ifndef __REGION__H__
#define __REGION__H__

#include "style.h"

int is_target_point_inside_hotspot(Point2D target, Point2D *hotspot, int hotspot_point_num);
int is_point_inside_polygon(Point2D pt, Point2D *polygon, int polygon_point_num);

#endif /* __REGION__H__ */
