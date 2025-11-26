#include <stdio.h>

typedef enum {
    STRUCT_ARRAY = 0,
    STRUCT_LINKED_LIST,
    STRUCT_STACK,
    STRUCT_QUEUE,
    STRUCT_BST,
    STRUCT_HEAP,
    STRUCT_GRAPH
} DataStructureType;

typedef struct {
    int need_random_access;
    int frequent_insert_delete_middle;
    int need_fifo;
    int need_lifo;
    int need_sorted;
    int need_priority;
    int need_graph_relationships;
    int expected_size_large;
} Answers;

DataStructureType decide_structure(const Answers *a) {

    if (a->need_graph_relationships) {
        return STRUCT_GRAPH;
    }

    if (a->need_priority) {
        return STRUCT_HEAP;
    }

    if (a->need_fifo && !a->need_lifo) {
        return STRUCT_QUEUE;
    }

    if (a->need_lifo && !a->need_fifo) {
        return STRUCT_STACK;
    }

    if (a->need_sorted) {
        return STRUCT_BST;
    }

    if (a->need_random_access && !a->frequent_insert_delete_middle) {
        return STRUCT_ARRAY;
    }

    if (a->frequent_insert_delete_middle || a->expected_size_large) {
        return STRUCT_LINKED_LIST;
    }

    return STRUCT_ARRAY;
}

const char* structure_name(DataStructureType t) {
    switch (t) {
        case STRUCT_ARRAY:        return "Arreglo (Array)";
        case STRUCT_LINKED_LIST:  return "Lista ligada";
        case STRUCT_STACK:        return "Pila (Stack)";
        case STRUCT_QUEUE:        return "Cola (Queue)";
        case STRUCT_BST:          return "Arbol binario de busqueda (BST)";
        case STRUCT_HEAP:         return "Heap / Priority Queue";
        case STRUCT_GRAPH:        return "Grafo";
        default:                  return "Desconocida";
    }
}

int run_test(const char *test_name, Answers a, DataStructureType expected) {
    DataStructureType got = decide_structure(&a);
    int ok = (got == expected);

    if (ok) {
        printf("[OK]   %s -> %s\n", test_name, structure_name(got));
    } else {
        printf("[FAIL] %s -> esperado: %s, obtenido: %s\n",
               test_name,
               structure_name(expected),
               structure_name(got));
    }
    return ok;
}

int main(void) {
    int passed = 0;
    int total = 0;

    /* Caso 1: Problema con relaciones tipo grafo */
    {
        Answers a = {0};
        a.need_graph_relationships = 1;
        total++;
        passed += run_test("Caso 1 - Grafo", a, STRUCT_GRAPH);
    }

    /* Caso 2: Uso de prioridades (heap) */
    {
        Answers a = {0};
        a.need_priority = 1;
        total++;
        passed += run_test("Caso 2 - Heap / Priority Queue", a, STRUCT_HEAP);
    }

    /* Caso 3: FIFO claro (cola) */
    {
        Answers a = {0};
        a.need_fifo = 1;
        a.need_lifo = 0;
        total++;
        passed += run_test("Caso 3 - Queue (FIFO)", a, STRUCT_QUEUE);
    }

    /* Caso 4: LIFO claro (pila) */
    {
        Answers a = {0};
        a.need_lifo = 1;
        a.need_fifo = 0;
        total++;
        passed += run_test("Caso 4 - Stack (LIFO)", a, STRUCT_STACK);
    }

    /* Caso 5: Datos ordenados (BST) */
    {
        Answers a = {0};
        a.need_sorted = 1;
        total++;
        passed += run_test("Caso 5 - BST (ordenado)", a, STRUCT_BST);
    }

    /* Caso 6: Acceso por índice, pocas inserciones en medio (Array) */
    {
        Answers a = {0};
        a.need_random_access = 1;
        a.frequent_insert_delete_middle = 0;
        total++;
        passed += run_test("Caso 6 - Array (acceso por indice)", a, STRUCT_ARRAY);
    }

    /* Caso 7: Muchas inserciones en medio (Lista ligada) */
    {
        Answers a = {0};
        a.frequent_insert_delete_middle = 1;
        total++;
        passed += run_test("Caso 7 - Lista ligada (muchas inserciones en medio)", a, STRUCT_LINKED_LIST);
    }

    /* Caso 8: Tamaño grande y dinamico (Lista ligada) */
    {
        Answers a = {0};
        a.expected_size_large = 1;
        total++;
        passed += run_test("Caso 8 - Lista ligada (tamano dinamico)", a, STRUCT_LINKED_LIST);
    }

    /* Caso 9: Por defecto (ninguna condición fuerte) -> Array */
    {
        Answers a = {0};
        total++;
        passed += run_test("Caso 9 - Default (Array)", a, STRUCT_ARRAY);
    }

    printf("\nResumen: %d/%d tests pasaron.\n", passed, total);

    return (passed == total) ? 0 : 1;
}
