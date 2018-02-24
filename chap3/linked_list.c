#include <stdio.h>
#include <stdlib.h>
struct node {
    char *data;
    struct node *next;
};

int main() {
    typedef struct node Node;

    Node *head = (Node *)malloc(sizeof(Node));
    head->data = "Tuesday";
    head->next = NULL;

    Node *q = (Node *)malloc(sizeof(Node));
    q->data = "Wednesday";
    q->next = NULL;
    head->next = q;

    q = (Node *)malloc(sizeof(Node));
    q->data = "Monday";
    q->next = head;
    head = q;

    Node *p = head;
    while (p != NULL) {
        printf("%s\n", p->data);
        p = p->next;;
    }

    return 0;
}
    


