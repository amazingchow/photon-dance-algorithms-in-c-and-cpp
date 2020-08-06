#include "intersect.h"

int is_intersected(Point* l1, Point* l2)
{
    Point a = l1[0], b = l1[1], c = l2[0], d = l2[1];
    double u, v, w, z;
	u = (c.x -a.x) * (b.y - a.y) - (b.x - a.x) * (c.y - a.y);
	v = (d.x -a.x) * (b.y - a.y) - (b.x - a.x) * (d.y - a.y);
	w = (a.x -c.x) * (d.y - c.y) - (d.x - c.x) * (a.y - c.y);
	z = (b.x -c.x) * (d.y - c.y) - (d.x - c.x) * (b.y - c.y);
	return u * v <= 0.1 && w * z <= 0.1;
};
