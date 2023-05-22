#include "palindrom.h"

int check_correct_letter(wchar_t c)
{
    return (c >= L'А' && c <= L'Я') || (c >= L'а' && c <= L'я');
}

void check_correct_file(FILE* file)
{
    wchar_t ch;

    while ((ch = fgetwc(file)) != WEOF) {
        if (!(iswspace(ch) || iswpunct(ch) || check_correct_letter(ch))) {
            wprintf(L"Данные внутри предложенного файла неккоректны.\n");
            exit(-1);
        }
    }
    fseek(file, 0, SEEK_SET);
}

wchar_t** prepare_two_dim_arr(wchar_t** arr)
{
    for (int i = 0; i < MAX_SIZE; i++) {
        arr[i] = malloc(MAX_SIZE * sizeof(wchar_t));
        if (arr[i] == NULL) {
            wprintf(L"Не удалось выделить память.\n");
            for (int j = 0; j < i; j++) {
                free(arr[j]);
            }
            free(arr);
            return NULL;
        }
    }
    return arr;
}

void read_text(FILE* file, wchar_t** start, int* line, int* num)
{
    wchar_t ch;
    while ((ch = getwc(file)) != WEOF) {
        if (ch == L'.' || ch == L'?' || ch == L'!') {
            start[*line][*num] = L'\0';
            *num = 0;
            (*line)++;
        } else {
            start[*line][*num] = ch;
            (*num)++;
        }
    }
}

void skip_trash(wchar_t* arr, int num)
{
    int j = 0;
    for (int i = 0; i < num; i++) {
        if (arr[i] == L'\0') {
            break;
        }
        if (check_correct_letter(arr[i])) {
            arr[j] = towlower(arr[i]);
            j++;
        }
    }
    arr[j] = L'\0';
}

void skip_n(wchar_t* arr, int num)
{
    int j = 0;
    for (int i = 0; i < num; i++) {
        if (arr[i] == L'\0') {
            break;
        }
        if (arr[i] != L'\n') {
            arr[j] = arr[i];
            j++;
        }
    }
    arr[j] = L'\0';
}

void skip_empty(wchar_t** arr, int* line)
{
    int i = 0;
    while (i < *line) {
        if (arr[i][0] == L' ') {
            for (int j = 0; arr[i][j] != L'\0'; j++) {
                arr[i][j] = arr[i][j + 1];
            }
        }
        int num = wcslen(arr[i]);
        skip_n(arr[i], num);
        if (num == 0) {
            for (int k = i; k < *line - 1; k++) {
                arr[k] = arr[k + 1];
            }
            (*line)--;
        } else {
            i++;
        }
    }
}

int pal(wchar_t* arr, int num)
{
    for (int i = 0; i < (num / 2); i++) {
        if (arr[i] != arr[num - i - 1]) {
            return -1;
        }
    }
    return 0;
}
