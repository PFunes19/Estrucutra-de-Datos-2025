#include <stdio.h>
#include <stdlib.h>

/* Enumeración de estructuras de datos posibles */
typedef enum {
    STRUCT_ARRAY = 0,
    STRUCT_LINKED_LIST,
    STRUCT_STACK,
    STRUCT_QUEUE,
    STRUCT_BST,
    STRUCT_HEAP,
    STRUCT_GRAPH
} DataStructureType;

/* Respuestas del usuario a las preguntas */
typedef struct {
    int need_random_access;              // ¿Necesito acceder por índice rápido?
    int frequent_insert_delete_middle;   // ¿Inserto/borro mucho en medio?
    int need_fifo;                       // ¿Comportamiento cola (FIFO)?
    int need_lifo;                       // ¿Comportamiento pila (LIFO)?
    int need_sorted;                     // ¿Necesito mantener ordenado?
    int need_priority;                   // ¿Hay prioridades (siempre el "más importante" primero)?
    int need_graph_relationships;        // ¿Relaciones complejas como grafo?
    int expected_size_large;             // ¿Conjunto de datos grande y dinámico?
} Answers;

/* Prototipos */
void ask_questions(Answers *a);
DataStructureType decide_structure(const Answers *a);
const char* structure_name(DataStructureType t);
void print_structure_diagram(DataStructureType t);
void print_explanation(DataStructureType t, const Answers *a);
void print_operations_pseudocode(DataStructureType t);

int read_yes_no(void);

int main(void) {
    Answers ans;
    DataStructureType choice;

    printf("=========================================\n");
    printf("  Asistente de Seleccion de Estructuras\n");
    printf("=========================================\n\n");

    ask_questions(&ans);
    choice = decide_structure(&ans);

    printf("\n-----------------------------------------\n");
    printf("Estructura recomendada: %s\n", structure_name(choice));
    printf("-----------------------------------------\n\n");

    print_structure_diagram(choice);
    printf("\n");
    print_explanation(choice, &ans);
    printf("\n");
    print_operations_pseudocode(choice);

    printf("\nGracias por usar el asistente.\n");
    return 0;
}

/* Lee una respuesta 1 = Si, 0 = No, con validación básica */
int read_yes_no(void) {
    int x;
    while (1) {
        printf(" (1 = Si, 0 = No): ");
        if (scanf("%d", &x) != 1) {
            /* Limpiar buffer si hay entrada no numerica */
            int c;
            while ((c = getchar()) != '\n' && c != EOF) { }
            printf("Entrada invalida. Intenta de nuevo.\n");
        } else if (x == 0 || x == 1) {
            return x;
        } else {
            printf("Por favor responde 1 (Si) o 0 (No).\n");
        }
    }
}

/* Preguntas al usuario */
void ask_questions(Answers *a) {
    printf("Responde las siguientes preguntas sobre tu problema:\n\n");

    printf("1) ¿Necesitas acceder rapidamente a un elemento por su indice?\n");
    a->need_random_access = read_yes_no();

    printf("\n2) ¿Vas a insertar o eliminar elementos frecuentemente en medio de la coleccion?\n");
    a->frequent_insert_delete_middle = read_yes_no();

    printf("\n3) ¿Los elementos se procesan en orden de llegada (primero en entrar, primero en salir - FIFO)?\n");
    a->need_fifo = read_yes_no();

    printf("\n4) ¿Los elementos se procesan en orden inverso a la llegada (ultimo en entrar, primero en salir - LIFO)?\n");
    a->need_lifo = read_yes_no();

    printf("\n5) ¿Necesitas mantener los datos ordenados de forma continua (por valor, clave, etc.)?\n");
    a->need_sorted = read_yes_no();

    printf("\n6) ¿Siempre necesitas extraer el elemento con mayor prioridad (o menor) primero?\n");
    a->need_priority = read_yes_no();

    printf("\n7) ¿Tu problema modela entidades con relaciones complejas (por ejemplo ciudades y rutas, usuarios conectados, etc.)?\n");
    a->need_graph_relationships = read_yes_no();

    printf("\n8) ¿Esperas una cantidad grande y cambiante de datos (crece mucho con el tiempo)?\n");
    a->expected_size_large = read_yes_no();
}

