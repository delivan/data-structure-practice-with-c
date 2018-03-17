// operand must be positive integer
// all operands and operators must be delimited by empty space
#include "infix_to_postfix_conversion.h"

Stack operand_stack;

int eval(char *expr);
int eval_op(char *op);
void handle_exception(char *message);

int main() {
    char infix[MAX_SIZE];
    char *postfix;

    while (1) {
        printf("infix: ");
        if (read_line(stdin, infix, MAX_SIZE) < 0)
            continue;
        postfix = convert(infix);
        printf("postfix: %s\n", postfix);
        printf("result: %d\n\n", eval(postfix));
    }
}

int eval(char *expr) {
    // 2 3 5 + *
    operand_stack = create();
    char *op = strtok(expr, " ");
    while (op != NULL) {
        if (op[0] >= '0' && op[0] <= '9') 
            push(operand_stack, atoi(op));
        else {
            push(operand_stack, eval_op(op));
        }
        op = strtok(NULL, " ");
    }
    if (is_empty(operand_stack))
        handle_exception("Stack is empty in evaluating");
    int result = pop(operand_stack);
    if (is_empty(operand_stack))
        return result;
    else {
        handle_exception("Stack should be empty in last");
        return -1;
    }
}

int eval_op(char *op) {
    int right_op = pop(operand_stack);
    int left_op = pop(operand_stack);
    int result;
    switch (op[0]) {
        case '+':
            result = left_op + right_op;
            break;
        case '-':
            result = left_op - right_op;
            break;
        case '*':
            result = left_op * right_op;
            break;
        case '/':
            result = left_op / right_op;
            break;
    }
    return result;
}

void handle_exception(char *message) {
    printf("%s\n", message);
    exit(1);
}
