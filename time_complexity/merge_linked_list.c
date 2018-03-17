#include <stdio.h>
#include <stdlib.h>     // for malloc

#define MAX_SIZE 3 
#define DIVISOR 2

typedef struct node Node;
struct node {
    int data;
    Node *next;
};

void print_linked_list(Node *head, int size) {
    for (int i = 0; i < size && head != NULL; i++) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}
        

Node *insert_to_ordered_linked_list(Node *head, int item) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = item;
    new_node->next = NULL;
    
    Node *p = head;
    Node *q = NULL;
    while (p != NULL && p->data < item) {
        q = p;
        p = p->next;
    }
    if (q == NULL) {
        new_node->next = head;
        head = new_node;
    }
    else {
        new_node->next = p;
        q->next = new_node;
    }

    return head;
}

// O(size^2)
Node *merge_two_ordered_list1(Node *head1, Node *head2) {
    while (head1 != NULL) {
        head2 = insert_to_ordered_linked_list(head2, head1->data);
        head1 = head1->next;
    }

    return head2;
}

// O(size+size)
Node *merge_two_ordered_list2(Node *head1, Node *head2) {
    Node *merged_head = NULL, *merged_tail = NULL;
    Node *tmp;
    while (head1 != NULL && head2 != NULL) {
        if (head1->data <= head2->data) { 
            tmp = head1;
            head1 = head1->next;
        }
        else { 
            tmp = head2;
            head2 = head2->next;
        }
        if (merged_head == NULL)
            merged_head = merged_tail = tmp;
        else {
            merged_tail->next = tmp;
            merged_tail = merged_tail->next;
        }
    }
    if (head1 != NULL) 
        merged_tail->next = head1;
    if (head2 != NULL) 
        merged_tail->next = head2;

    return merged_head;
}

Node *reverse_linked_list(Node *head) {
    if (head == NULL || head->next == NULL) {
        printf("can't reverse\n");
        return head;
    }
    Node *q = NULL;
    Node *p = head;
    Node *r = head->next;
    while (r != NULL) {
        p->next = q;
        q = p;
        p = r;
        r = r->next;
    }
    p->next = q;

    return p;
}

Node *remove_all_divisible(Node *head, int divisor) {
    Node *p = head;
    Node *q = NULL;
    Node *deleting;
    while (p != NULL) {
        if (p->data % divisor == 0) {
            if (q == NULL) 
                head = head->next;
            else 
                q->next = p->next;
            deleting = p;
            p = p->next;
            free(deleting);
        }
        else {
            q = p;
            p = p->next;
        }
    }

    return head;
}

int main() {
    Node *head1 = NULL, *head2 = NULL;
    Node *merged_head, *reversed_head, *removed_head;
    int size = 0;
    int item;

    while (size < MAX_SIZE) {
        scanf("%d", &item);
        head1 = insert_to_ordered_linked_list(head1, item);
        scanf("%d", &item);
        head2 = insert_to_ordered_linked_list(head2, item);
        size++;

        Node *p1 = head1;
        printf("linked list1: ");
        print_linked_list(p1, size);
        Node *p2 = head2;
        printf("linked list2: ");
        print_linked_list(p2, size);
    }
    size *= 2;
    printf("merged linked list2: ");
    merged_head = merge_two_ordered_list2(head1, head2);
    print_linked_list(merged_head, size);
    printf("reversed linked list: ");
    reversed_head = reverse_linked_list(merged_head);
    print_linked_list(reversed_head, size);
    printf("removed all divisble linked list: ");
    removed_head = remove_all_divisible(reversed_head, DIVISOR); 
    print_linked_list(removed_head, size);

    return 0;
}
