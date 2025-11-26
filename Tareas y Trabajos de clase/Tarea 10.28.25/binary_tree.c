#include <stdio.h>

#define MAX_SIZE 100

int heap[MAX_SIZE];
int heapSize = 0;

void insert(int item);
void showHeap(void);
int removeMax(void);
void reHeapDown(int i);
void showHeapAsTree(void);
void printHeapTree(void);

int main() {
    int n, item, k, i;

    printf("Enter number of elements to insert: ");
    scanf("%d", &n);

    printf("Enter %d integers:\n", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &item);
        insert(item);
        printf("\nHeap after insertion of %d:\n", item);
        showHeap();
        printHeapTree();
    }

    printf("\nHow many times do you want to remove the maximum (root)? ");
    scanf("%d", &k);

    for (i = 0; i < k && heapSize > 0; i++) {
        int removed = removeMax();
        printf("\nRemoved max: %d\n", removed);
        printf("Heap after removal:\n");
        showHeap();
        printHeapTree();
    }

    return 0;
}

void insert(int item) {
    int i = heapSize;
    heap[heapSize++] = item;

    while (i > 0 && heap[(i - 1) / 2] < heap[i]) {
        int temp = heap[i];
        heap[i] = heap[(i - 1) / 2];
        heap[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}

void showHeap(void) {
    for (int i = 0; i < heapSize; i++) {
        printf("%d ", heap[i]);
    }
    printf("\n");
}

int removeMax(void) {
    if (heapSize == 0) {
        printf("Heap is empty!\n");
        return -1;
    }

    int max = heap[0];
    heap[0] = heap[--heapSize];
    reHeapDown(0);
    return max;
}

void reHeapDown(int i) {
    int left, right, largest;

    while (1) {
        left = 2 * i + 1;
        right = 2 * i + 2;
        largest = i;

        if (left < heapSize && heap[left] > heap[largest])
            largest = left;
        if (right < heapSize && heap[right] > heap[largest])
            largest = right;

        if (largest == i)
            break;

        int temp = heap[i];
        heap[i] = heap[largest];
        heap[largest] = temp;

        i = largest;
    }
}

void printHeapTree() {
    printf("\nVisual Heap Representation:\n");

    if (heapSize >= 1)
        printf("               %d\n", heap[0]);

    if (heapSize >= 2) {
        printf("          ");
        (heapSize > 1) ? printf("%d", heap[1]) : printf(" ");
        printf("           ");
        (heapSize > 2) ? printf("%d", heap[2]) : printf(" ");
        printf("\n");
    }

    if (heapSize >= 4) {
        printf("      ");
        (heapSize > 3) ? printf("%d", heap[3]) : printf(" ");
        printf("     ");
        (heapSize > 4) ? printf("%d", heap[4]) : printf(" ");
        printf("     ");
        (heapSize > 5) ? printf("%d", heap[5]) : printf(" ");
        printf("     ");
        (heapSize > 6) ? printf("%d", heap[6]) : printf(" ");
        printf("\n");
    }

    if (heapSize >= 8) {
        printf("   ");
        (heapSize > 7) ? printf("%d", heap[7]) : printf(" ");
        printf("   ");
        (heapSize > 8) ? printf("%d", heap[8]) : printf(" ");
        printf("   ");
        (heapSize > 9) ? printf("%d", heap[9]) : printf(" ");
        printf("   ");
        (heapSize > 10) ? printf("%d", heap[10]) : printf(" ");
        printf("   ");
        (heapSize > 11) ? printf("%d", heap[11]) : printf(" ");
        printf("   ");
        (heapSize > 12) ? printf("%d", heap[12]) : printf(" ");
        printf("   ");
        (heapSize > 13) ? printf("%d", heap[13]) : printf(" ");
        printf("   ");
        (heapSize > 14) ? printf("%d", heap[14]) : printf(" ");
        printf("\n");
    }
}
