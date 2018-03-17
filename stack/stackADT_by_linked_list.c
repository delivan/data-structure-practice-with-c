#include "stackADT.h"

typedef struct node Node; 
struct node {
    Item data;
    Node *next;
};

struct stack_type {
    Node *top;
};

static void terminate(const char *message) {
    printf("%s\n", message);
    exit(EXIT_FAILURE);
}

Stack create() {
    Stack s = (Stack)malloc(sizeof(Stack));
    if (s == NULL)
        terminate("Error in creating: Stack can't be created.");
    s->top = NULL;
    
    return s;
}

void destroy(Stack s) {
    make_empty(s);
    free(s);
}

void make_empty(Stack s) {
    while(!is_empty(s))
        pop(s);
}

bool is_empty(Stack s) {
    return s->top == NULL;
}

void push(Stack s, Item i) {
    Node *n = (Node *)malloc(sizeof(Node));
    if (n == NULL)
        terminate("Error in pushing: Node can't be created.");
    n->data = i;
    n->next = s->top;
    s->top = n;
}

Item pop(Stack s) {
    if (is_empty(s))
        terminate("Error in popping: Stack is empty.");
    Node *tmp = s->top;
    Item i = tmp->data;
    s->top = tmp->next;
    free(tmp);

    return i;
}

Item peek(Stack s) {
    if (is_empty(s))
        terminate("Error in peeking: Stack is empty.");
    return s->top->data;
}
