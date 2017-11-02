// Satvik Choudhary
// 111601021

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define inf 100000000
#include "graph.h"

int dist[105], graph[105][105], n, dotted[105][105], visited[105];
char matrix[105][105];
int parent[105];

int min(int a, int b){
	return (a <= b ? a : b);
}

void dfs(int u){
	int i;
	visited[u] = 1;
	for(i=0; i<n; i++){
		if(graph[u][i] && !visited[i]){
			matrix[u][i] = matrix[i][u] = '2';
			dfs(i);
		}
	}
}

void call_dfs(){
	memset(visited, 0, sizeof visited);
	int i=0;
	printf("Enter the root node please: ");
	scanf("%d", &i);
	dfs(i);
}

int main(){
	n = read_input(matrix, graph);
	call_dfs();
	write_output(matrix, n);
	return 0;
}