/* Lógica de decisión basada en las respuestas */
DataStructureType decide_structure(const Answers *a) {

    /* 1. Si hay relaciones complejas, un grafo es buen candidato */
    if (a->need_graph_relationships) {
        return STRUCT_GRAPH;
    }

    /* 2. Si hay prioridad clara, usar heap/priority queue */
    if (a->need_priority) {
        return STRUCT_HEAP;
    }

    /* 3. FIFO -> Cola */
    if (a->need_fifo && !a->need_lifo) {
        return STRUCT_QUEUE;
    }

    /* 4. LIFO -> Pila */
    if (a->need_lifo && !a->need_fifo) {
        return STRUCT_STACK;
    }

    /* 5. Datos ordenados -> Arbol binario de busqueda (simplificado) */
    if (a->need_sorted) {
        return STRUCT_BST;
    }

    /* 6. Acceso por indice rapido, pocas inserciones intermedias -> Arreglo */
    if (a->need_random_access && !a->frequent_insert_delete_middle) {
        return STRUCT_ARRAY;
    }

    /* 7. Si hay muchas inserciones/borrados en medio o tamano dinamico grande -> Lista ligada */
    if (a->frequent_insert_delete_middle || a->expected_size_large) {
        return STRUCT_LINKED_LIST;
    }

    /* 8. Caso por defecto: arreglo */
    return STRUCT_ARRAY;
}

/* Nombre legible de la estructura */
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

/* Dibujo ASCII simple de cada estructura */
void print_structure_diagram(DataStructureType t) {
    printf("=== Representacion visual (ASCII) ===\n");

    switch (t) {
        case STRUCT_ARRAY:
            printf("[ idx ]:  0     1     2     3     4\n");
            printf("        +-----+-----+-----+-----+-----+\n");
            printf("        | a0  | a1  | a2  | a3  | a4  |\n");
            printf("        +-----+-----+-----+-----+-----+\n");
            break;

        case STRUCT_LINKED_LIST:
            printf("[head] -> [dato|*] -> [dato|*] -> [dato|NULL]\n");
            printf("          nodo1      nodo2       nodo3\n");
            break;

        case STRUCT_STACK:
            printf("   +-------+\n");
            printf("   | top   |  <- push/pop\n");
            printf("   +-------+\n");
            printf("   |  x3   |\n");
            printf("   |  x2   |\n");
            printf("   |  x1   |\n");
            printf("   +-------+\n");
            break;

        case STRUCT_QUEUE:
            printf("front -> [ x1 ] -> [ x2 ] -> [ x3 ] -> ... -> [ xn ] <- rear\n");
            break;

        case STRUCT_BST:
            printf("        [ 8 ]\n");
            printf("       /     \\\n");
            printf("    [ 3 ]   [ 10 ]\n");
            printf("    /  \\       \\\n");
            printf(" [ 1 ] [ 6 ]  [ 14 ]\n");
            break;

        case STRUCT_HEAP:
            printf("        [ 1 ]\n");
            printf("       /     \\\n");
            printf("    [ 3 ]   [ 5 ]\n");
            printf("    /  \\    /  \\\n");
            printf("  [ 4 ][ 8][ 7 ][ 9]\n");
            printf(" (ejemplo de min-heap)\n");
            break;

        case STRUCT_GRAPH:
            printf("   (A) --- (B)\n");
            printf("    | \\     |\n");
            printf("    |  \\    |\n");
            printf("   (C)  --- (D)\n");
            printf("   Nodos conectados por aristas\n");
            break;

        default:
            printf("No hay diagrama disponible.\n");
            break;
    }
}

