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


char matrix[100][100];
char copy[100][100];
int n;
int visited[105];
int blue[105];

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
		for(int j=0; j<n; j++) copy[i][j] = matrix[i][j];
	}
	fclose(p);
}

int anc[105];
int dist[105];

// recursive function for finding and printing the path.
void print_path(int v){
	if(anc[v] != -1){ // if the target is not found make a recursive call.
		print_path(anc[v]);
		matrix[anc[v]][v] = '5'; // red  
		matrix[v][anc[v]] = '5'; // red
	} 
 	printf("%d ", v);
	return;
}

char colors[100][100] = {"red", "green", "blue"};
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
			if(matrix[i][j] != '5' && matrix[i][j] != '0'){ 
				flag = 1;
				fprintf(q, "\t%d -- %d[color=%s];\n", i, j, colors[copy[i][j]-1-'0']);
			}
			else if(matrix[i][j] == '5'){ // red edge.
				flag = 1;
				fprintf(q, "\t%d -- %d[style = dotted, color=%s];\n", i, j, colors[copy[i][j]-1 - '0']);
			}
			
		}
		if(!flag){
			fprintf(q, "\t%d\n", i);
		}
	}
	fprintf(q, "}\n");
	fclose(q);
}

// bfs function which uses queue to generate the bfs tree.
void bfs(int u, int v){
	int i = 0;
	for(i=0; i<n; i++){
		blue[i] = inf;
		dist[i] = inf;
	}
	memset(visited, 0, sizeof(visited)); // initializing all visited nodes 0
	memset(anc, -1, sizeof(anc)); // initializing all ancestors -1
	queue que = newQueue(105);
	visited[u] = 1;
	dist[u] = 0;
	blue[u] = 0;
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
				if(matrix[temp][i] != '0' && !visited[i]){ // unvisited edge
					if(dist[i] < dist[temp] + 1){
						visited[i] = 1;
						continue;
					}	
					dist[i] = dist[temp] + 1;
					if(dist[i] == dist[temp] + 1){
						if(copy[temp][i] == '3' && blue[temp]+1 < blue[i]){
							blue[i] = blue[temp] + 1;
							anc[i] = temp;
						}  
						else if(matrix[temp][i] != '3' && blue[temp] < blue[i]){
							blue[i] = blue[temp];
							anc[i] = temp;
						}
					}
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
		printf("The number of blue edges between the two edges is: %d.\n", blue[v]);
		write_output();
	}
}



int main(){
	read();
	int u, v;
	printf("Enter the initial and final vertex: ");
	scanf("%d%d",  &u, &v);
	bfs(u, v);
	return 0;
}

