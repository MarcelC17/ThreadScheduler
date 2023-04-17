#include<stdio.h>
#include<limits.h>
#include <stdlib.h>
#define QUECAP 696
#define MAXIO 256

#include "util/so_scheduler.h"

typedef struct queueElem{
    int time;
    tid_t tid;
} *thread;

typedef struct queue{
  int idx;
  unsigned int time_quantum;
  int io;
  thread* threads;
  int* threadprior; 
} *threadQueue, tq;


int isEmpty(threadQueue q){
    return q->idx == -1;
}

int isFull(threadQueue q){
    return q->idx == QUECAP - 1;
}
// Insert the element in maintaining items in sorted order 
// of their priority
void enqueue(thread thr, int priority, threadQueue thrQueue)
{
    if(!isFull(thrQueue)){
        
        // first item being entered
        if(thrQueue->idx == -1){
            thrQueue->idx++; // increase the index
            thrQueue->threads[thrQueue->idx] = thr;
            thrQueue->threadprior[thrQueue->idx] = priority;
            return;
        }
        else{
             // Increase the index
            thrQueue->idx++;
            // in reverse order
            for(int i = thrQueue->idx-1; i >= 0;i--){
                // shift all items rightwards with higher priority
                // than the element we trying to insert
                if(thrQueue->threadprior[i] >= priority){
                    thrQueue->threads[i+1] = thrQueue->threads[i];
                   thrQueue->threadprior[i+1] =thrQueue->threadprior[i];
                }
                else{
                    // insert item just before where
                    // lower priority index was found
                    thrQueue->threads[i+1] = thr;
                    thrQueue->threadprior[i+1] = priority;
                    break;
                }
                
            }
        }

    }
}

// returns item with highest priority
// note highest priority in max priority queue is last item in array
int peek(threadQueue thrQueue)
{
    return  thrQueue->idx;
}

// just reducing index would mean we have dequed
// the value would be sitll there but we can say that 
// no more than a garbage value
void dequeue(threadQueue thrQueue)
{
        (thrQueue->idx)--;
}


// void display(){
//     for (int i = 0; i <= idx; i++) {
//         printf("(%d, %d)\n",pqVal[i], pqPriority[i]);
//     } 
// }
static threadQueue scheduler = NULL;

int so_init(unsigned int timeq, unsigned int io){

    if (scheduler != NULL || io > MAXIO || timeq <= 0)
    return -1;

    scheduler = malloc(sizeof(tq));
    scheduler->idx = -1;
    scheduler->time_quantum = timeq;
    scheduler->io = io;
    scheduler->threads = malloc(sizeof(thread) * QUECAP);
    scheduler->threadprior= malloc(sizeof(thread) * QUECAP);

    return 0;
}

void so_end(){

}
void so_exec(){

} 
int so_wait(unsigned int io){
    return 0;
} 
int so_signal(unsigned int io){
    return 0;
}
tid_t so_fork(so_handler *func, unsigned int priority){
    return 0;
}