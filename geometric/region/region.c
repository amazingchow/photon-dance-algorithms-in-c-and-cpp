#include "region.h"

int
is_target_point_inside_hotspot(Point2D target, Point2D *hotspot, int hotspot_point_num) {
    if (hotspot_point_num <= 2) {
        return 0;
    }

    // 如果目标点不在热区外接矩形的范围内, 则目标点一定不在热区内
    float min_x = hotspot[0].x;
    float min_y = hotspot[0].y;
    float max_x = hotspot[0].x;
    float max_y = hotspot[0].y;

    for (int i = 1; i < hotspot_point_num; i++) {
        if (hotspot[i].x < min_x) {
            min_x = hotspot[i].x;
        } else if (hotspot[i].x > max_x) {
            max_x = hotspot[i].x;
        }
        if (hotspot[i].y < min_y) {
            min_y = hotspot[i].y;
        } else if (hotspot[i].y > max_y) {
            max_y = hotspot[i].y;
        }
    }

    if (target.x < min_x || target.x > max_x || target.y < min_y || target.y > max_y) {
        return 0;
    }

    return is_point_inside_polygon(target, hotspot, hotspot_point_num);
}

/*
    Ray-Crossing算法

    从目标点水平向右引一条射线, 记录该射线与多边形每条边的相交次数.
    如果总相交次数为奇数, 说明目标点位于多边形内部; 如果为偶数, 说明目标点位于多边形外部.
*/
int
is_point_inside_polygon(Point2D pt, Point2D *polygon, int polygon_point_num) {
    int n_cross = 0;

    for (int i = 0; i < polygon_point_num; i++) {
        // p1是某条边的一个节点
        Point2D p1 = polygon[i];
        // p2是沿着顺时针方向看去该边的下一个节点
        Point2D p2 = polygon[(i + 1) % polygon_point_num];

        // 边界情况一般被认为在多边形内部
        if ((pt.x == p1.x && pt.y == p1.y) || (pt.x == p2.x && pt.y == p2.y)) {
            return 1;
        }

        // 先以y轴方向来判断
        if (p1.y == p2.y) {
            if ((pt.y == p1.y) && ((pt.x > p1.x) != (pt.x > p2.x) || (pt.x < p1.x) != (pt.x < p2.x))) {
                return 1;
            }
            // 目标点不在这条水平线段上, 跳过
            continue;
        }

        // 如果目标点高于这条斜线段, 跳过
        if (pt.y > (p1.y < p2.y ? p2.y : p1.y)) {
            continue;
        }
        // 如果目标点低于这条斜线段, 跳过
        if (pt.y < (p1.y > p2.y ? p2.y : p1.y)) {
            continue;
        }

        // 过目标点, 画一条水平线, x是这条水平线与当前斜线段的交点的横坐标
        float x = (pt.y - p1.y) * (p2.x - p1.x) / (p2.y - p1.y) + p1.x;
        if (x > pt.x) {
            // 如果交点在目标点右边, 相交次数加一
            n_cross++;
        }
    }

    // 如果是奇数，说明在多边形内部; 否则在多边形外部
    if (n_cross % 2 == 1) {
        return 1;
    }
    return 0;
}
