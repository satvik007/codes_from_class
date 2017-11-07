// Satvik Choudhary
// 111601021
// Question 2
// The entire logic is in how dfs is implemented.
// including the standard c libraries.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
typedef long long ll; // my favourite typedef.

#define inf 1000000000 // large value can be used sometimes.
#define SIZE 105 // Assumed size of the graph. Should be increased if larger graphs are intended.

// a C++ functionality that I am used to.
int min(int a, int b){
    return (a <= b ? a : b);
}

char matrix[SIZE][SIZE], out_name[50]; // matrix to store the adjacency matrix
int graph[SIZE][SIZE]; // matrix on which operations happen.
int n, flag; // n is the size of the matrix.
int colors[SIZE], visited[SIZE]; // colors is the color assigned to the respective vertex in a 2 coloring ans.
// visited is used to keep track of 2 distance neighbours.
int visited2[SIZE]; // visited2 is used to mark the ones with depth 1 in a dfs tree but does not marks depth 2 since 
// what may be depth 2 in one case can also be depth 1 if the dfs tree was formed in a different manner and can prevent some neighbours to be listed.

// find the vertex with max number of edges. Also this vertex should not be colored.
int max_neighbour_vertex(){
    int counter, ver=0, max1=0;
    for(int i=0; i<n; i++){
        counter = 0;
        if(colors[i] != -1) continue; 
        for(int j=0; j<n; j++){
            if(graph[i][j] == 1) counter++;
        }
        if(counter > max1) max1 = counter, ver = i;
    }
    //printf("%d\n", ver);
    if(max1 == 0) return -1;
    else return ver;
}

// A dfs which marks the ones at depth 1 a dfs tree but does not mark depth 2
// since what may be depth 2 in one case can also be depth 1 if the dfs tree was formed in a different manner and
// can prevent some neighbours to be marked in visited.

void dfs(int u, int depth){
	if(depth < 2) visited2[u] = 1; // only depth 1 and depth 0 are marked to prevent looping. Depth 2 vertices are anyways not allowed to carry on more branching.
	visited[u] = 1; // important neighbours are marked to be used when coloring.
	if(depth == 2) return; // stopping tree growth at depth 2. Global warming can't be prevented anyways. Just meant for
	// fun. Not to be taken seriously.
	for(int i=0; i<n; i++){
		if(graph[u][i] && !visited2[i]){
			dfs(i, depth+1);
		}	
	}	
}

// yay lets start coloring.
void lets_start_coloring(){
	memset(colors, -1, sizeof colors); // important step. The graph should be initially 
	int current, i;
	int col_left[SIZE]; // To be used for checking unused colors while coloring.
	while((current = max_neighbour_vertex()) != -1){
		memset(visited, 0, sizeof visited); // making everything unvisited.
		memset(visited2, 0, sizeof visited2);
		dfs(current, 0); // call dfs with depth 0. Should step as soon as it hits depth 2 for all 
		//possible variants of dfs tree.
		memset(col_left, 0, sizeof col_left);
		for(i=0; i<n; i++){
			if(visited[i] && colors[i] != -1){
				col_left[colors[i]] = 1;
			}
		}
		for(i=0; i<n; i++){
			if(col_left[i] == 0) break;
		}
		colors[current] = i; // using the missing color.
	}
}

int main(){
	n = read_input(matrix, graph, out_name);
	lets_start_coloring();
	/*for(int i=0; i<n; i++){
		printf("%d %d\n",i, colors[i]); 
	}
	puts("");*/
	// The above part can be uncommented to check the exact color number for every vertex.
	int max1 = 0;
	for(int i=0; i<n; i++){
		if(max1 < colors[i]) max1 = colors[i];
	}
	printf("The maximum number of colors used is: %d.\n", max1+1);
	write_output(matrix, n, out_name, colors);
	return 0;
}
