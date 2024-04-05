#include <libgeometry/parser.h>
int main()
{
    FILE* file = NULL;
    file = fopen("main.txt", "r");
    if (file == NULL) {
        printf("The file doesn't open\n");
        return 1;
    } else

    {
        parser(file);
        fclose(file);
    }
    return 0;
}
