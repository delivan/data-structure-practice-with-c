#include "stack.h"

char stack[MAX_SIZE];
int top = -1;

void push(char ch) {
    if (is_full()) {
        printf("stack is full\n");
        return;
    }
    top++;
    stack[top] = ch;
}

char pop() {
    if (is_empty())
        return '\0';
    char tmp = stack[top];
    top--;
    
    return tmp;
}

int is_empty() {
    return (top == -1);
}

int is_full() {
    return (top == MAX_SIZE - 1);
}

