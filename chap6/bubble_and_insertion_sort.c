#include <stdio.h>

void bubble_sort(int *numbers);
void insertion_sort(int *numbers);

int main() {
    int numbers[10] = {3, 5, 2, 1 ,7 ,8, 9, 4, 10, 6};
    for (int i = 0; i < 10; i++)
        printf("%d ", numbers[i]);
    printf("\n");

    insertion_sort(numbers);
    for (int i = 0; i < 10; i++)
        printf("%d ", numbers[i]);
    printf("\n");

    return 0;
}

void bubble_sort(int *numbers) {
    for (int i = 9; i > 0; i--) {
        for (int j = 0; j < i; j++) {
            if (numbers[j] > numbers[j+1]) {
                int tmp = numbers[j];
                numbers[j] = numbers[j+1];
                numbers[j+1] = tmp;
            }
        }
    }
}

void insertion_sort(int *numbers) {
    int i, j;
    for (i = 1; i < 10; i++) {
        int tmp = numbers[i];
        j = i - 1;
        while (j >= 0 && tmp < numbers[j]) {
            numbers[j+1] = numbers[j];
            j--;
        }
        numbers[j+1] = tmp;
    }
}