/* Explicacion de por que se escogio la estructura */
void print_explanation(DataStructureType t, const Answers *a) {
    printf("=== Explicacion de la recomendacion ===\n");

    switch (t) {
        case STRUCT_ARRAY:
            printf("- Se recomendo un *arreglo* porque:\n");
            if (a->need_random_access)
                printf("  * Necesitas acceso rapido por indice.\n");
            if (!a->frequent_insert_delete_middle)
                printf("  * No realizas muchas inserciones/eliminaciones en medio.\n");
            printf("  * El costo de mover elementos ocasionalmente es aceptable.\n");
            break;

        case STRUCT_LINKED_LIST:
            printf("- Se recomendo una *lista ligada* porque:\n");
            if (a->frequent_insert_delete_middle)
                printf("  * Realizas inserciones/eliminaciones frecuentes en medio.\n");
            if (a->expected_size_large)
                printf("  * El tamano de la coleccion es dinamico y puede crecer mucho.\n");
            printf("  * No es tan importante el acceso por indice directo.\n");
            break;

        case STRUCT_STACK:
            printf("- Se recomendo una *pila (stack)* porque:\n");
            printf("  * Tu patron de acceso es LIFO: el ultimo en entrar es el primero en salir.\n");
            printf("  * Es util para deshacer acciones, evaluar expresiones, backtracking, etc.\n");
            break;

        case STRUCT_QUEUE:
            printf("- Se recomendo una *cola (queue)* porque:\n");
            printf("  * Tu patron de acceso es FIFO: el primero en entrar es el primero en salir.\n");
            printf("  * Es util para colas de tareas, procesos, atencion de clientes, etc.\n");
            break;

        case STRUCT_BST:
            printf("- Se recomendo un *arbol binario de busqueda (BST)* porque:\n");
            if (a->need_sorted)
                printf("  * Necesitas mantener los elementos ordenados.\n");
            printf("  * Permite busqueda, insercion y eliminacion en O(log n) (en el mejor/promedio caso).\n");
            break;

        case STRUCT_HEAP:
            printf("- Se recomendo un *heap / priority queue* porque:\n");
            if (a->need_priority)
                printf("  * Siempre necesitas obtener primero el elemento de mayor o menor prioridad.\n");
            printf("  * Inserciones y extraccion del minimo/maximo son O(log n).\n");
            break;

        case STRUCT_GRAPH:
            printf("- Se recomendo un *grafo* porque:\n");
            if (a->need_graph_relationships)
                printf("  * Tu problema involucra entidades con relaciones complejas (rutas, redes, etc.).\n");
            printf("  * Es adecuado para representar nodos y conexiones entre ellos.\n");
            break;

        default:
            printf("- No se pudo determinar una estructura clara; se usa arreglo por defecto.\n");
            break;
    }
}

