#include <stdio.h>
#include <stdlib.h>

#define V 4

struct Node {
    int vertex;
    struct Node* next;
};

struct Node* adjList[V];

struct Node* createNode(int v) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

void addEdge(int src, int dest) {
    struct Node* newNode = createNode(dest);
    newNode->next = adjList[src];
    adjList[src] = newNode;
}

int main() {
    for (int i = 0; i < V; i++)
        adjList[i] = NULL;

    // Directed edges: A->B, A->C, B->D
    addEdge(0, 1);
    addEdge(0, 2);
    addEdge(1, 3);

    char labels[] = {'A', 'B', 'C', 'D'};
    printf("Adjacency List (Directed):\n");
    for (int i = 0; i < V; i++) {
        printf("%c: ", labels[i]);
        struct Node* temp = adjList[i];
        while (temp) {
            printf("%c -> ", labels[temp->vertex]);
            temp = temp->next;
        }
        printf("NULL\n");
    }

    return 0;
}
