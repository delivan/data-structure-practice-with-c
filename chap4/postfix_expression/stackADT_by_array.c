#include "stackADT.h"

#define INIT_CAPACITY 100

struct stack_type {
    Item *contents;
    int top;
    int size;
};

static void terminate(const char *message) {
    printf("%s\n", message);
    exit(1);
}

Stack create() {
    Stack s = (Stack)malloc(sizeof(Stack));
    if (s == NULL)
        terminate("Error in creating: stack could not be created.");
    s->contents = (Item *)malloc(INIT_CAPACITY * sizeof(Item));
    if (s->contents == NULL) {
        free(s);
        terminate("Error in creating: stack could not be created.");
    }
    s->top = -1;
    s->size = INIT_CAPACITY;
    
    return s;
}

void reallocate(Stack s) {
    Item *tmp = (Item *)malloc(2 * s->size * sizeof(Item));
    if (tmp == NULL)
        terminate("Error in creating: stack could not be created.");
    for (int i = 0; i < s->size; i++)
        tmp[i] = s->contents[i];
    free(s->contents);
    s->contents = tmp;
    s->size *= 2;
}   

void destroy(Stack s) {
    free(s->contents);
    free(s);
}

void make_empty(Stack s) {
    s->top = -1;
}

bool is_empty(Stack s) {
    return s->top == -1;
}

bool is_full(Stack s) {
    return s->top == s->size-1;
}

void push(Stack s, Item i) {
    if (is_full(s))
        reallocate(s);
    s->top++;
    s->contents[s->top] = i;
}

Item pop(Stack s) {
    if (is_empty(s)) 
        return '\0';
    
    return s->contents[s->top--];
}

Item peek(Stack s) {
    if (is_empty(s)) 
        return '\0';

    return s->contents[s->top];
}

