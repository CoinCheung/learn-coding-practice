#ifndef _DATASTR_H_
#define _DATASTR_H_
/* =============================================================
 *  header files
 * ============================================================= */
#include<stdlib.h>
#include<stdio.h>




/* =============================================================
 *  micros and types 
 * ============================================================= */

typedef struct queuenode queuenode;
typedef struct queue queue;



/* =============================================================
 *  function definitions
 * ============================================================= */

void init_queue(queue *);
void add(queue *, int);
void printrear(queue *);



#endif
