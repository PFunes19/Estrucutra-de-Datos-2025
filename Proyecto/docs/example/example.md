# Ejemplo: Sistema de atención de llamadas (Call Center)

## 1. Descripción del problema
Un call center recibe llamadas de clientes. Si todos los agentes están ocupados, las llamadas deben esperar en el mismo orden en que llegan. El comportamiento es claramente **FIFO**, lo que corresponde al uso de una **cola (queue)** como estructura de datos.

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

Resultado: `need_fifo = 1` y `need_lifo = 0` → **Queue**.

---

## 3. Estructura recomendada: Cola (Queue)

```text
front -> [ C1 ] -> [ C2 ] -> [ C3 ] <- rear

    - front: llamada que será atendida primero.
    - rear: última llamada que llegó.

---

## 4. Estructura recomendada: Cola (Queue)

enqueue (llega una llamada)