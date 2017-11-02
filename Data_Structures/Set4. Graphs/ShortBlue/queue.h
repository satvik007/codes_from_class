// Satvik Choudhary
// 111601021

#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <ctype.h>
#include "queue.h"
#define inf 10000000

// queue implementation.
struct queue{
	int maxSize;
	int first;
	int last;
	int size;
	int *a;
};
typedef struct queue* queue;

queue newQueue (int max);
void enQueue (queue q, int x);
int deQueue (queue q);
int queueSize (queue q);
int queueIsEmpty (queue q);
void queueFront (queue q);
void print(queue q);

#endif


