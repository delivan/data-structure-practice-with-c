#include <stdlib.h>
#include "queueADT.h"

#define INIT_CAPACITY 100

struct queue_type {
    Item *contents;
    int front;
    int rear;
    int size;
    int capacity;
};

void terminate(char *err_msg) {
    printf("%s\n", err_msg);
    exit(1);
}

Queue create() {
    Queue q = (Queue)malloc(sizeof(struct queue_type));
    if (q == NULL)
        terminate("Error in create(): Queue couldn't be created");
    q->contents = (Item *)malloc(INIT_CAPACITY * sizeof(Item));
    if (q->contents == NULL) {
        free(q);
        terminate("Error in create(): contents couldn't be created");
    }
    q->front = 0;
    q->rear = -1;
    q->size = 0;
    q->capacity = INIT_CAPACITY;

    return q;
}

void reallocate(Queue q) {
    Item *tmp = (Item *)malloc(2 * q->capacity * sizeof(Item));
    if (tmp == NULL)
        terminate("Error in reallocate(): tmp couldn't be created");
    int j = q->front;
    for (int i = 0; i < q->size; i++) {
        tmp[i] = q->contents[j];
        j = (j + 1) % q->capacity;
    }
    free(q->contents);
    q->contents = tmp;
    q->front = 0;
    q->rear = q->size - 1;
    q->capacity *= 2;
}

void destroy(Queue q) {
    free(q->contents);
    free(q);
}

void make_empty(Queue q) {
    q->front = 0;
    q->rear = -1;
    q->size = 0;
}

bool is_empty(Queue q) {
    return q->size == 0;
}

bool is_full(Queue q) {
    return q->size == q->capacity;
}

void enqueue(Queue q, Item i) {
    if (is_full(q))
        reallocate(q);
    q->rear = (q->rear + 1) % q->capacity;
    q->contents[q->rear] = i;
    q->size++;
}

Item dequeue(Queue q) {
    if (is_empty(q))
        terminate("Error in dequeue(): queue is empty");
    Item old_i = q->contents[q->front];
    q->front = (q->front + 1) % q->capacity;
    q->size--;

    return old_i;
}

Item peek(Queue q) {
    if (is_empty(q))
        terminate("Error in peek(): queue is empty");
    return q->contents[q->front];
}

int get_size(Queue q) {
    return q->size;
}
