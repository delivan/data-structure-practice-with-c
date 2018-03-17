#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 10

int read_line(char str[], int n);

int main(int argc, char *argv[]) {
    char buffer[BUFFER_SIZE];
    int strlen;

    while (1) {
        printf("$ ");
        strlen = read_line(buffer, BUFFER_SIZE);
        printf("%s:%d\n", buffer, strlen);
    }

    return 0;
}

int read_line(char str[], int limit) {
    int ch, i = 0;

    while ((ch = getchar()) != '\n')
        if (i < limit-1)
            str[i++] = ch;
    str[i] = '\0';

    return i;
}
