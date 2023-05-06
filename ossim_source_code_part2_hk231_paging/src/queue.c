#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int empty(struct queue_t *q)
{
        if (q == NULL)
                return 1;
        return (q->size == 0);
}

void enqueue(struct queue_t *q, struct pcb_t *proc)
{
        /* TODO: put a new process to queue [q] */
        // printf("go to endquue\n");
        if (q == NULL || q->size >= MAX_QUEUE_SIZE)
                return;
        q->proc[q->size] = proc;
        q->size++;
        // printf("Queue Size after en: %d\n", q->size);
}

struct pcb_t *dequeue(struct queue_t *q)
{
        /* TODO: return a pcb whose prioprity is the highest
         * in the queue [q] and remember to remove it from q
         * */
        if (q == NULL || q->size == 0)
                return NULL;
#ifdef MLQ_SCHED
        struct pcb_t *temp = q->proc[0];
        for (int i = 1; i < q->size; ++i)
        {
                q->proc[i] = q->proc[i + 1];
        }
        q->size--;
        return temp;
#else
        int indx = 0, max_prio = 0;
        for (int i = 0; i < q->size; ++i)
        {
                if (q->proc[i]->priority > max_prio)
                {
                        max_prio = q->proc[i]->priority;
                        indx = i;
                }
        }
        struct pcb_t *temp = q->proc[indx];
        for (int i = indx; i < q->size; ++i)
        {
                q->proc[i] = q->proc[i + 1];
        }
        q->size--;
        // printf("Queue Size after de: %d\n", q->size);
        return temp;
#endif
}
