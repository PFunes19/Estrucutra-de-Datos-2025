#include <stdio.h>

#define MAX_ELEMENTS 11

typedef struct {
    char nodes[MAX_ELEMENTS];
    int numElements;
} BinaryTree;

int main() {
    BinaryTree tree;

    tree.numElements = MAX_ELEMENTS;

    tree.nodes[0] = 'G';
    tree.nodes[1] = 'D';
    tree.nodes[2] = 'I';
    tree.nodes[3] = 'B';
    tree.nodes[4] = 'F';
    tree.nodes[5] = 'H';
    tree.nodes[6] = 'J';
    tree.nodes[7] = 'A';
    tree.nodes[8] = 'C';
    tree.nodes[9] = 'E';
    tree.nodes[10] = 'X'; // Added node to make it full

    printf("Full binary tree representation:\\n");
    for (int i = 0; i < tree.numElements; i++) {
        printf("Index %d: %c \n", i, tree.nodes[i]);
    }

    return 0;
}
