// Satvik Choudhary
// 111601021

#include <bits/stdc++.h>
#include "graph.h"
#include "dlist.h"
#define inf (int)1e8
using namespace std;

int n, visited[maxn]; // size of graph, keeping track of visited vertices.
Dlist matrix[maxn], graph[maxn]; // graph stored as adjacency list,
// type of edge (tree, forward etc.) also stored as adjacency list.
int parent[maxn], started[maxn], finished[maxn]; // keep track of the dfs tree.
int cnt1, cnt2; // counters to keep track of the new nodes or leaving old nodes.
int globalTime;
int startTimes[maxn], leaveTimes[maxn];

void dfs(int u){
	int i;
	started[u] = cnt1++; // new node entered and its assigned its entry number.
	visited[u] = 1; // node is marked as visited.
	Node* current = matrix[u].root1; // edges
	startTimes[u] = globalTime++;
	for(; current->data != -1; current = current->next){
		int v = current->data;
		if(!visited[v]){
			DlistAddAtBack(&graph[u], 1); // tree
			dfs(v);
		}else{
			if(finished[v] == 0){
				DlistAddAtBack(&graph[u], 2); // back
			}else if(started[v] > started[u]){
				DlistAddAtBack(&graph[u], 3); // forward
			}else{
				DlistAddAtBack(&graph[u], 4); // cross
			}
		}
	}
	leaveTimes[u] = globalTime++;
	DlistAddAtBack(&graph[u], -1); // Not so much useful but its okay.
	finished[u] = cnt2++; // When we leave the node we assign its number.
}

void call_dfs(){
	memset(visited, 0, sizeof visited);
	memset(finished, 0, sizeof finished);
	memset(started, 0, sizeof started);
	int i=0; 
	globalTime = 0;
	cnt1 = 1; cnt2 = 1;
	for(int i=0; i<n; i++){
		if(!visited[i]) dfs(i);
	}
	cout << "Vertex  StartTime   LeaveTime\n";
	for(int i=0; i<n; i++){
		cout << i << "         " << startTimes[i] << "            " << leaveTimes[i] << endl;
	}
	//for(int i=0; i<n; i++){ DlistPrintForward(&graph[i]); }
}

char type[100][100] = {"tree", "back", "forward", "cross"};

int main(){
	read_input(matrix, n);
	//for(int i=0; i<n; i++){DlistPrintForward(&matrix[i]);}
	call_dfs();
	int i, j;
	for(i=0; i<n; i++){
		Node* current = matrix[i].root1;
		Node* colcurr = graph[i].root1;
		for(; current->data != -1; ){
			printf("%d to %d is a %s edge\n", i+1 , current->data+1, type[colcurr->data-1]);
			current = current->next;
			colcurr = colcurr->next;
		}
	}
	write_output(matrix, graph, n); // write a dot file.
	return 0;
}
