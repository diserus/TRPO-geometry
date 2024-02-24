#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define M_PI 3.14159265358979323846
typedef struct
{
    float x,y,r;
    char name[20];
    int number;
} Circle;

void parseCircle(char* buff,Circle* circle)
{
    static int n = 0;
    sscanf(buff,"%[^(](%f %f, %f)",circle->name,&circle->x,&circle->y,&circle->r);
    circle->number = ++n;
}
void printCircle(Circle* circle)
{
    printf("%d. %s(%.f %.f, %.1f)\n",circle->number,circle->name,circle->x, circle->y, circle->r);
} 
int main()
{
    Circle circle;

    FILE *geometry;
    geometry = fopen("main.txt","r");
    if (geometry == NULL)
    {
        printf("The file doesn't open");
        return 1;
    }
    
    char buff[256];
    while((fgets(buff,256,geometry))!=NULL)
    {
        parseCircle(buff,&circle);
        printCircle(&circle);
    }
    fclose(geometry);
    // while((fgets(buff,256,geometry))!=NULL)
    // {
    //     char name[20];
    //     sscanf(buff,"%[^(]", name);
    //     if (strcmp(name,"circle")!=0 || strcmp(name,"triangle")!=0)
    //     {
    //         printf("\nError: expected 'circle' or 'triangle'");
    //         return 1;
    //     }
    //     char* first_bracket = strchr(buff, '(');
    //     if(first_bracket == NULL)
    //     {
    //         puts("expected '('");
    //         return 1;
    //     }
    //     if (strcmp(name,"circle")==0)
    //     {
    //         numberShape++;
    //         float x,y,r;
    //         sscanf(buff, "circle(%f %f, %f)", &x, &y, &r);
    //         float perimetr = 2*M_PI*r;
    //         float area = M_PI*pow(r,2);
    //         printf("%d. %s(%.f %.f, %.1f)\n",numberShape,name,x,y,r);
    //         printf("perimeter = %.4f\n", perimetr);
    //         printf("area = %.4f\n\n",area);
    //     }
    //     if (strcmp(name,"triangle")==0)
    //     {
    //         numberShape++;
    //         float x1,y1,x2,y2,x3,y3;
    //         sscanf(buff, "triangle((%f %f, %f %f, %f %f))", &x1, &y1, &x2,&y2,&x3,&y3);
    //         float perimetr = sqrt(pow(x2-x1,2)+pow(y2-y1,2))+sqrt(pow(x3-x2,2)+pow(y3-y2,2))+sqrt(pow(x3-x1,2)+pow(y3-y1,2));
    //         float area = 0.5*fabs((x2-x1)*(y3-y1)-(x3-x1)*(y2-y1));
    //         printf("%d. %s((%.f %.f, %.f %.f, %.f %.f))\n",numberShape,name,x1, y1, x2, y2, x3, y3);
    //         printf("perimeter = %.3f\n", perimetr);
    //         printf("area = %.f\n\n",area);  
    //     }
    // }
    
    return 0;
}