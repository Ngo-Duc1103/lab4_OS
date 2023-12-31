
#include <stdlib.h>
#include "queue.h"
#include "structs.h"
#include <pthread.h>

/* Remember to initilize the queue before using it */
void initialize_queue(struct pqueue_t * q) {
	q->head = q->tail = NULL;
	pthread_mutex_init(&q->lock, NULL);
}

/* Return non-zero if the queue is empty */
int empty(struct pqueue_t * q) {
	return (q->head == NULL);
}

/* Get PCB of a process from the queue (q).
 * Return NULL if the queue is empty */
struct pcb_t * de_queue(struct pqueue_t * q) {
	struct pcb_t * proc = NULL;
	// TODO: return q->head->data and remember to update the queue's head
	// and tail if necessary. Remember to use 'lock' to avoid race
	// condition
	
	// YOUR CODE HERE
  if (!q || !(q->head)) return NULL;

  pthread_mutex_lock(&q->lock);
  struct qitem_t *tmp = q->head->next;

  proc = q->head->data;
  free(q->head);
  q->head = tmp;
  
  if (!(q->head)) q->tail = NULL;
  pthread_mutex_unlock(&q->lock);
  
	return proc;
}

/* Put PCB of a process to the inqueue. */
void en_inqueue(struct pqueue_t * q, struct pcb_t * proc) {
	// TODO: Update q->tail.
	// Remember to use 'lock' to avoid race condition
	
	// YOUR CODE HERE
  if (!q || !proc) return;
  
  pthread_mutex_lock(&q->lock);
  struct qitem_t **tmp = &(q->tail);
  if (*tmp) tmp = &((*tmp)->next);

  *tmp = (struct qitem_t *) malloc(sizeof(struct qitem_t));
  (*tmp)->data = proc;
  (*tmp)->next = NULL;
  q->tail = *tmp;
  
  if (!(q->head)) q->head = q->tail;
  pthread_mutex_unlock(&q->lock);
}

// ver2
/* Put PCB of a process to the queue. */
void en_queue(struct pqueue_t * q, struct pcb_t * proc) {
	// TODO: Update into priority preemptive queue.
	// Remember to use 'lock' to avoid race condition
	
	// YOUR CODE HERE
  if (!q || !proc) return;
  
  pthread_mutex_lock(&q->lock);

  struct qitem_t **tmp = &(q->head);
  while ((*tmp) && (*tmp)->data->priority >= proc->priority) {
    tmp = &((*tmp)->next);
  }
  
  struct qitem_t *new_qitem = (struct qitem_t *) malloc(sizeof(struct qitem_t));
  new_qitem->data = proc;
  new_qitem->next = *tmp;
  *tmp = new_qitem;
  
  if (!(q->tail)) q->tail = q->head;
  pthread_mutex_unlock(&q->lock);
}


