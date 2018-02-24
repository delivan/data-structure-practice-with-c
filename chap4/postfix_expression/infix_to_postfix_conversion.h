#include "stackADT.h"
#include <string.h>

#define MAX_SIZE 100

char *convert(char *infix);
int read_line(FILE *fp, char str[], int size); 
int get_priority(char op);
