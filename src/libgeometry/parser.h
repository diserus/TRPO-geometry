#pragma once

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_SIZE 32
#define STR_SIZE 512
#define MAX_CIRCLES 50
#define MAX_TRIANGLES 50

typedef struct {
    double x;
    double y;
} Point;

typedef struct {
    Point point;
    double radius;
    double area;
    double perimetr;
    char name[NAME_SIZE];
    int number;

} Circle;

typedef struct {
    Point point1;
    Point point2;
    Point point3;
    Point point4;
    char name[NAME_SIZE];
    double perimeter;
    double area;
    int number;

} Triangle;

Circle parse_circle(char* geomName, int number, char* buff);
Triangle parse_triangle(char* geomName, int number, char* buff);
void print_circle_info(Circle* circle);
void print_triangle_info(Triangle* trinagle);
void print_geometry(
        Circle circles[],
        int circles_cnt,
        Triangle triangles[],
        int triangle_cnt,
        int queue[]);
void parser(FILE* file);
