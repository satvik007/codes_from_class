// Satvik Choudhary 
// 111601021

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

char matrix[100][100]; // matrix to store the adjacency matrix
int visited[100]; // keeps account of the visited vertices.

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
void emptyQueue(queue q);

int n;
void read_input(){
    FILE *p;
    char filename[50];
    printf("Enter the name of the file: ");
    scanf("%s", filename);
    p = fopen(filename, "r");
    char name[50];
    char dummy[50];
    fscanf(p, "%s\n", name);
    fscanf(p, "%s\n", dummy);
    fscanf(p, "%d\n", &n);
    int i = 0;
    for(i=0; i<n; i++) fscanf(p, "%s\n", matrix[i]);
    fclose(p);
}

char colors[100][100] = {"green", "brown1", "deepskyblue1", "bisque", "crimson",
                   "aquamarine1", "azure", "darkslategray",
                    "darkorange1", "darkorange1", "gold"};
int dfs(){
    memset(visited, 0, sizeof(visited));
    queue que = newQueue(100);
    int counter = 0;
    int j, i;
    for(i=0; i<n; i++){
        if(visited[i]) continue;
        visited[i] = 1; // edge marked as visited.
        counter++;
        int current;
        enQueue(que, i);
        while(!queueIsEmpty(que)){
            current = deQueue(que);
            for(j=0; j<n; j++){
                if(!visited[j] && matrix[current][j] != '0'){
                    matrix[current][j] = counter-1; // coloring the bfs tree.
                    matrix[j][current] = counter-1; // ...
                    enQueue(que, j);
                    visited[j] = 1;
                }
            }
        }
    }
    return counter;
}

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
            // nice handpicked colors in edges.
            else if(matrix[i][j] != '0'){
                flag = 1;
                fprintf(q, "\t%d -- %d[color = %s];\n", i, j, colors[matrix[i][j]]);
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
    read_input();
    int counter = dfs();
    printf("Total number of connected components is %d\n", counter);
    write_output();
    return 0;
}

void emptyQueue(queue q){
    while(!queueIsEmpty(q)){
        deQueue(q);
    }
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
