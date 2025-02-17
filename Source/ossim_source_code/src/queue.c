#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int empty(struct queue_t * q) {
        if (q == NULL) return 1;
	return (q->size == 0);
}

void enqueue(struct queue_t * q, struct pcb_t * proc) {
        /* TODO: put a new process to queue [q] */
        // #ifdef MLQ_SCHED
        // if (q != NULL && q->size < MAX_QUEUE_SIZE) {
        //         q->proc[q->size] = proc;
        //         q->size++;
        // }
        // #else
        // for (int i = 0; i < q->size; i++) {
        //         if (q->proc[i]->priority <= proc->priority) {
        //                 for (int j = q->size - 1; j >= i; j--)
        //                 q->proc[j + 1] = q->proc[j];

        //                 q->proc[i] = proc;
        //                 q->size++;
        //                 return;
        //         }
        // }

        // q->proc[q->size] = proc;
        // q->size++;
        // #endif
        /* TODO: put a new process to queue [q] */
        // Find the correct position to insert the new process based on its priority
        // print_queue(q, 1);
        if (q == NULL)
        {
                return; // q is not initialized
                perror("Queue is null !\n");
                exit(1);
        }
        if (q->size == MAX_QUEUE_SIZE)
        {
                perror("Queue is full\n"); // queue [q] is full, cannot put more process
                exit(1);
        }
        q->proc[q->size] = proc;
        q->size = q->size + 1;
}

struct pcb_t * dequeue(struct queue_t * q) {
        /* TODO: return a pcb whose prioprity is the highest
         * in the queue [q] and remember to remove it from q
         * */
         
	// struct pcb_t * proc = NULL;
	// proc = q->proc[0];
        // for(int j = 0; j < MAX_QUEUE_SIZE; j++){
        //         if(j != MAX_QUEUE_SIZE - 1)
        //                 q->proc[j] = q->proc[j+1]; 
        //         else    
        //                 q->proc[j] = NULL;                        
        // }
        // q->size--;
	// return proc;
         /* TODO: return a pcb whose prioprity is the highest
         * in the queue [q] and remember to remove it from q
         * */

        if (empty(q))
        {
                return NULL; // q is not initialized or q is empty, cannot remove process
        }
        struct pcb_t *temp = q->proc[0]; // Get the first process in queue
        // print_queue(q, 1);
#ifdef MLQ_SCHED
        for (int i = 0; i < q->size - 1; i++)
        {
                q->proc[i] = q->proc[i + 1];
        }
        q->proc[q->size - 1] = NULL;
        q->size = q->size - 1;
        // print_queue(q, 2);
        return temp;
#else
        int index = 0;
        for (int i = 1; i < q->size; i++)
        {
                if (q->proc[i]->priority < q->proc[index]->priority)
                {
                        index = i;
                }
        }
        struct pcb_t *remove_process = q->proc[index]; // Get the process with highest priority

        // Remove that process, push all processes after that up 1 position
        for (int i = index; i < q->size - 1; i++)
        {
                q->proc[i] = q->proc[i + 1];
        }
        q->proc[q->size - 1] = NULL;
        q->size = q->size - 1;
        // print_queue(q, 2);
        return remove_process;
#endif
}
