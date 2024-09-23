#include <stdio.h>
#include <stdlib.h>

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("No numbers to sort\n");
        return 0;
    }

    int count = argc - 1;
	int* numbers = (int*)malloc(count * sizeof(int));
    for (int i = 1; i < argc; i++) {
        numbers[i - 1] = atoi(argv[i]);
    }

    qsort(numbers, count, sizeof(int), compare);

    for (int i = 0; i < count; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");
    free(numbers);
    return 0;
}
