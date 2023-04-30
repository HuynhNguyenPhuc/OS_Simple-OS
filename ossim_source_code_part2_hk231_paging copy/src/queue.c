#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int empty(struct queue_t *q) {
        if (q == NULL)
                return 1;
        return (q->size == 0);
}

void enqueue(struct queue_t *q, struct pcb_t *proc)
{
        /* TODO: put a new process to queue [q] */
        if (q->size == MAX_QUEUE_SIZE) { return; } // Queue is full, return

        // Add the process to the end of the queue
        q->proc[q->size] = proc;
        q->size++;
}

struct pcb_t *dequeue(struct queue_t *q)
{
        /* TODO: return a pcb whose priority is the highest
         * in the queue [q] and remember to remove it from q
         * */
        if (q->size == 0) { return NULL; } // Queue is empty, cannot dequeue

        // Find the process with the highest priority
        int max_priority_idx = 0;
        uint32_t max_priority = q->proc[0]->priority;

        for (int i = 1; i < q->size; i++) {
                if (q->proc[i]->priority > max_priority) {
                        max_priority = q->proc[i]->priority;
                        max_priority_idx = i;
                }
        }

        // Remove the process from the queue
        struct pcb_t *removed_proc = q->proc[max_priority_idx];

        for (int i = max_priority_idx; i < q->size - 1; i++) { q->proc[i] = q->proc[i + 1]; }

        q->size--;

        return removed_proc;
}
