#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* next;
} Node;

Node *head = NULL;

Node* createNode(int val) {
    Node *n = (Node*)malloc(sizeof(Node));
    if (!n) return NULL;
    n->data = val;
    n->next = NULL;
    return n;
}

int size(void) {
    int c = 0;
    for (Node *p = head; p != NULL; p = p->next) c++;
    return c;
}

void display(void) {
    if (!head) { printf("Lista: (vacia)\n"); return; }
    printf("Lista: ");
    for (Node *p = head; p != NULL; p = p->next) {
        printf("%d", p->data);
        if (p->next) printf(" -> ");
    }
    printf("\n");
}

void insertAtBeginning(int val) {
    Node *n = createNode(val);
    if (!n) return;
    n->next = head;
    head = n;
}

void insertAtEnd(int val) {
    Node *n = createNode(val);
    if (!n) return;
    if (!head) { head = n; return; }
    Node *p = head;
    while (p->next) p = p->next;
    p->next = n;
}

void insertAtPosition(int pos, int val) {
    if (pos < 0 || pos > size()) {
        printf("Posicion invalida: %d\n", pos);
        return;
    }
    if (pos == 0) { insertAtBeginning(val); return; }
    Node *n = createNode(val);
    if (!n) return;
    Node *p = head;
    for (int i = 0; i < pos - 1; i++) p = p->next;
    n->next = p->next;
    p->next = n;
}

void deleteAtBeginning(void) {
    if (!head) { printf("Lista vacia.\n"); return; }
    Node *tmp = head;
    head = head->next;
    free(tmp);
}

void deleteAtEnd(void) {
    if (!head) { printf("Lista vacia.\n"); return; }
    if (!head->next) { free(head); head = NULL; return; }
    Node *p = head;
    while (p->next && p->next->next) p = p->next;
    free(p->next);
    p->next = NULL;
}

void deleteAtPosition(int pos) {
    int n = size();
    if (pos < 0 || pos >= n) {
        printf("Posicion invalida: %d\n", pos);
        return;
    }
    if (pos == 0) { deleteAtBeginning(); return; }
    Node *p = head;
    for (int i = 0; i < pos - 1; i++) p = p->next;
    Node *toDel = p->next;
    p->next = toDel->next;
    free(toDel);
}

int main(void) {
    insertAtEnd(10);
    insertAtEnd(20);
    insertAtEnd(30);
    display();
    insertAtBeginning(5);
    display();
    insertAtPosition(2, 99);
    display();
    deleteAtBeginning();
    display();
    deleteAtEnd();
    display();
    deleteAtPosition(1);
    display();
    return 0;
}
