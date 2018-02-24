#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    char *data;
    struct node *next;
};
typedef struct node Node;
Node *head;

int add_after(Node *prev, char *item) {
    if (prev == NULL)
        return 0;
    Node *tmp = (Node *)malloc(sizeof(Node));
    tmp->data = item;
    tmp->next = prev->next;
    prev->next = tmp;

    return 1;
}

Node *remove_first() {
    if (head == NULL)
        return NULL;
    Node *tmp = head;
    head = head->next;

    return tmp;
}

Node *remove_after(Node *prev) {
    if (prev == NULL)
        return NULL;
    Node *tmp = prev->next;
    prev->next = tmp->next;
    
    return tmp;
}

Node *find(char *word) {
    Node *p = head;
    while (p != NULL) {
        if (strcmp(p->data, word) == 0)
            return p;
        p = p->next;
    }
    return NULL;
}


int main() {

    head = (Node *)malloc(sizeof(Node));
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

    if (add_after(head->next->next, "Thursday") == 1)
        printf("Success\n");
    else
        printf("Failed\n");

    free(remove_first());
    free(remove_after(head));
    printf("find %s\n", find("Tuesday")->data);

    Node *p = head;
    while (p != NULL) {
        printf("%s\n", p->data);
        p = p->next;;
    }

    return 0;
}
    


