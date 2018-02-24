#include <stdio.h>

int main() {
    FILE * fp;
    char buf1[100], buf2[100];

    fp = fopen("input.txt", "r");
    while (fscanf(fp, "%s", buf1) != EOF) {
        printf("%s ", buf1);
        fscanf(fp, "%s", buf2);
        printf("%s\n", buf2);
    }
    fclose(fp);
    
    return 0;
}
