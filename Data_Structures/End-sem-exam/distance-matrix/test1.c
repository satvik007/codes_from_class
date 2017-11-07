// Satvik Choudhary
// 111601021
// Question 1

// including standard C libraries.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
typedef long long ll; // I like this typedef.

#define inf 1000000000 // A large value indeed. To be used while applying floyd warshall's algorithm.
#define SIZE 105 // The assumed number of vertices in the graph. If larger graph is tested please change.

// more or less a C++ functionality that I am used to.
int min(int a, int b){
    return (a <= b ? a : b);
}

char matrix[SIZE][SIZE]; // matrix to store the adjacency matrix
int dist[SIZE][SIZE]; // matrix on which operations happen.
int n, flag; // n is the size of graph. flag is used to test if the graph is connected or not.

// This matrix contains distance between the vertices and -1 printed if not connected.
void write_dist_matrix(){
	char out_name[50] = "file-distance.txt";
	FILE *p;
	p = fopen(out_name, "w");
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			if(dist[i][j] == inf){
				fprintf(p, "%d ", (-1));
				flag = 1; 
			}
			else fprintf(p, "%d ", (dist[i][j]));
		}	
		fprintf(p, "\n");
	}	
	fclose(p);
}

// Simply adding up the dist matrix values and dividing by n^2 - n.
void display_average(){
	ll counter = 0;
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			counter += dist[i][j];
		}
	}
	printf("The graph is connected and the average shortest distance between all pairs is %lf.\n", (1.0*counter/(n*n-n)));
}

// floyd warshalls algorithm for all pairs shortest path.
void floyd(){
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			if(dist[i][j] == 0) dist[i][j] = inf;
		}
		dist[i][i] = 0;
	}
	for(int k=0; k<n; k++){
		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++){
				dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
			}
		}
	}
	flag = 0;
	write_dist_matrix();
	if(flag){
		puts("The graph is not connected.");
	}
	else{
		display_average();
	}
}
int main(){
	n = read_input(matrix, dist);
	floyd();	
	//write_ouput(matrix, n);
	return 0;
}