/* Pseudocodigo de operaciones tipicas (se imprime como texto) */
void print_operations_pseudocode(DataStructureType t) {
    printf("=== Operaciones tipicas (pseudocodigo + complejidad) ===\n");

    switch (t) {
        case STRUCT_ARRAY:
            printf("\n[Acceso por indice]\n");
            printf("  function get(A, i):\n");
            printf("      return A[i]\n");
            printf("  Complejidad: O(1)\n");

            printf("\n[Busqueda lineal]\n");
            printf("  function find(A, x):\n");
            printf("      for i from 0 to n-1:\n");
            printf("          if A[i] == x:\n");
            printf("              return i\n");
            printf("      return -1\n");
            printf("  Complejidad: O(n)\n");
            break;

        case STRUCT_LINKED_LIST:
            printf("\n[Insercion al inicio]\n");
            printf("  function insert_front(head, x):\n");
            printf("      newNode = Nodo(x)\n");
            printf("      newNode.next = head\n");
            printf("      head = newNode\n");
            printf("  Complejidad: O(1)\n");

            printf("\n[Busqueda]\n");
            printf("  function find(head, x):\n");
            printf("      curr = head\n");
            printf("      while curr != NULL:\n");
            printf("          if curr.data == x:\n");
            printf("              return curr\n");
            printf("          curr = curr.next\n");
            printf("      return NULL\n");
            printf("  Complejidad: O(n)\n");
            break;

        case STRUCT_STACK:
            printf("\n[Push]\n");
            printf("  function push(S, x):\n");
            printf("      S.top = S.top + 1\n");
            printf("      S[A.top] = x\n");
            printf("  Complejidad: O(1)\n");

            printf("\n[Pop]\n");
            printf("  function pop(S):\n");
            printf("      if S.top < 0: error\n");
            printf("      x = S[S.top]\n");
            printf("      S.top = S.top - 1\n");
            printf("      return x\n");
            printf("  Complejidad: O(1)\n");
            break;

        case STRUCT_QUEUE:
            printf("\n[Enqueue]\n");
            printf("  function enqueue(Q, x):\n");
            printf("      Q[rear] = x\n");
            printf("      rear = rear + 1 (mod capacidad)\n");
            printf("  Complejidad: O(1)\n");

            printf("\n[Dequeue]\n");
            printf("  function dequeue(Q):\n");
            printf("      if front == rear: error (vacia)\n");
            printf("      x = Q[front]\n");
            printf("      front = front + 1 (mod capacidad)\n");
            printf("      return x\n");
            printf("  Complejidad: O(1)\n");
            break;

        case STRUCT_BST:
            printf("\n[Busqueda]\n");
            printf("  function searchBST(node, x):\n");
            printf("      if node == NULL: return NULL\n");
            printf("      if x == node.key: return node\n");
            printf("      else if x < node.key:\n");
            printf("          return searchBST(node.left, x)\n");
            printf("      else:\n");
            printf("          return searchBST(node.right, x)\n");
            printf("  Complejidad promedio: O(log n)\n");

            printf("\n[Insercion]\n");
            printf("  function insertBST(node, x):\n");
            printf("      if node == NULL:\n");
            printf("          node = Nodo(x)\n");
            printf("      else if x < node.key:\n");
            printf("          node.left = insertBST(node.left, x)\n");
            printf("      else:\n");
            printf("          node.right = insertBST(node.right, x)\n");
            printf("      return node\n");
            printf("  Complejidad promedio: O(log n)\n");
            break;

        case STRUCT_HEAP:
            printf("\n[Insert en min-heap]\n");
            printf("  function heapInsert(H, x):\n");
            printf("      H.size = H.size + 1\n");
            printf("      i = H.size\n");
            printf("      H[i] = x\n");
            printf("      while i > 1 and H[parent(i)] > H[i]:\n");
            printf("          swap(H[parent(i)], H[i])\n");
            printf("          i = parent(i)\n");
            printf("  Complejidad: O(log n)\n");

            printf("\n[Extraer minimo]\n");
            printf("  function extractMin(H):\n");
            printf("      min = H[1]\n");
            printf("      H[1] = H[H.size]\n");
            printf("      H.size = H.size - 1\n");
            printf("      heapifyDown(1)\n");
            printf("      return min\n");
            printf("  Complejidad: O(log n)\n");
            break;

        case STRUCT_GRAPH:
            printf("\n[Recorrido BFS con lista de adyacencia]\n");
            printf("  function BFS(G, s):\n");
            printf("      crear cola Q\n");
            printf("      marcar s como visitado\n");
            printf("      enqueue(Q, s)\n");
            printf("      while Q no vacia:\n");
            printf("          u = dequeue(Q)\n");
            printf("          para cada vecino v de u:\n");
            printf("              if v no visitado:\n");
            printf("                  marcar v\n");
            printf("                  enqueue(Q, v)\n");
            printf("  Complejidad: O(V + E)\n");
            break;

        default:
            printf("No hay pseudocodigo disponible.\n");
            break;
    }
}
