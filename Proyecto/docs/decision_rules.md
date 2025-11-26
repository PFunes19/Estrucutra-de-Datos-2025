# decision_rules.md
# Reglas de decisión del asistente de estructuras de datos

Este documento describe cómo el asistente convierte las respuestas del cuestionario
en la recomendación de una estructura de datos.

Campos de respuesta (0 = No, 1 = Sí):

- need_random_access              – ¿Necesito acceso rápido por índice?
- frequent_insert_delete_middle   – ¿Inserto/borro mucho en medio de la colección?
- need_fifo                       – ¿Uso patrón FIFO (primero en entrar, primero en salir)?
- need_lifo                       – ¿Uso patrón LIFO (último en entrar, primero en salir)?
- need_sorted                     – ¿Debo mantener los datos ordenados automáticamente?
- need_priority                   – ¿Siempre extraigo primero el elemento de mayor/menor prioridad?
- need_graph_relationships        – ¿Hay relaciones complejas tipo grafo?
- expected_size_large             – ¿El tamaño puede crecer mucho y de forma dinámica?

---

## 1. Regla: problemas con relaciones tipo grafo

Condición:

    if need_graph_relationships == 1:
        recomendar -> Grafo

Interpretación (resumen):
- Si el problema es una red de nodos y conexiones (rutas, usuarios, ciudades, etc.), se usa un grafo.

---

## 2. Regla: prioridades explícitas

Condición:

    else if need_priority == 1:
        recomendar -> Heap / Priority Queue

Interpretación:
- Si lo importante es extraer siempre el elemento de mayor (o menor) prioridad, se usa heap/priority queue.

---

## 3. Regla: comportamiento FIFO (cola)

Condición:

    else if need_fifo == 1 and need_lifo == 0:
        recomendar -> Queue

Interpretación:
- Si los elementos se procesan en el mismo orden en que llegan, se usa una cola (queue).

---

## 4. Regla: comportamiento LIFO (pila)

Condición:

    else if need_lifo == 1 and need_fifo == 0:
        recomendar -> Stack

Interpretación:
- Si el patrón es “último en entrar, primero en salir”, se usa una pila (stack).

---

## 5. Regla: datos ordenados

Condición:

    else if need_sorted == 1:
        recomendar -> Arbol binario de búsqueda (BST)

Interpretación:
- Si los datos deben mantenerse ordenados automáticamente, se usa un BST.

---

## 6. Regla: acceso rápido por índice

Condición:

    else if need_random_access == 1
            and frequent_insert_delete_middle == 0:
        recomendar -> Array

Interpretación:
- Si necesito acceso rápido por índice y casi no inserto/borro en medio, se usa un arreglo (array).

---

## 7. Regla: muchas inserciones en medio o tamaño dinámico

Condición:

    else if frequent_insert_delete_middle == 1
            or expected_size_large == 1:
        recomendar -> Lista ligada

Interpretación:
- Si hay muchas inserciones/borrados en posiciones intermedias o el tamaño cambia mucho, se usa lista ligada.

---

## 8. Regla: caso por defecto

Condición:

    else:
        recomendar -> Array

Interpretación:
- Si ninguna condición anterior aplica claramente, se recomienda array como opción por defecto.

---

## 9. Resumen en tabla

| Orden | Condición principal                                         | Estructura recomendada | Comentario breve                                      |
|-------|-------------------------------------------------------------|------------------------|-------------------------------------------------------|
| 1     | need_graph_relationships == 1                               | Grafo                  | Nodos y relaciones complejas.                        |
| 2     | need_priority == 1                                          | Heap / Priority Queue  | Siempre extraer según prioridad.                     |
| 3     | need_fifo == 1 and need_lifo == 0                           | Queue                  | Comportamiento FIFO.                                 |
| 4     | need_lifo == 1 and need_fifo == 0                           | Stack                  | Comportamiento LIFO.                                 |
| 5     | need_sorted == 1                                            | BST                    | Mantener datos ordenados.                            |
| 6     | need_random_access == 1 y pocas inserciones en medio        | Array                  | Acceso rápido por índice.                            |
| 7     | frequent_insert_delete_middle == 1 o expected_size_large == 1 | Lista ligada        | Inserciones/borrados frecuentes, tamaño dinámico.    |
| 8     | Ninguna de las anteriores                                   | Array                  | Caso por defecto.                                    |
