#include <stdio.h>
#include <stdlib.h>

int main(void) {
    printf("Enter rows cols (separated by an space):");
    int N, M;
    if (scanf("%d %d", &N, &M) != 2 || N <= 0 || M <= 0) {
        fprintf(stderr, "Entrada invalida\n");
        return 1;
    }
    printf("Enter %d int for the matrix:\n", N * M);

    int *A = (int*)malloc((size_t)N * (size_t)M * sizeof(int));
    if (!A) {
        fprintf(stderr, "No se pudo asignar memoria\n");
        return 1;
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (scanf("%d", &A[i*M + j]) != 1) {
                fprintf(stderr, "Error al leer la matriz\n");
                free(A);
                return 1;
            }
        }
    }

    int top = 0, bottom = N - 1, left = 0, right = M - 1;
    int first = 1;

    while (top <= bottom && left <= right) {
        // izquierda -> derecha (fila superior)
        for (int j = left; j <= right; ++j) {
            if (!first) printf(" ");
            printf("%d", A[top*M + j]);
            first = 0;
        }
        top++;

        // arriba -> abajo (columna derecha)
        for (int i = top; i <= bottom; ++i) {
            printf(" %d", A[i*M + right]);
        }
        right--;

        // derecha -> izquierda (fila inferior)
        if (top <= bottom) {
            for (int j = right; j >= left; --j) {
                printf(" %d", A[bottom*M + j]);
            }
            bottom--;
        }

        // abajo -> arriba (columna izquierda)
        if (left <= right) {
            for (int i = bottom; i >= top; --i) {
                printf(" %d", A[i*M + left]);
            }
            left++;
        }
    }

    printf("\n");
    free(A);
    return 0;
}
