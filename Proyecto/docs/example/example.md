# Ejemplo: Sistema de atención de llamadas (Call Center)

## 1. Descripción del problema
Un call center recibe llamadas de clientes. Si los agentes están ocupados, las llamadas esperan en el mismo orden en que llegan. Este comportamiento es **FIFO**, por lo que la estructura adecuada es una **cola (queue)**.

---

## 2. Respuestas del cuestionario

| Pregunta | Respuesta |
|---------|-----------|
| ¿Acceso rápido por índice? | 0 |
| ¿Inserciones en medio? | 0 |
| ¿FIFO? | 1 |
| ¿LIFO? | 0 |
| ¿Orden automático? | 0 |
| ¿Prioridad? | 0 |
| ¿Relaciones tipo grafo? | 0 |
| ¿Tamaño dinámico grande? | 1 |

Resultado: **Queue**.

---

## 3. Estructura recomendada: Cola (Queue)

```text
    front -> [ C1 ] -> [ C2 ] -> [ C3 ] <- rear
```
---
## 4. Pseudocódigo escnecial
enqueue(nueva llamada)
```text
enqueue(Q, x):
    Q[rear] = x
    rear = (rear + 1) mod capacidad
```
dequeue (un agente atiende)
```text
dequeue(Q):
    x = Q[front]
    front = (front + 1) mod capacidad
    return x
```
---
## 5. Ejecución del ejemplo
- 1.Llegan C1, C2, C3
```text
front -> [ C1 ] -> [ C2 ] -> [ C3 ] <- rear
```