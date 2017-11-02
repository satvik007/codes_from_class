// Satvik Choudhary
// 111601021

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define inf 100000000
#include "graph.h"

int graph[105][105], n;
char matrix[105][105];
int parent[105], dfs_low[105], dfs_num[105], cool, counter, art[105], ans, root, child;

int min(int a, int b){
	return (a <= b ? a : b);
}

void dfs(int u){
	int i;
	//printf("%d\n", u);
	dfs_low[u] = dfs_num[u] = cool++;
	for(i=0; i<n; i++){
		if(graph[u][i]){
			if(dfs_num[i] == -1){
				parent[i] = u;
				if(u == root) child++;
				dfs(i);
				if(dfs_low[i] >= dfs_num[u]) art[u] = 1;
			} 
			else if(i != parent[u]) dfs_low[u] = min(dfs_low[u], dfs_num[i]); 
		}
	}
}

void call_dfs(){
	memset(dfs_num, -1, sizeof dfs_num);
	memset(dfs_low, 0, sizeof dfs_low);
	memset(art, 0, sizeof art);
	cool = counter = 0;
	int i;
	for(i=0; i<n; i++){
		if(dfs_num[i] == -1){
			root = i, child = 0, dfs(i);
			art[root] = (child > 1);
		}
	}
	for(int i=0; i<n; i++) if(art[i]){
		printf("%d ", i);
	}
	puts("");
}

int main(){
	n = read_input(matrix, graph);
	call_dfs();
	write_output(matrix, n, art);
	return 0;
}
