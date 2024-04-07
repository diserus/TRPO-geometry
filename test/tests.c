#include <ctest.h>
#include <libgeometry/calculate.h>
#include <libgeometry/intersects.h>
#include <libgeometry/lexer.h>
#include <libgeometry/parser.h>
#include <stdio.h>

CTEST(lexer, to_lower_string)
{
    char string1[] = "Circle";
    char string2[] = "TRIangle";
    const char expected1[] = "circle";
    const char expected2[] = "triangle";

    to_lower_string(string1);
    to_lower_string(string2);

    ASSERT_STR(string1, expected1);
    ASSERT_STR(string2, expected2);
}

CTEST(lexer, count_char)
{
    char target = 'q';
    char string[] = "uq";
    int expected = 1;
    int result = count_char(string, target);
    ASSERT_EQUAL(expected, result);
}

CTEST(lexer, remove_extra_spaces)
{
    char string[] = "1   5";
    char expected[] = "1 5";
    char string2[] = "1   5 1    8";
    char expected2[] = "1 5 1 8";
    remove_extra_spaces(string);
    remove_extra_spaces(string2);
    ASSERT_STR(expected, string);
    ASSERT_STR(expected2, string2);
}

CTEST(lexer, str_clear)
{
    char string[] = "123456789";
    char expected[] = "";
    str_clear(string, strlen(string));
    ASSERT_STR(expected, string);
}

CTEST(calculate, calc_area_circle)
{
    Circle circle = {.radius = 2};
    double expected = 12.566;
    double result = calc_area_circle(&circle);
    double tol = 1e-3;
    ASSERT_DBL_NEAR_TOL(expected, result, tol);
}

CTEST(calculate, calc_perimetr_circle)
{
    Circle circle = {.radius = 2.5};
    double expected = 15.707;
    double result = calc_perimetr_circle(&circle);
    double tol = 1e-3;
    ASSERT_DBL_NEAR_TOL(expected, result, tol);
}

CTEST(calculate, calc_area_triangle)
{
    Triangle triangle = {{1, 5}, {7, 6}, {1, 2}, {1, 5}};
    double expected = 9;
    double result = calc_area_triangle(&triangle);
    ASSERT_DBL_NEAR(expected, result);
}

CTEST(calculate, calc_perimetr_triangle)
{
    Triangle triangle = {{1, 5}, {7, 6}, {1, 2}, {1, 5}};
    double expected = 16.29;
    double result = calc_perimetr_triangle(&triangle);
    double tol = 1e-2;
    ASSERT_DBL_NEAR_TOL(expected, result, tol);
}
