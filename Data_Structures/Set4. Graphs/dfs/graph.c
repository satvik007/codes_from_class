// Satvik Choudhary
// 111601021

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"


int read_input(char matrix[][105], int dist[][105]){
    int n;
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
    int i, j;
    for(i=0; i<n; i++) fscanf(p, "%s\n", matrix[i]);
    fclose(p);
    // initialising the dist matrix.
    for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            dist[i][j] = matrix[i][j] - '0';
        }
    }
    return n;
}

void write_output(char matrix[][105], int n){
	int i, j;
    char file2[50];
    printf("Enter the name of the output file: ");
    scanf("%s", file2);
    FILE *q;
    q = fopen(file2, "w");
    fprintf(q, "graph BFS{\n");
    for(i=0; i<n; i++){
        // writing the color of the vertex to be shown.
        fprintf(q, "\t%d;\n", i);
        int flag = 0;
        for(j=i+1; j<n; j++){
            if(matrix[i][j] == '2'){
            	fprintf(q, "\t%d -- %d [color=red];\n", i, j);
            }
            else if(matrix[i][j] == '1'){
            	fprintf(q, "\t%d -- %d [color=black];\n", i, j);
            }
        }
        if(!flag){
            fprintf(q, "\t%d\n", i);
        }
    }
    fprintf(q, "}\n");
    fclose(q);
}
