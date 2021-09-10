#include "intersect.h"

// 参考资料: https://www.cnblogs.com/wuwangchuxin0924/p/6218494.html
int
is_two_lines_intersected(Point2D *la, Point2D *lb) {
    Point2D a1 = la[0], a2 = la[1], b1 = lb[0], b2 = lb[1];
    double u, v, w, z;
    u = (b1.x - a1.x) * (a2.y - a1.y) - (a2.x - a1.x) * (b1.y - a1.y);
    v = (b2.x - a1.x) * (a2.y - a1.y) - (a2.x - a1.x) * (b2.y - a1.y);
    w = (a1.x - b1.x) * (b2.y - b1.y) - (b2.x - b1.x) * (a1.y - b1.y);
    z = (a2.x - b1.x) * (b2.y - b1.y) - (b2.x - b1.x) * (a2.y - b1.y);
    return u * v <= 0.0001 && w * z <= 0.0001;
};
