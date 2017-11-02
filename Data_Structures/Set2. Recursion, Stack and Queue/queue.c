#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

int main(){
	queue q = newQueue(10);
	while(1){
		printf("Press 1 to enQueue.\nPress 2 to deQueue.\nPress 3 to know queueSize.\n\
Press 4 to check queue empty.\nPress 5 to know the value at queue front.\nPress 6 to exit.\n");
		int n;
		scanf("%d", &n);
		if(n == 1){
			printf("Enter the value to add to queue: ");
			scanf("%d", &n);
			enQueue(q, n);
		}
		else if(n == 2) deQueue(q);
		else if(n == 3) printf("%d\n", queueSize(q));
		else if(n == 4) {
			if(queueIsEmpty(q)) printf("Queue is empty!.\n");
			else printf("Queue is not empty!\n");
		}
		else if(n == 5) queueFront(q);
		else if(n == 6) break;
		else printf("INVALID INPUT.\n");
	}
	print(q);
	return 0;
}

void print(queue q){
	while(!queueIsEmpty(q)){
		queueFront(q);
		deQueue(q);
	}
}
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
void enQueue (queue q, int x){
	if(q->size == q->maxSize) printf("Sorry Can't enQueue. Queue is full.\n");
	else {
		q->last = (q->last+1)%(q->maxSize);
		q->a[q->last] = x;
		q->size += 1;
	}
	return;
}
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