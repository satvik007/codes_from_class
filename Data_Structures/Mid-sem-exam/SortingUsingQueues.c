// Satvik Choudhary
// 111601021
// 10.64.1.174
// Serial number c
// Question 3
// Assumptions positive integers.
// Logic - selection sort on one queue and entering the minimum elements into another queue. O(n^2) algorithm 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define inf 1000000000
int a[100];
typedef long long ll;
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
//int queueSize (queue q);
int queueIsEmpty (queue q);
//void queueFront (queue q);
void print(queue q);

int main(){
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	queue q1 = newQueue(100);
	queue q2 = newQueue(100);
	int n;
	printf("Enter n: ");
	scanf("%d", &n);
	int i = 0;
	printf("Enter the elements: ");
	for(i = 0; i<n; i++){
		scanf("%d", &a[i]);
	}
	for(i = 0; i<n; i++){
		enQueue(q1, a[i]);
	}
	int min1;
	int m = n;
	while(!queueIsEmpty(q1)){
		min1 = inf;
		for(i = 0; i<m; i++){
			int current = deQueue(q1);
			if(current < min1) {
				min1 = current;
			}
			enQueue(q1, current);
		}
		int ind = 0;
		for(i = 0; i<m; i++){
			int current = deQueue(q1);
			if(current == min1){
				enQueue(q2, current);
				ind++;
			}
			else enQueue(q1, current);
		}
		m -= ind;
	}
	print(q2);
	return 0;
}

void print(queue q){
	while(!queueIsEmpty(q)){
		printf("%d ", deQueue(q));
	}
	printf("\n");
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
}/*
int queueSize (queue q){
	return q->size;
}*/
int queueIsEmpty (queue q){
	if(q->size == 0) return 1;
	else return 0;
}
/*void queueFront (queue q){
	if(q->size == 0) printf("The queue is empty.\n");
	else printf("%d\n", q->a[q->first]);
}*/
