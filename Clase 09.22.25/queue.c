#include <stdio.h>
#include <stdlib.h>

#define QUEUESIZE 5

int queue[QUEUESIZE];
int front = 0;
int rear = 0;
int numCurrentElements = 0;

int isEmpty(void);
int isFull(void);
void enqueue(int val);
int dequeue(int *out);
void display(void);

int main(void) {
    int choice = -1;
    int valor, x;

    while (1) {
        printf("0. Enqueue (añadir)\n");
        printf("1. Dequeue (eliminar)\n");
        printf("2. Salir\n");
        printf("Elige una opción: ");
        if (scanf("%d", &choice) != 1) {
            printf("Entrada inválida.\n");
            return 1;
        }

        if (choice == 0) {               
            if (isFull()) {
                printf("La cola está llena.\n");
            } else {
                printf("Valor a añadir: ");
                if (scanf("%d", &valor) != 1) return 1;
                enqueue(valor);
                printf("Enqueued: %d\n", valor);
                display();
            }
        } 
        else if (choice == 1) {            
            if (isEmpty()) {
                printf("La cola está vacía.\n");
            } else {
                if (dequeue(&x)) {
                    printf("Dequeued: %d\n", x);
                    display();
                }
            }
        } 
        else if (choice == 2) {    
            printf("Saliendo...\n");
            break;
        } 
        else {
            printf("Opción inválida, intenta de nuevo.\n");
        }
    }

    return 0;
}

int isEmpty(void) {
    return numCurrentElements == 0;
}

int isFull(void) {
    return numCurrentElements == QUEUESIZE;
}

void enqueue(int val) {
    queue[rear] = val;
    rear = (rear + 1) % QUEUESIZE;
    numCurrentElements++;
}

int dequeue(int *out) {
    if (isEmpty()) return 0;
    *out = queue[front];
    front = (front + 1) % QUEUESIZE;
    numCurrentElements--;
    return 1;
}

void display(void) {
    if (isEmpty()) {
        printf("La cola está vacía.\n");
        return;
    }
    printf("Cola: ");
    int i, index;
    for (i = 0; i < numCurrentElements; i++) {
        index = (front + i) % QUEUESIZE;
        printf("%d ", queue[index]);
    }
    printf("\n");
}
