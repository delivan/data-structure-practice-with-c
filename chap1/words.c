#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORDS 5
#define MAXLEN 100

/* strdup은 대략 이런 원리일것이다.
char * strdup(char *s) {
    char *p;

    p = (char *)malloc(strlen(s)+1);
    if (p != NULL)
        strcpy(p, s);

    return p;
}
*/  

int main(void) {
    char *words[MAXWORDS];
    int nwords;

    char tmp[MAXLEN];
    nwords = 0;

    while (nwords < MAXWORDS && scanf("%s", tmp) != EOF) {
        words[nwords] = strdup(tmp);
        nwords++;
    }

    for (int i = 0; i < MAXWORDS; i++)
        printf("%s\n", words[i]);

    return 0;
}
