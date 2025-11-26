# Changelog
---


- Se crea el asistente de selección de estructuras de datos en C.
- El programa hace preguntas de tipo sí/no al usuario.
- Se implementa la lógica de decisión básica para recomendar una estructura de datos.
- Se muestran:
  - nombre de la estructura recomendada,
  - diagrama ASCII,
  - explicación de la recomendación,
  - pseudocódigo de operaciones típicas.

---

- Se agregan diagramas ASCII específicos para:
  - Array
  - Lista ligada
  - Stack
  - Queue
  - BST
  - Heap
  - Grafo
- Se añade la función para intentar abrir archivos PNG con los nombres:
  - `Array.png`
  - `Lista ligada.png`
  - `Stack.png`
  - `Queue.png`
  - `BST.png`
  - `Heap.png`
  - `Grafo.png`

---

- Se organiza la carpeta `/docs` con:
  - `decision_questions.md` (preguntas del cuestionario + breve justificación).
  - `decision_rules.md` (reglas de decisión usadas por el sistema).
  - Carpeta de diagramas (`diagrams/`) con las imágenes PNG de las estructuras.
- Se agrega la carpeta `/example` con un caso de uso basado en una tarea (por ejemplo, call center con cola).
- Se agrega `run.bat` en la raíz del proyecto para compilar y ejecutar el programa con un solo comando en Windows.
