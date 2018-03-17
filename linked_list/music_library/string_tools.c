#include "string_tools.h"

int read_line(FILE *fp, char str[], int length) {
    int ch, i = 0;

    while ((ch = fgetc(fp)) != '\n' && ch != EOF)
        if (i < length - 1)
            str[i++] = ch;

    str[i] = '\0';
    return i;
}
