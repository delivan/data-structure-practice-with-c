#ifndef QUEUEADT_H
#define QUEUEADT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>    // c99 only
#include "maze.h"

typedef Pos Item;
typedef struct queue_type *Queue;

void terminate(char *err_msg);
Queue create();
void reallocate(Queue q);
void destroy(Queue q);
void make_empty(Queue q);
bool is_empty(Queue q);
bool is_full(Queue q);
void enqueue(Queue q, Item i);
Item dequeue(Queue q);
Item peek(Queue q);
int get_size(Queue q);

#endif
