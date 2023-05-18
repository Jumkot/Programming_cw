#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>
#define MAX_SIZE 1000

int check_correct_letter(wchar_t c);
void check_correct_file(FILE* file);
wchar_t** prepare_two_dim_arr(wchar_t** arr);
void skip_trash(wchar_t* arr, int num);
void skip_n(wchar_t* arr, int num);
int pal(wchar_t* arr, int num);