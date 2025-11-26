# Asistente de selección de estructuras de datos (C)

Este proyecto es un asistente interactivo en C que hace una serie de preguntas sobre cómo se van a usar los datos en un problema y, con base en las respuestas, recomienda una estructura de datos adecuada.  

Además de la recomendación, el sistema muestra:

- Una representación visual sencilla (diagrama ASCII).
- Una explicación de por qué se eligió esa estructura.
- Pseudocódigo de operaciones típicas con su complejidad temporal.

---

## Objetivo del proyecto

Ayudar a un usuario (por ejemplo, un estudiante de estructuras de datos) a conectar los **requisitos de un problema** con la **estructura de datos** más razonable, usando un cuestionario guiado y reglas de decisión explícitas.

---

## Estructuras de datos soportadas

El sistema puede recomendar, entre otras:

- Arreglo (Array)
- Lista ligada (Linked List)
- Pila (Stack)
- Cola (Queue)
- Árbol binario de búsqueda (BST)
- Heap / Priority Queue
- Grafo


---

## Funcionamiento general

1. El programa hace una serie de preguntas de tipo **sí/no** sobre:
   - Acceso por índice.
   - Inserciones/eliminaciones en medio.
   - Comportamiento FIFO (cola) o LIFO (pila).
   - Necesidad de mantener los datos ordenados.
   - Uso de prioridades.
   - Relaciones complejas tipo grafo.
   - Tamaño y dinamismo del conjunto de datos.

2. Con las respuestas, el programa aplica una **lógica de decisión** (reglas if/else) para seleccionar una estructura de datos.

3. Finalmente, muestra:
   - El nombre de la estructura recomendada.
   - Un diagrama ASCII.
   - Una explicación de la recomendación.
   - Pseudocódigo de operaciones básicas con su complejidad Big-O.

---

## Requisitos

- **Sistema operativo:** Windows.
- **Compilador C:** `gcc` disponible en el `PATH` (por ejemplo, mediante MinGW-w64 u otra distribución de GCC para Windows).

---

## Cómo ejecutar el sistema (Run-Anywhere Behavior)

Para cumplir con el requisito de tener una forma sencilla de ejecutar el sistema con un solo comando en Windows, el proyecto incluye un archivo `run.bat` en la raíz del repositorio.

### Pasos

1. Clona o descarga este repositorio.
2. Verifica que la estructura de carpetas sea similar a:

   ```text
   /README.md
   /run.bat
   /src/
       main.c
   /docs/
       decision_questions.md
       decision_rules.md
       ... (diagramas, slides, etc.)
   /example/
       ... (ejemplo basado en alguna tarea)
   /tests/
       ... (pruebas de la lógica de decisión)
3. Asegúrate de tener gcc instalado y agregado al PATH.

4. En Windows, abre una terminal en la carpeta del proyecto y ejecuta:

run.bat