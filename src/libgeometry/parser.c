#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libgeometry/calculate.h>
#include <libgeometry/lexer.h>
#include <libgeometry/parser.h>

Circle parse_circle(char* geomName, int number, char* buff)
{
    Circle circle;
    strcpy(circle.name, geomName);
    circle.number = number;
    sscanf(buff,
           "circle(%lf %lf, %lf)",
           &circle.point.x,
           &circle.point.y,
           &circle.radius);
    circle.perimetr = calc_perimetr_circle(&circle);
    circle.area = calc_area_circle(&circle);
    if (circle.radius < 0) {
        printf("Error: radius must be positive");
        exit(EXIT_FAILURE);
    }
    return circle;
}

Triangle parse_triangle(char* geomName, int number, char* buff)
{
    Triangle triangle;
    strcpy(triangle.name, geomName);
    triangle.number = number;
    sscanf(buff,
           "triangle((%lf %lf, %lf %lf, %lf %lf, %lf %lf))",
           &triangle.point1.x,
           &triangle.point1.y,
           &triangle.point2.x,
           &triangle.point2.y,
           &triangle.point3.x,
           &triangle.point3.y,
           &triangle.point4.x,
           &triangle.point4.y);
    triangle.perimeter = calc_perimetr_triangle(&triangle);
    triangle.area = calc_area_triangle(&triangle);
    if (triangle.point4.x != triangle.point1.x
        || triangle.point4.y != triangle.point1.y) {
        printf("Error: first and last point must be equivalent");
        exit(EXIT_FAILURE);
    }
    return triangle;
}

void print_circle_info(Circle* circle)
{
    printf("%d. %s(%.2lf %.2lf, %.2lf)\n",
           circle->number,
           circle->name,
           circle->point.x,
           circle->point.y,
           circle->radius);
    printf("\tarea = %.4f\n", circle->area);
    printf("\tperimeter = %.4f\n", circle->perimetr);
}

void print_triangle_info(Triangle* triangle)
{
    printf("%d. %s((%.1lf %.1lf, %.1lf %.1lf, %.1lf %.1lf, %.1lf %.1lf))\n",
           triangle->number,
           triangle->name,
           triangle->point1.x,
           triangle->point1.y,
           triangle->point2.x,
           triangle->point2.y,
           triangle->point3.x,
           triangle->point3.y,
           triangle->point4.x,
           triangle->point4.y);
    printf("\tarea = %.3f\n", triangle->area);
    printf("\tperimeter = %.3f\n", triangle->perimeter);
}

void print_geometry(
        Circle circles[],
        int circles_cnt,
        Triangle triangles[],
        int triangle_cnt,
        int queue[])
{
    int c = 0;
    int t = 0;
    for (int i = 1; i <= circles_cnt + triangle_cnt; i++) {
        if (queue[i] == 1) {
            print_circle_info(&circles[c]);
            c++;
        } else if (queue[i] == 2) {
            print_triangle_info(&triangles[t]);
            t++;
        }
    }
}

void parser(FILE* file)
{
    char buff[STR_SIZE];
    char geomName[NAME_SIZE];
    int circles_cnt = 0;
    Circle circles[MAX_CIRCLES];
    int triangle_cnt = 0;
    int cnt = 1;
    Triangle triangles[MAX_TRIANGLES];
    int queue[MAX_CIRCLES + MAX_TRIANGLES] = {0};
    while (fgets(buff, STR_SIZE, file) != NULL) {
        to_lower_string(buff);
        sscanf(buff, "%[^(]", geomName);
        remove_extra_spaces(buff);
        token_after_bracket(buff);
        check_unexpected_brackets(buff, geomName);
        check_near_brackets(buff);
        if (strcmp(geomName, "circle") == 0) {
            circles[circles_cnt++] = parse_circle(geomName, cnt, buff);
            queue[cnt++] = 1;

        } else if (strcmp(geomName, "triangle") == 0) {
            triangles[triangle_cnt++] = parse_triangle(geomName, cnt, buff);
            queue[cnt++] = 2;

        } else {
            printf("Error: expected 'circle' or 'triangle'");
            exit(EXIT_FAILURE);
        }
        str_clear(geomName, NAME_SIZE);
    }

    print_geometry(circles, circles_cnt, triangles, triangle_cnt, queue);
}
