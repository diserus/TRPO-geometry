#include <math.h>

#include <libgeometry/intersects.h>
#include <libgeometry/parser.h>

double distance(Circle a, Circle b)
{
    double d;
    d = sqrt(pow(b.point.x - a.point.x, 2) + pow(b.point.y - a.point.y, 2));
    return d;
}

bool is_intersect_circles(Circle a, Circle b)
{
    double d = distance(a, b);
    if (d > a.radius + b.radius) {
        return false;
    }
    return true;
}

bool is_intersect_triangles_help(Triangle a, Triangle b)
{
    double f1 = a.point1.x * b.point2.y - a.point1.y * b.point2.x;
    double f2 = a.point2.x * b.point3.y - a.point2.y * b.point3.x;
    double f3 = a.point3.x * b.point1.y - a.point3.y * b.point1.x;

    return (f1 > 0 || f2 > 0 || f3 > 0);
}

bool is_intersect_triangles(Triangle a, Triangle b)
{
    bool res1 = is_intersect_triangles_help(a, b);
    bool res2 = is_intersect_triangles_help(b, a);
    return (res1 && res2);
}

bool is_intersect_circle_line(Circle circle, Point p1, Point p2)
{
    double x01 = p1.x - circle.point.x;
    double y01 = p1.y - circle.point.y;
    double x02 = p2.x - circle.point.x;
    double y02 = p2.y - circle.point.y;

    double dx = x02 - x01;
    double dy = y02 - y01;

    double a = dx * dx + dy * dy;
    double b = 2.0f * (x01 * dx + y01 * dy);
    double c = x01 * x01 + y01 * y01 - circle.radius * circle.radius;

    if (-b < 0)
        return (c < 0);
    if (-b < (2.0f * a))
        return (4.0f * a * c - b * b < 0);
    return (a + b + c < 0);
}

bool is_intersect_circle_triangle(Circle circle, Triangle tr)
{
    bool res1 = is_intersect_circle_line(circle, tr.point1, tr.point2);
    bool res2 = is_intersect_circle_line(circle, tr.point2, tr.point3);
    bool res3 = is_intersect_circle_line(circle, tr.point1, tr.point3);

    if (res1 || res2 || res3)
        return true;
    return false;
}
