#include "infix_to_postfix_conversion.h"

Stack operator_stack;

int read_line(FILE *fp, char str[], int size) {
    int ch, i = 0;
    while ((ch = fgetc(fp)) != '\n' && ch != EOF)
        if (i < size - 1)
            str[i++] = ch;
    str[i] = '\0';

    return i;
}

char *convert(char *infix) {
    operator_stack = create();
    char *postfix = (char *)malloc(strlen(infix) + 1);
    char *postfix_index = postfix;
    char *op = strtok(infix, " ");
    while (op != NULL) {
        if (op[0] >= '0' && op[0] <= '9') {
            sprintf(postfix_index, "%s ", op);
            postfix_index += (strlen(op) + 1);
        }
        else {
            char top_op = (char)peek(operator_stack);
            if (top_op == '\0' || op[0] == '(')
                push(operator_stack, op[0]);
            else {
                while (get_priority(top_op) >= get_priority(op[0])) {
                    pop(operator_stack);
                    if (top_op == '(')
                        break;
                    sprintf(postfix_index, "%c ", top_op);
                    postfix_index += 2;
                    top_op = (char)peek(operator_stack);
                }
                if (op[0] != ')')
                    push(operator_stack, op[0]);
            }
        }
        op = strtok(NULL, " ");
    }
    while (!is_empty(operator_stack)) {
        char op = (char)pop(operator_stack);
        if (op == '(' || op == ')')
            return NULL;
        sprintf(postfix_index, "%c ", op);
        postfix_index += 2;
    }
    *postfix_index = '\0';

    return postfix;
}

int get_priority(char op) {
    int priority;
    switch (op) {
        case '(':
            priority = -1;
            break;
        case ')':
            priority = -1;
            break;
        case '+':
            priority = 1;
            break;
        case '-':
            priority = 1;
            break;
        case '*':
            priority = 2;
            break;
        case '/':
            priority = 2;
            break;
    }

    return priority;
}
    


