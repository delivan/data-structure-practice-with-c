#include <string.h>
#include "stackADT.h"

#define MAX_LENGTH 100

char OPEN[] = "({[";
char CLOSE[] = ")}]";

int is_balanced(char *expr);
int is_open(char expr);         // if ( = 0, { = 1, [ = 2 is returned, else -1
int is_close(char expr);        // same as is_open()

int main() {
    char expr[MAX_LENGTH];
   
    while (1) {
        printf("type parens: ");
        scanf("%s", expr);
        if (is_balanced(expr))
            printf("this expression is balanced\n");
        else
            printf("this expression is unbalanced\n");
    }
    return 0;
}

int is_balanced(char *expr) {
    Stack s = create();
    char popped;

    for (int i = 0; i < strlen(expr); i++) {
        if (is_open(expr[i]) > -1)
            push(s, expr[i]);
        else if (is_close(expr[i]) > -1) {
            if ((popped = pop(s)) == '\0')               // if stack is empty
                return 0;
            if (is_open(popped) != is_close(expr[i]))   // if paren is not same
                return 0;
        }
    }
    if (is_empty(s))     // all parens are same and stack is empty
        return 1;
    
    return 0;
}

int is_open(char expr) {
    for (int i = 0; i < strlen(OPEN); i++) {
        if (OPEN[i] == expr)
            return i;
    }

    return -1;
}

int is_close(char expr) {
    for (int i = 0; i < strlen(CLOSE); i++) {
        if (CLOSE[i] == expr)
            return i;
    }

    return -1;
}

