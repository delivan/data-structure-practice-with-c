#include <stdio.h>

#define MAX_SIZE 3

void insert_to_ordered_array(int data[], int size, int item) {
    int i = size - 1;
    for (;item < data[i] && i >= 0; i--) {
        data[i+1] = data[i];
    }
    data[i+1] = item;
}

// O(size^2)
void merge_ordered_arrays1(int data1[], int data2[], int merged_data[], int size) {
    for (int i = 0; i < size; i++)
        merged_data[i] = data1[i];
    for (int j = 0; j < size; j++)
        insert_to_ordered_array(merged_data, size + j, data2[j]);
}

// O(size)
void merge_ordered_arrays2(int data1[], int data2[], int merged_data[], int size) {
    int i = 0, j = 0, k = 0;
    while (i < size && j < size) {
        if (data1[i] <= data2[j]) 
            merged_data[k++] = data1[i++];
        else 
            merged_data[k++] = data2[j++];
    }
    while (i < size)
        merged_data[k++] = data1[i++];
    while (j < size)
        merged_data[k++] = data2[j++];
}



int main() {
    int array_data1[MAX_SIZE], array_data2[MAX_SIZE];
    int merged_data1[2 * MAX_SIZE], merged_data2[2 * MAX_SIZE];
    int size = 0;
    int item;

    while (size < MAX_SIZE) {
        scanf("%d", &item);
        insert_to_ordered_array(array_data1, size, item);
        scanf("%d", &item);
        insert_to_ordered_array(array_data2, size, item);
        size++;

        printf("array1: ");
        for (int i = 0; i < size; i++) 
            printf("%d ", array_data1[i]);
        printf("\n");
        printf("array2: ");
        for (int i = 0; i < size; i++) 
            printf("%d ", array_data2[i]);
        printf("\n");
    }
    merge_ordered_arrays1(array_data1, array_data2, merged_data1, size);
    merge_ordered_arrays2(array_data1, array_data2, merged_data2, size);
    size *= 2;
    printf("merged array1: ");
    for (int i = 0; i < size; i++) 
        printf("%d ", merged_data1[i]);
    printf("\n");
    printf("merged array2: ");
    for (int i = 0; i < size; i++) 
        printf("%d ", merged_data2[i]);
    printf("\n");

    return 0;
}
