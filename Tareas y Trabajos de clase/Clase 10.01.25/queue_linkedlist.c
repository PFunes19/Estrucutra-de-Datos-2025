#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* next;
} Node;

typedef struct {
    Node* front;
    Node* rear;
    int count;
} Queue;

Node* create_node(int val) {
    Node* n = (Node*)malloc(sizeof(Node));
    if (!n) return NULL;
    n->data = val;
    n->next = NULL;
    return n;
}

void init_queue(Queue* q) {
    q->front = q->rear = NULL;
    q->count = 0;
}

int is_empty(Queue* q) {
    return q->count == 0;
}


int enqueue(Queue* q, int val) {
    Node* n = create_node(val);
    if (!n) return 0;
    if (is_empty(q)) {
        q->front = q->rear = n;
    } else {
        q->rear->next = n;
        q->rear = n;
    }
    q->count++;
    return 1;
}

int dequeue(Queue* q, int* out) {
    if (is_empty(q)) return 0;
    Node* tmp = q->front;
    if (out) *out = tmp->data;
    q->front = tmp->next;
    if (!q->front) q->rear = NULL;
    free(tmp);
    q->count--;
    return 1;
}

void clear_queue(Queue* q) {
    Node* p = q->front;
    while (p) {
        Node* nxt = p->next;
        free(p);
        p = nxt;
    }
    q->front = q->rear = NULL;
    q->count = 0;
}

void display(Queue* q) {
    if (is_empty(q)) {
        printf("Cola: (vacia)\n");
        return;
    }
    printf("Cola: ");
    for (Node* p = q->front; p; p = p->next) {
        printf("%d", p->data);
        if (p->next) printf(" -> ");
    }
    printf("\n");
}

int read_int(const char* prompt, int* out) {
    int x;
    int r;
    do {
        if (prompt) printf("%s", prompt);
        r = scanf("%d", &x);
        if (r != 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}
            printf("Entrada invalida. Intenta de nuevo.\n");
        }
    } while (r != 1);
    if (out) *out = x;
    return 1;
}

int main(void) {
    Queue q;
    init_queue(&q);
    int opcion;
    for (;;) {
        printf("\n1) Enqueue\n2) Dequeue\n3) Mostrar\n4) Vaciar\n0) Salir\n");
        read_int("Opcion: ", &opcion);
        switch (opcion) {
            case 0:
                clear_queue(&q);
                return 0;
            case 1: {
                int v;
                read_int("Valor a encolar: ", &v);
                if (!enqueue(&q, v)) printf("No se pudo encolar.\n");
                display(&q);
                break;
            }
            case 2: {
                int v;
                if (dequeue(&q, &v)) {
                    printf("Desencolado: %d\n", v);
                } else {
                    printf("Cola vacia.\n");
                }
                display(&q);
                break;
            }
            case 3:
                display(&q);
                break;
            case 4:
                clear_queue(&q);
                printf("Cola vaciada.\n");
                display(&q);
                break;
            default:
                printf("Opcion invalida.\n");
                break;
        }
    }
}
