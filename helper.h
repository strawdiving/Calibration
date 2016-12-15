#ifndef HELPER_H
#define HELPER_H

#define DEG_TO_RAD 	0.01745329251994
#define RAD_TO_DEG 	57.2957795130823

#define PI 3.14159265358979323846
#define PI_2 1.57079632679489661923

#define CONSTANTS_RADIUS_OF_EARTH 6371393

#define NORTHERN_HEMISPHERE 1
#define EASTERN_HEMISPHERE 1

//(1023,584)
#define ROUTEPLAN_W 742 //width of routeplan label
#define ROUTEPLAN_H 604 //height of routeplan label

#define DISPLAY_W 658 //width of display label
#define DISPLAY_H 431 //height of display label

#include <qmath.h>
#include <QPointF>
#include <QString>

namespace Helper {
int gps_to_local(QPointF global_position, qreal *x, qreal *y, QPointF home_position) ;//y is North, x is East
void local_to_gps(QPointF local_position, double *lat, double *lon,QPointF home_position);

qreal point_dist(QPointF p1,QPointF p2);
float point_line_dist(float m, float n, float k, float b);

void scale(QList<QPointF> list, float *_draw_scale,float *_min_x,float *_min_y);
void scale1(QList<QPointF> list, float *_draw_scale,float *_min_x,float *_min_y);

float limitAngleToPMPIf(float angle);

quint32 crc32(const quint8 *src, unsigned len, unsigned state);
}

#endif
