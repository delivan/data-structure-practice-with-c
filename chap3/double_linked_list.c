#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 50
#define LIST_SIZE 10

typedef struct node {
    char *data;
    struct node *prev;
    struct node *next;
} Node;

Node **linked_list;
Node *head;
Node *tail;
int size;

void init();
void process_command();
int read_line(FILE *fp, char *line, int size);
void add_ordered_list(char *item);
void add_after(Node *pre, char *item);
void remove_item(char *item);
Node *find_item(char *item);
void print_list();

int main() {
    init();
    process_command();

    return 0;
}

void init() {
    linked_list = (Node **)malloc(LIST_SIZE * sizeof(Node *));
    head = NULL;
    tail = NULL;
    size = 0;
}

void process_command() {
    char command_line[BUFFER_SIZE];
    char *command, *item;

    while (1) {
        printf("$ ");
        if (read_line(stdin, command_line, BUFFER_SIZE) <= 0)
            continue;
        
        command = strtok(command_line, " ");
        if (strcmp(command, "add") == 0) {
            item = strtok(NULL, " ");
            add_ordered_list(item);
        } else if (strcmp(command, "remove") == 0) {
            item = strtok(NULL, " ");
            remove(item);
        } else if (strcmp(command, "print") == 0) {
            print_list();
        } else if (strcmp(command, "exit") == 0)
            break;
        else 
            continue;

    }
}

int read_line(FILE *fp, char *line, int size) {
    int ch, i = 0;

    while ((ch = fgetc(fp)) != '\n' && ch != EOF)
        if (i < size - 1)
            line[i++] = ch;
    line[i] = '\0';

    return i;
}
void add_ordered_list(char *item) {
    Node *p = tail;
    while (p != NULL && strcmp(p->data, item) > 0)
        p = p->prev;
    add_after(p, item);
}

void add_after(Node *pre, char *item) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = strdup(item);
    new_node->prev = NULL;
    new_node->next = NULL;

    if (pre == NULL && head == NULL) {  // at the head to empty list
        head = new_node;
        tail = new_node;
    } else if (pre == NULL) {           // at the head
        new_node->next = head;
        head->prev = new_node;
        head = new_node;
    } else if (pre == tail) {           // at the tail
        new_node->prev = tail;
        tail->next = new_node;
        tail = new_node;
    } else {                            // at the middle
        new_node->prev = pre;
        new_node->next = pre->next;
        pre->next->prev = new_node;
        pre->next = new_node;
    }
    size++;
}

void remove_item(char *item) {
    Node *p = find_item(item);
    if (p == NULL) {
        printf("cant find %s\n", item);
        return;
    }
    if (p == head && p == tail) {       // only left p
        head = NULL;
        tail = NULL;
    } else if (p == head) {             // p is head
        p->next->prev = NULL;
        head = p->next;
    } else if (p == tail) {             // p is tail
        p->prev->next = NULL;
        tail = p->prev;
    } else {                            // p is middle
        p->prev->next = p->next;
        p->next->prev = p->prev;
    }
    free(p->data);
    free(p->next);
    free(p->prev);
    free(p);
}

Node *find_item(char *item) {
    Node *p = tail;
    while (p != NULL) {
        if (strcmp(p->data, item) == 0)
            return p;
        p = p->prev;
    }
    return NULL;
}

void print_list() {
    Node *p = head;
    while (p!= NULL) {
        printf("%s\n", p->data);
        p = p->next;
    }
}
