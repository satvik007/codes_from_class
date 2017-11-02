#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define inf 1000000000

int min(int a, int b){
    return (a <= b ? a : b);
}
char matrix[100][100]; // matrix to store the adjacency matrix
int visited[100], anc[100]; // keeps account of the visited vertices.
int dist[100][100];
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

char colors[100][100] = {"red", "brown1", "deepskyblue1", "bisque", "crimson",
                         "aquamarine1", "azure", "darkslategray",
                         "darkorange1", "darkorange1", "gold"};

// recursive function for finding and printing the path.
void print_path(int v){
    if(anc[v] != -1){ // if the target is not found make a recursive call.
        print_path(anc[v]);
        matrix[anc[v]][v] = 0; // red
        matrix[v][anc[v]] = 0; // red
    }
    printf("%d ", v);
}

// bfs function which uses queue to generate the bfs tree.
void bfs(int u, int v){
    int i = 0;
    memset(visited, 0, sizeof(visited)); // initializing all visited nodes 0
    memset(anc, -1, sizeof(anc)); // initializing all ancestors -1
    queue que = newQueue(105);
    visited[u] = 1;
    enQueue(que, u); // enQueuing the source.
    int flag = 1;
    while(!queueIsEmpty(que) && flag){
        int temp = deQueue(que);
        if(temp == v){
            break;
        }
        for(i=0; i<n; i++){
            if(matrix[temp][i] == '1' && !visited[i]){ // unvisited edge
                anc[i] = temp; // setting ancestor.
                visited[i] = 1; // the vertex is now visited.
                enQueue(que, i); // enqueuing the new vertex.
            }
        }
    }
    print_path(v); printf("\n");
}

int floydWarshall(){
    int i, j, k;
    // initialising the shortest dp matrix.
    for(i=0; i<n; i++){
        for(j=0; j<n; j++) dist[i][j] = inf;
        dist[i][i] = 0;
    }
    // settling for the known distances.
    for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            if(matrix[i][j] == '1') dist[i][j] = 1;
        }
    }
    // Using dp finding the all pairs shortest paths.
    for(k=0; k<n; k++){
        for(i=0; i<n; i++){
            for(j=0; j<n; j++){
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    int max1 = -1;
    int flag = 0;
    int index1 = 0, index2 = 0;
    for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            if(dist[i][j] == inf) flag = 1; // graph is not connected.
            if(dist[i][j] > max1){ // diameter of the graph.
                max1 = dist[i][j];
                index1 = i;
                index2 = j;
            }
        }
    }
    if(flag) printf("The graph is not connected.\n");
    else{
        printf("The diameter of the graph is %d.\n", max1);
        bfs(index1, index2); // color the requred edges.
    }

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
    floydWarshall();
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