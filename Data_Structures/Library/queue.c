// Satvik Choudhary
// 111601021

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <ctype.h>
#include "queue.h"
#define inf 10000000

// not used in this program.
void print(queue q){
	while(!queueIsEmpty(q)){
		queueFront(q);
		deQueue(q);
	}
}

// creating a new queue with an array as the base data structure.
queue newQueue(int max){
	queue q = (queue) malloc (sizeof(queue));
	q->first = 0;
	q->last = max-1;
	q->size = 0;
	q->maxSize = max;
	q->a = (int*) malloc (sizeof(int)*q->maxSize);
	for(int i=0; i<q->maxSize; i++) q->a[i] = 0;
	return q;
}

// Entering a new number at the end of the queue
void enQueue (queue q, int x){
	if(q->size == q->maxSize) printf("Sorry Can't enQueue. Queue is full.\n");
	else {
		q->last = (q->last+1)%(q->maxSize);
		q->a[q->last] = x;
		q->size += 1;
	}
	return;
}

// Taking out an element from the front of the queue.
int deQueue (queue q){
	static int x = -1;
	if(q->size == 0) printf("Can't deQueue. Queue is empty.\n");
	else{
		x = q->a[q->first];
		q->first = (q->first+1)%(q->maxSize);
		q->size -= 1;
	}
	return x;
}
int queueSize (queue q){
	return q->size;
}
int queueIsEmpty (queue q){
	if(q->size == 0) return 1;
	else return 0;
}
void queueFront (queue q){
	if(q->size == 0) printf("The queue is empty.\n");
	else printf("%d\n", q->a[q->first]);
}
