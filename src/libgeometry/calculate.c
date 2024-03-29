#include <math.h>
#include <stdio.h>

#include <libgeometry/calculate.h>

double calc_perimetr_circle(Circle* circle)
{
    return 2 * M_PI * circle->radius;
}

double calc_area_circle(Circle* circle)
{
    return M_PI * powf(circle->radius, 2);
}

double calc_perimetr_triangle(Triangle* triangle)
{
    double len1, len2, len3;
    len1
            = sqrt(pow(triangle->point1.x - triangle->point2.x, 2)
                   + pow(triangle->point1.y - triangle->point2.y, 2));
    len2
            = sqrt(pow(triangle->point1.x - triangle->point3.x, 2)
                   + pow(triangle->point1.y - triangle->point3.y, 2));
    len3
            = sqrt(pow(triangle->point2.x - triangle->point3.x, 2)
                   + pow(triangle->point2.y - triangle->point3.y, 2));
    return len1 + len2 + len3;
}

double calc_area_triangle(Triangle* triangle)
{
    double len1, len2, len3;
    len1
            = sqrt(pow(triangle->point1.x - triangle->point2.x, 2)
                   + pow(triangle->point1.y - triangle->point2.y, 2));
    len2
            = sqrt(pow(triangle->point1.x - triangle->point3.x, 2)
                   + pow(triangle->point1.y - triangle->point3.y, 2));
    len3
            = sqrt(pow(triangle->point2.x - triangle->point3.x, 2)
                   + pow(triangle->point2.y - triangle->point3.y, 2));
    double p = (len1 + len2 + len3) / 2;
    return sqrt(p * (p - len1) * (p - len2) * (p - len3));
}