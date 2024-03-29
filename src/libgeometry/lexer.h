#pragma once

void remove_extra_spaces(char* str);
void to_lower_string(char* string);
void str_clear(char* str, size_t size);
int count_char(char* str, char target);
void check_near_brackets(char* str);
void check_unexpected_brackets(char* str, char* geomName);
void token_after_bracket(char* str);