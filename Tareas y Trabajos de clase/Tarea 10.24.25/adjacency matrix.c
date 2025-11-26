#include <stdio.h>

#define V 4  // Number of vertices

int main() {
    int adjMatrix[V][V] = {0}; // Initialize all to 0

    // Mapping: A=0, B=1, C=2, D=3
    adjMatrix[0][1] = 1; // A-B
    adjMatrix[1][0] = 1;

    adjMatrix[0][2] = 1; // A-C
    adjMatrix[2][0] = 1;

    adjMatrix[1][3] = 1; // B-D
    adjMatrix[3][1] = 1;

    // Print the matrix
    printf("Adjacency Matrix (Undirected):\n");
    char labels[] = {'A', 'B', 'C', 'D'};
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            printf("%d ", adjMatrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}
