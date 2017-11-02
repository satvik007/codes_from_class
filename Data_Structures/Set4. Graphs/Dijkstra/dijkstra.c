// Satvik Choudhary
// 111601021

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define inf 100000000
#include "graph.h"

int dist[105], graph[105][105], n, dotted[105][105];
char matrix[105][105];
int parent[105];

int min(int a, int b){
	return (a <= b ? a : b);
}

int minDist(int dist[], bool sptSet[]){
	int min = inf+3, index, i;
	for(i=0; i<n; i++){
		if(!sptSet[i] && dist[i] <= min){
			min = dist[i]; index = i;
		}	
	}	
	return index;
}

void print_path(int v){
	if(parent[v] != -1){ // if the target is not found make a recursive call.
		print_path(parent[v]);
		dotted[parent[v]][v] = 1; // red  
		dotted[v][parent[v]] = 1; // red
	} 
 	printf("%d ", v);
	return;
}


void dijkstra(int src, int v){
	int i, j;
	memset(parent, -1, sizeof parent);
	bool sptSet[105];
	for(i=0; i<n; i++){
		dist[i] = inf;
		sptSet[i] = false;
	}
	dist[src] = 0;
	for(i=0; i<n-1; i++){
		int u = minDist(dist, sptSet);
		sptSet[u] = true;
		for(j=0; j<n; j++){
			if(!sptSet[j] && graph[u][j] && dist[j] > dist[u]+graph[u][j]){
				parent[j] = u;
				dist[j] = dist[u]+graph[u][j];
				
			}
		}
	}
	printf("The shortest path between the source and target vertex is %d.\n", dist[v]);
	memset(dotted, 0, sizeof dotted);
	print_path(v); printf("\n");
}

int main(){
	int src, v;
	n = read_input(matrix, graph);
	int i, j;
	//for(i=0; i<n; i++){for(j=0; j<n; j++){printf("%d", graph[i][j]);}printf("\n");}
	printf("Enter the source vertex and the next vertex: ");
	scanf("%d%d", &src, &v);
	dijkstra(src, v);
	write_output(matrix, n, dotted);
	return 0;
}
