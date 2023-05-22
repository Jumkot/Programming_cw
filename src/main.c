#include "palindrom.h"

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "");

    FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
        wprintf(L"Не удалось открыть файл.\n");
        return -1;
    }
    check_correct_file(file);

    int num = 0;
    int line = 0;
    wchar_t** start = malloc(MAX_SIZE * sizeof(wchar_t*));
    start = prepare_two_dim_arr(start);
    read_text(file, start, &line, &num);
    fclose(file);

    skip_empty(start, &line);

    wchar_t** processing = malloc(MAX_SIZE * sizeof(wchar_t*));
    processing = prepare_two_dim_arr(processing);
    for (int i = 0; i < line; i++) {
        for (int j = 0; start[i][j] != L'\0'; j++) {
            processing[i][j] = start[i][j];
        }
        skip_trash(processing[i], wcslen(processing[i]));
    }

    int* result = calloc(MAX_SIZE, sizeof(int));
    int step = 0;
    for (int i = 0; i < line; i++) {
        num = wcslen(processing[i]);
        if (pal(processing[i], num) == 0) {
            result[step] = i;
            step++;
        }
    }

    if (step == 0) {
        wprintf(L"В предложенном файле не обнаружено ни одного палиндрома.\n");
    } else {
        wprintf(L"Найденные палиндромы:\n");
        for (int i = 0; i < step; i++) {
            wprintf(L"%ls\n", start[result[i]]);
        }
    }

    for (int i = 0; i < line; i++) {
        free(start[i]);
    }
    free(start);
    for (int i = 0; i < line; i++) {
        free(processing[i]);
    }
    free(processing);
    free(result);

    return 0;
}