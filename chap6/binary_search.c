#include <stdio.h>
#include <string.h>

void binary_search(char **names, char *searching_name) {
    int begin = 0, end = 6;
    int middle, result;
    while (begin <= end) {
        middle = (begin + end) / 2;
        result = strcmp(names[middle], searching_name);
        if (result == 0) {
            printf("search success: %s\n", names[middle]);
            return;
        }
        else if (result > 0)
            end = middle - 1;
        else
            begin = middle + 1;
    }
    printf("search fail\n");
}

void read_line(FILE *fp, char str[], int size) {
    int ch, i = 0;
    while ((ch = fgetc(fp)) == '\n' && ch != EOF)
        if (i < size - 1)
            str[i++] = ch;
    str[i] = '\0';
}


int main() {
    char *names[7] = {"Caryn", "Debbie", "Dustin", "Elliot", "Jacquie", "Jonathon", "Rich"};
    char searching_name[10];
    scanf("%s", searching_name);
    binary_search(names, searching_name);
    return 0;
}
