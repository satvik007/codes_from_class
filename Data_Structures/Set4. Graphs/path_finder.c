// Satvik Choudhary
// 111601021

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <ctype.h>

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


char matrix[100][100];
int n;
int visited[105];

// reading the adjacency matrix and writing into a 2d char array.
void read(){
	int i=0;
	char file1[50];
	printf("Enter the name of the input file: ");
	scanf("%s", file1);
	char name[50];
	char type[50];
	FILE *p;
	p = fopen(file1, "r");
	fscanf(p, "%s\n%s\n", name, type);
	fscanf(p, "%d\n", &n);
	for(i=0; i<n; i++){
		fscanf(p, "%s\n", matrix[i]);
	}
	fclose(p);
}

int anc[105];
int dist[105];

// recursive function for finding and printing the path.
void print_path(int v){
	if(anc[v] != -1){ // if the target is not found make a recursive call.
		print_path(anc[v]);
		matrix[anc[v]][v] = '2'; // red  
		matrix[v][anc[v]] = '2'; // red
	} 
 	printf("%d ", v);
	return;
}

// bfs function which uses queue to generate the bfs tree.
void bfs(int u, int v){
	int i = 0;
	memset(visited, 0, sizeof(visited)); // initializing all visited nodes 0
	memset(anc, -1, sizeof(anc)); // initializing all ancestors -1
	queue que = newQueue(105);
	visited[u] = 1;
	dist[u] = 0;
	enQueue(que, u); // enQueuing the source.
	int flag = 1;
	if(u>n-1) flag = 0; // to prevent out of bound.
	while(!queueIsEmpty(que) && flag){
		int temp = deQueue(que);
		if(temp == v){
			flag = 0;
			break;
		}
		for(i=0; i<n; i++){
			if(matrix[temp][i] == '1' && !visited[i]){ // unvisited edge
				anc[i] = temp; // setting ancestor.
				dist[i] = dist[temp] + 1; // storing its distance.
				visited[i] = 1; // the vertex is now visited.
				enQueue(que, i); // enqueuing the new vertex.
			}
		}
	}
	if(flag){
		printf("No path between the two vertices.\n");
		return;
	}
	else {
		printf("There is a path between the two vertices.\n");
		printf("The length of the path is %d.\n", dist[v]);
		print_path(v); printf("\n");
	}
}

// writing a xdot file with the bfs path shown.
void write_output(){
	char file2[50];
	printf("Enter the name of the output file: ");
	scanf("%s", file2);
	FILE *q;
	q = fopen(file2, "w");
	fprintf(q, "graph BFS{\n");
	for(int i=0; i<n; i++){
		int flag = 0;
		for(int j=i+1; j<n; j++){
			if(matrix[i][j] == '1'){ // black edge.
				flag = 1;
				fprintf(q, "\t%d -- %d ;\n", i, j);
			}
			else if(matrix[i][j] == '2'){ // red edge.
				flag = 1;
				fprintf(q, "\t%d -- %d[color = red];\n", i, j);
			}
		}
		if(!flag){
			fprintf(q, "\t%d\n", i);
		}
	}
	fprintf(q, "}\n");
	fclose(q);
}

int main(){
	read();
	int u, v;
	printf("Enter the initial and final vertex: ");
	scanf("%d%d",  &u, &v);
	bfs(u, v);
	write_output();
	return 0;
}

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
