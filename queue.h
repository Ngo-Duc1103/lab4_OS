
#ifndef QUEUE_H
#define QUEUE_H

#include "structs.h"

/* Initialize the process queue */
void initialize_queue(struct pqueue_t * q);

/* Get a process from a queue */
struct pcb_t * de_queue(struct pqueue_t * q);

/* Put a process into a queue */
void en_queue(struct pqueue_t * q, struct pcb_t * proc);

/* Put a process into inqueue different from that for the ready queue*/
void en_inqueue(struct pqueue_t * q, struct pcb_t * proc);

int empty(struct pqueue_t * q);

#endif


