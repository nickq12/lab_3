#include <time.h>
#include <locale.h>
#include <iostream>

#define ARRAY_SIZE 100000
#define ARRAY_TYPE int

void reverse(ARRAY_TYPE* items, int size) {
    ARRAY_TYPE temp;
    int opposite;
    for (int i = 0; i < size / 2; ++i) {
        opposite = size - i - 1;
        temp = items[i];
        items[i] = items[opposite];
        items[opposite] = temp;
    }
}

void shellSort(ARRAY_TYPE* items, int count) {
    int i, j, gap, k;
    int x, a[5] = { 9, 5, 3, 2, 1 };

    for (k = 0; k < 5; k++) {
        gap = a[k];
        for (i = gap; i < count; ++i) {
            x = items[i];
            for (j = i - gap; (x < items[j]) && (j >= 0); j = j - gap) {
                items[j + gap] = items[j];
            }
            items[j + gap] = x;
        }
    }
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"

void quickSort(ARRAY_TYPE* items, int left, int right) { // qs
    int i, j;
    ARRAY_TYPE x, y;

    i = left;
    j = right;

    /* выбор компаранда */
    x = items[(left + right) / 2];

    do {
        while ((items[i] < x) && (i < right)) i++;
        while ((x < items[j]) && (j > left)) j--;

        if (i <= j) {
            y = items[i];
            items[i] = items[j];
            items[j] = y;
            i++;
            j--;
        }
    } while (i <= j);

    if (left < j) quickSort(items, left, j);
    if (i < right) quickSort(items, i, right);
}

#pragma clang diagnostic pop

ARRAY_TYPE cmp(const ARRAY_TYPE* a, const ARRAY_TYPE* b) {
    return (*a > *b) - (*a < *b);
}

int main() {
    setlocale(LC_ALL, "Rus");
    clock_t start; // объявляем переменные для определения времени выполнения
    ARRAY_TYPE shellSortSample[ARRAY_SIZE], quickSortSample[ARRAY_SIZE];

    for (int i = 0; i < ARRAY_SIZE; ++i) {
        shellSortSample[i] = quickSortSample[i] = rand() % 100 + 1;
    }

#define TIME_SAMPLES(na)\
    start = clock();\
    shellSort(shellSortSample, ARRAY_SIZE);\
    printf("shellSort %sпроизводился %lu тиков\n", na, clock() - start);\
    start = clock();\
    quickSort(quickSortSample, quickSortSample[0], quickSortSample[ARRAY_SIZE - 1]);\
    printf("quickSort %sпроизводился %lu тиков\n", na, clock() - start);\
    qsort(quickSortSample, ARRAY_SIZE, sizeof(ARRAY_TYPE), (int (*)(const void *, const void *)) cmp);\
    printf("qsort "na"производился %lu тиков\n", clock() - start);

    TIME_SAMPLES("");
    TIME_SAMPLES("на упорядоченном массиве ");

    reverse(shellSortSample, ARRAY_SIZE);
    reverse(quickSortSample, ARRAY_SIZE);

    TIME_SAMPLES("на обратно упорядоченном массиве ");

    reverse(shellSortSample + ARRAY_SIZE / 2, ARRAY_SIZE / 2);
    reverse(quickSortSample + ARRAY_SIZE / 2, ARRAY_SIZE / 2);

    TIME_SAMPLES("на пирамидально упорядоченном массиве ");

    return 0;
}
