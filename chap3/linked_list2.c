#include <stdio.h>
#include <stdlib.h>

struct node {
    char *data;
    struct node *next;
};
typedef struct node Node;


void add_first(char *data, Node **ptr_head);
Node *add_first2(char *data, Node *head);

int main() {

    Node *head = (Node *)malloc(sizeof(Node));
    head->data = "Tuesday";
    head->next = NULL;

    Node *q = (Node *)malloc(sizeof(Node));
    q->data = "Wednesday";
    q->next = NULL;
    head->next = q;
    
    // 2 ways for adding first node in linked list
    add_first("Monday", &head);
    head = add_first2("Monday", head); 
    
    Node *p = head;
    while (p != NULL) {
        printf("%s\n", p->data);
        p = p->next;
    }

    return 0;
}

void add_first(char *data, Node **ptr_head) {
    Node *tmp = (Node *)malloc(sizeof(Node));
    tmp->data = data;
    tmp->next = *ptr_head;
    *ptr_head = tmp;
}

Node *add_first2(char *data, Node *head) {
    Node *tmp = (Node *)malloc(sizeof(Node));
    tmp->data = data;
    tmp->next = head;
  
    return tmp;
}


