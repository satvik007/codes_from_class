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
int bridge[105][105];

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
				if(dfs_low[i] > dfs_num[u]) bridge[u][i] = bridge[i][u] = 1;
			} 
			else if(i != parent[u]) dfs_low[u] = min(dfs_low[u], dfs_num[i]); 
		}
	}
}

void call_dfs(){
	memset(dfs_num, -1, sizeof dfs_num);
	memset(dfs_low, 0, sizeof dfs_low);
	memset(art, 0, sizeof art);
	memset(bridge, 0, sizeof bridge);
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

/*
vi dfs_num, dfs_low, S, visited;
// global variables
void tarjanSCC(int u) {
	dfs_low[u] = dfs_num[u] = dfsNumberCounter++; // dfs_low[u] <= dfs_num[u]
	S.push_back(u);
	// stores u in a vector based on order of visitation
	visited[u] = 1;
	for (int j = 0; j < (int)AdjList[u].size(); j++) {
		ii v = AdjList[u][j];
		if (dfs_num[v.first] == UNVISITED)
		tarjanSCC(v.first);
		if (visited[v.first])
		// condition for update
			dfs_low[u] = min(dfs_low[u], dfs_low[v.first]); }
		if (dfs_low[u] == dfs_num[u]) {
		// if this is a root (start) of an SCC
			printf("SCC %d:", ++numSCC);
			// this part is done after recursion
			while (1) {
			int v = S.back(); S.pop_back(); visited[v] = 0;
			printf(" %d", v);
			if (u == v) break; 
		}
		printf("\n");
	} 
}
// inside int main()
dfs_num.assign(V, UNVISITED); dfs_low.assign(V, 0); visited.assign(V, 0);
dfsNumberCounter = numSCC = 0;
for (int i = 0; i < V; i++)
if (dfs_num[i] == UNVISITED)
tarjanSCC(i);
*/