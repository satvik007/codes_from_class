// Satvik Choudhary
// 111601021
// Commenting line 49 in graph.c will lead to printing of only edges that
// are part of the hamiltonian cycle.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "graph.h"
#include "dlist.h"
#define inf 10000000

int dist[105][105];
char matrix[105][105];
int visited[105];
Dlist current, dupl;
int n;

// roses are red , sky is blue , I am happy and I wish so are you.
char colors1[100][100] = {"red", "blue", "green", "yellow",
                         "orange", "violet"};

// Simple depth first search algorithm which adds at back of list.
void dfs(int u){
	int i=0;
	for(i=0; i<n; i++){
		if(dist[u][i] && !visited[i]){
			visited[i] = 1;
			DlistAddAtBack(current, i);
			dfs(i);
			return;
		}
	}
}
// Simple depth first search algorithm which adds in front of list.
void dfs2(int u){
	int i = 0;
	for(i=0; i<n; i++){
		if(dist[u][i] && !visited[i]){
			visited[i] = 1;
			DlistAddAtFront(current, i);
			dfs(i);
			return;
		}
	}
}
// apply the 2 dfs algorithms making the longest path saturate.
void explore(){
	dfs(current->root2->data);
	dfs2(current->root1->data);
}
// find the node with the special property that its next is 
// connected to start and it is connected to the end node.
Node findPivot(){
	Node temp = current->root1;
	while(temp != current->root2){
		if(dist[temp->data][current->root2->data] && dist[temp->next->data][current->root1->data]){
			return temp;
		}
		temp = temp->next;
	}
	return temp;
}
// reverse the pointers after finding the pivot
void reversePointers(Node root){
	Node temp;
	while(root != current->root2){
		temp = root->next;
		root->next = root->prev;
		root->prev = temp;
		root = temp;
	}
}
// creating our first complete/non complete hamiltonian cycle.
void cutting(){
	Node temp = findPivot();
	Node temp2 = temp->next;
	temp->next = current->root2;
	reversePointers(temp2);
	temp2->next = current->root1;
	temp->next = current->root2;
	current->root2->next = current->root2->prev;
	current->root2->prev = temp;
	current->root2 = temp2;
}
// finding untraversed vertices.
void backTraverse(){
	int i = 0;
	Node temp = current->root2;
	while(temp != current->root1){
		for(i=0; i<n; i++){
			if(dist[temp->data][i] && !visited[i]){
				current->root1 = temp->next;
				current->root2 = temp;
				return;
			}
		}
		temp = temp->prev;
	}
}
// The driver function for all the important steps.
void goMikeTysonOnTheseEdges(){
	memset(visited, 0, sizeof visited);
	current = DlistCreateNew();
	dupl = DlistCreateNew();
	// the first cycle.
	int start = 0;
	visited[start] = 1;
	DlistAddAtBack(current, start);
	explore();
	cutting();
	DlistPrintForward(current);
	// more cycles coming along.
	while(current -> size != n){
		backTraverse();
		explore();
		cutting();
		DlistPrintForward(current);
	}
}
// color the edges for display using data stored in circular dlist.
void modifyTheGraph(){
	Node temp = current->root1;
	int flag = 1;
	while(temp != current->root1 || flag){
		flag = 0;
		matrix[temp->data][temp->next->data] = matrix[temp->next->data][temp->data] = 0; 
		temp = temp->next;
	}
}

int main(){
	n = read_input(matrix, dist);
	goMikeTysonOnTheseEdges();
	modifyTheGraph();
	write_output(matrix, n, colors1);
	printf("Well the graph is a bit convoluted!\n");
	return 0;
}
