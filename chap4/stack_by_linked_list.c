#include <stdlib.h>     // for malloc
#include "stack.h"

typedef struct stack Stack;
struct stack {
    char data;
    Stack *next;
};

Stack *top = NULL;
int size = 0;

void push(char ch);
char pop();
int is_empty();
int is_full();

void push(char ch) {
    if (is_full()) {
        printf("stack is full.\n");
        return;
    }
    Stack *tmp = (Stack *)malloc(sizeof(Stack));
    tmp->data = ch;
    tmp->next = top;
    top = tmp;
    size++;
}

char pop() {
    if (is_empty()) 
        return '\0';
    Stack *tmp = top;
    char tmp_data = tmp->data;
    top = tmp->next;
    free(tmp);
    size--;

    return tmp_data;
}

int is_empty() {
    return top == NULL;
}

int is_full() {
    return size == MAX_SIZE - 1;
}




