#include <libgeometry/lexer.h>

void remove_extra_spaces(char* str)
{
    int i, j;
    for (i = 0, j = 0; str[i]; i++) {
        if (!isspace((char)str[i]) || (i > 0 && !isspace((char)str[i - 1]))) {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

void to_lower_string(char* string)
{
    while (*string != '\0') {
        *string = tolower(*string);
        string++;
    }
}

void str_clear(char* str, size_t size)
{
    for (int i = 0; i < size; i++)
        str[i] = '\0';
}

int count_char(char* str, char target)
{
    int cnt = 0;
    for (int i = 0; str[i]; i++) {
        if (str[i] == target)
            cnt++;
    }
    return cnt;
}

void check_near_brackets(char* str)
{
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == '(' && str[i + 1] != '(') {
            int j = i + 1;

            while (str[j] != ')' && str[j] != '\0') {
                if (!isdigit(str[j]) && str[j] != '.' && str[j] != '-'
                    && str[j] != ' ' && str[j] != ',') {
                    printf("Error at column: expected '<double>'\n");
                    exit(EXIT_FAILURE);
                } else if (str[j] == '.') {
                    if ((!isdigit(str[j - 1]) && !isdigit(str[j + 1]))
                        || (isdigit(str[j - 1]) && !isdigit(str[j + 1]))
                        || (!isdigit(str[j - 1]) && isdigit(str[j + 1]))) {
                        printf("Error: unexpected '.'");
                        exit(EXIT_FAILURE);
                    }
                } else if (str[j] == '-') {
                    if (!isdigit(str[j + 1]) || (isdigit(str[j - 1]) && isdigit(str[j + 1]))) {
                        printf("Error: unexpected '-'");
                        exit(EXIT_FAILURE);
                    }
                }
                j++;
            }
        }
        i++;
    }
    if (count_char(str, '(') == 1) {
        if (count_char(str, ',') > 1) {
            printf("Error: unexpected ','");
            exit(EXIT_FAILURE);
        }
        if (count_char(str, ',') == 0)
        {
            printf("Error: expected ','");
            exit(EXIT_FAILURE);
        }
        if (count_char(str, ' ') != 2) {
            printf("Error: not enought arguments");
            exit(EXIT_FAILURE);
        }

    } else if (count_char(str, '(') == 2) {
        if (count_char(str, ',') > 3) {
            printf("Error: unexpected ','");
            exit(EXIT_FAILURE);
        }
        if (count_char(str, ',') == 0 || count_char(str, ',') == 1 || count_char(str, ',') == 2)
        {
            printf("Error: expected ','");
            exit(EXIT_FAILURE);
        }
        if (count_char(str, ' ') != 7) {
            printf("Error: not enought arguments");
            exit(EXIT_FAILURE);
        }
    }
}

void token_after_bracket(char* str)
{
    int i = 0;
    int after_bracket = 0;

    while (str[i] != '\0') {
        if (str[i] == ')') {
            after_bracket = 1;
        } else if (
                after_bracket == 1 && str[i] != ' ' && str[i] != '\n'
                && str[i] != '\r' && str[i] != '\0') {
            printf("Error: unexpected token\n");
            exit(EXIT_FAILURE);
        }

        i++;
    }
}

void check_unexpected_brackets(char* str, char* geomName)
{
    if (strcmp(geomName, "circle") == 0) {
        if (count_char(str, '(') != 1 || count_char(str, ')') != 1) {
            printf("Error: unexpected brackets");
            exit(EXIT_FAILURE);
        }
    } else if (strcmp(geomName, "triangle") == 0) {
        if (count_char(str, '(') != 2 || count_char(str, ')') != 2) {
            printf("Error: unexpected brackets");
            exit(EXIT_FAILURE);
        }
    }
}
