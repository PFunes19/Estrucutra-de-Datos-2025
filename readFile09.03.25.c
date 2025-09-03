#include <stdio.h>
#include <stdlib.h>

float totalSale(float sales[], int n);
float maxSale(float sales[], int n);

int main(void) {
    FILE *fptr = fopen("sales.txt", "r");
    if (!fptr) {
        printf("Error al abrir el archivo.\n");
        exit(-1);
    }

    int count = 0;
    char line[10];

    while (fgets(line, 10, fptr)) {
        if (line[0] != '\n') count++;
    }

    rewind(fptr);

    float *sales = malloc(count * sizeof(float));

    int i = 0;
    while (fgets(line, 10, fptr) && i < count) {
        if (line[0] != '\n') {
            sales[i] = atof(line);  // convierte la línea en float
            i++;
        }
    }

    printf("Número de ventras: %d\n", count);
    printf("Total de ventas: %.2f\n", totalSale(sales, count));
    printf("Venta máxima: %.2f\n", maxSale(sales, count));

    free(sales);
    fclose(fptr);
    return 0;
}

float totalSale(float sales[], int n) {
    float total = 0;
    for (int i = 0; i < n; i++) total += sales[i];
    return total;
}

float maxSale(float sales[], int n) {
    float max = sales[0];
    for (int i = 1; i < n; i++) if (sales[i] > max) max = sales[i];
    return max;
}
