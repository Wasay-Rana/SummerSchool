#include <stdio.h>

int main() {
    int array[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    int size = sizeof(array) / sizeof(array[0]);
    int max = array[0];

    for (int i = 1; i < size; i++) {
        if (array[i] > max) {
            max = array[i];
        }
    }

    printf("Maximum value in the array: %d\n", max);
    return 0;
}
