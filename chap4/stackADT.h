#ifndef STACKADT_H
#define STACKADT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>    // c99 only

typedef char Item;
typedef struct stack_type *Stack;

Stack create();
void reallocate();
void destroy(Stack s);
void make_empty(Stack s);
bool is_empty(Stack s);
bool is_full(Stack s);
void push(Stack s, Item i);
Item pop(Stack s);
Item peek(Stack s);

#endif
