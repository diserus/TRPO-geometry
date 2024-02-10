#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define _USE_MATH_DEFINES

int main()
{
    FILE *geometry;
    geometry = fopen("main.txt","r");
    if (geometry)
    {
        char buff[256];
        while((fgets(buff,256,geometry))!=NULL)
        {
            int x,y,r;
            char name[20];
            sscanf(buff,"%[^(](%d %d, %d)", name, &x, &y, &r);
            printf("%s(%d %d, %d)\n",name,x,y,r);
            printf("perimetr = %f.4\n", 2*M_PI*r);
            printf("area: %f\n\n",2*M_PI*pow(r,2));
        }
    }
    return 1;
}