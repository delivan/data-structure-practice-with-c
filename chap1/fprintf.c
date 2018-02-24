#include <stdio.h>

int main() {
    FILE *fp1, *fp2;
    char buffer[100];

    fp1 = fopen("input.txt", "r");
    fp2 = fopen("output.txt", "w");
    while (fscanf(fp1, "%s", buffer) != EOF) {
        printf("%s\n", buffer);
        fprintf(fp2, "%s ", buffer);
    }
    fclose(fp1);
    fclose(fp2);

    return 0;
}
