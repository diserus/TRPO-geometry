#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define M_PI 3.14159265358979323846
typedef struct
{
    float x,y,r;
    char name[20];
    int number;
} Circle;

bool parseCircle(char* buff,Circle* circle)
{
    static int n = 0;
    int args=sscanf(buff,"%[^(](%f %f, %f)",circle->name,&circle->x,&circle->y,&circle->r)-1;
    circle->number = ++n;
    if (args<1)
    {
        printf("Error: figure doesn't read\n\n");
        return NULL;
    }
    if (circle->r<0)
    {
        printf("Error: incorrect radius\n\n");
        return NULL;
    }
    if (args!=3)
    {
        printf("Error: count of args must be 3\n\n");
        return NULL;
    }
    if (strcmp(circle->name,"circle")!=0)
    {
        printf("Error: expected 'circle'\n\n");
        return NULL;
    }
    return 1;
}
bool parse(char* buff)
{
    if(strlen(buff) <= 1)
    {
        printf("Error: empty input\n");
        return NULL;
    }
    char* first_bracket = strchr(buff, '(');
    if(first_bracket == NULL)
    {
        printf("Error: expected '('\n");
        return NULL;
    }
    char* second_bracket = strrchr(buff, ')');
    if(second_bracket == NULL)
    {
        printf("Error: expected ')'\n");
        return NULL;
    }
    if(strlen(second_bracket) > 2)
    {
        printf("Error: unexpected token\n");
        return NULL;
    }
    int brackets_count = 1;
    for(int i = 1; i < strlen(first_bracket); i++)
    {
        if(first_bracket[i] == '(')
        {
            brackets_count += 1;
        } else if(first_bracket[i] == ')') 
        {
            brackets_count -= 1;
        }
    }

    if(brackets_count > 0)
    {
        printf("Error: brackets are not closed\n");
        return NULL;
    }
    return 1;
}
void printCircle(Circle* circle)
{
    printf("%d. %s(%.f %.f, %.1f)\n",circle->number,circle->name,circle->x, circle->y, circle->r);
    float perimetr = 2*M_PI*circle->r;
    float area = M_PI*pow(circle->r,2);
    printf("perimeter = %.4f\n", perimetr);
    printf("area = %.4f\n\n",area);
} 
int main()
{
    Circle circle;

    FILE *geometry;
    geometry = fopen("main.txt","r");
    if (geometry == NULL)
    {
        printf("The file doesn't open\n");
        return 1;
    }
    
    char buff[256];
   
    
    if (fgets(buff, 256, geometry) == NULL)
    {
        printf("The file is empty\n");
        fclose(geometry);
        return 1;
    }
    else
    {
        do
        {
            if(parseCircle(buff,&circle) && parse(buff))
            {
                printCircle(&circle);
            }
            else 
            {
                printf("in circle %d",circle.number);
                fclose(geometry);
                return 1;
            }
        } while(fgets(buff, 256, geometry) != NULL);
    }
    
    fclose(geometry);
    
    return 0;
}