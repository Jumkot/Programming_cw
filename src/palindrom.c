#include "palindrom.h"

int check_correct_letter(wchar_t c)
{
    return (c >= L'А' && c <= L'Я') || (c >= L'а' && c <= L'я');
}

void check_correct_file(FILE* file)
{
    int flag = 0;
    wchar_t ch;

    while ((ch = fgetwc(file)) != WEOF) {
        if (check_correct_letter(ch)) {
            flag = 1;
            break;
        }
    }

    if (!flag) {
        wprintf(L"Данные внутри предложенного файла неккоректны.\n");
        exit(-1);
    }

    fseek(file, 0, SEEK_SET);

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

void skip_trash(wchar_t* arr, int num)
{
    int j = 0;
    for (int i = 0; i < num; i++) {
        if (arr[i] == L'\0') {
            break;
        }
        if (iswalpha(arr[i])) {
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

int pal(wchar_t* arr, int num)
{
    if (!num) {
        return -1;
    }
    for (int i = 0; i < (num / 2); i++) {
        if (arr[i] != arr[num - i - 1]) {
            return -1;
        }
    }
    return 0;
}