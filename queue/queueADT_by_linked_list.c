#include "queueADT.h"

typedef struct node Node;
struct node {
    Item data;
    Node *next;
};

struct queue_type {
    Node *front, *rear;
    int size;
};

void terminate(char *err_msg) {
    printf("%s\n", err_msg);
    exit(EXIT_FAILURE);
}

Queue create() {
    Queue q = (Queue)malloc(sizeof(struct queue_type));
    if (q == NULL)
        terminate("Error in create(): Queue could't be created"); 
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;

    return q;
}

void destroy(Queue q) {
    make_empty(q);
    free(q);
}

void make_empty(Queue q) {
    while (!is_empty(q))
        dequeue(q);
}

bool is_empty(Queue q) {
    return q->size == 0;
}

void enqueue(Queue q, Item i) {
    Node *n = (Node *)malloc(sizeof(struct node));
    if (n == NULL)
        terminate("Error in enqueue(): node couldn't be created");
    n->data = i;
    n->next = NULL;
    if (is_empty(q)) {
        q->front = n;
        q->rear = n;
    }
    else {
        q->rear->next = n;
        q->rear = n;
    }
    q->size++;
}

Item dequeue(Queue q) {
    if (is_empty(q))
        terminate("Error in dequeue(): Queue is empty");
    Node *old_n = q->front;
    Item old_i = old_n->data;
    q->front = old_n->next;
    if (q->front == NULL)
        q->rear = NULL;
    free(old_n);
    q->size--;

    return old_i;
}

Item peek(Queue q) {
    if (is_empty(q))
        terminate("Error in peek(): Queue is empty");
    return q->front->data;
}

int get_size(Queue q) {
    return q->size;
}

    



