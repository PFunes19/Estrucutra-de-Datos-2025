#include <stdio.h>

#define MAX_ELEMENTS 15

typedef struct {
    char nodes[MAX_ELEMENTS];
    int numElements;
} BinaryTree;


int main() {
    BinaryTree tree;

    tree.numElements = MAX_ELEMENTS;

    tree.nodes[0] = 'A';
    tree.nodes[1] = 'B';
    tree.nodes[2] = 'C';
    tree.nodes[3] = 'D';
    tree.nodes[4] = 'E';
    tree.nodes[5] = 'F';
    tree.nodes[6] = 'G';
    tree.nodes[7] = 'H';
    tree.nodes[8] = 'I';
    tree.nodes[9] = 'J';
    tree.nodes[10] = 'K';
    tree.nodes[11] = 'L';
    tree.nodes[12] = 'M';
    tree.nodes[13] = 'N';
    tree.nodes[14] = 'O';

    printTree(tree);

    return 0;
}

void printTree(BinaryTree tree) {
    printf("              %c\n", tree.nodes[0]);
    printf("           /     \\\n");
    printf("         %c         %c\n", tree.nodes[1], tree.nodes[2]);
    printf("       /  \\      /   \\\n");
    printf("     %c     %c    %c     %c\n", tree.nodes[3], tree.nodes[4], tree.nodes[5], tree.nodes[6]);
    printf("    / \\   / \\  / \\   / \\\n");
    printf("   %c  %c  %c  %c %c  %c  %c  %c\n",
           tree.nodes[7], tree.nodes[8], tree.nodes[9], tree.nodes[10],
           tree.nodes[11], tree.nodes[12], tree.nodes[13], tree.nodes[14]);
}