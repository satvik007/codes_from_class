// Satvik Choudhary
// 111601021

// Cannot live without including these libraries.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

// nice mouse-picked colors.
char color_name[100][100] = {
"red", "darkorange", "blueviolet", "blue", "chartreuse1", "darkslategray", "yellow4",
"deeppink1", "saddlebrown", "floralwhite", "green4", "pink1", "powderblue", "darkcyan", "yellow", "violetred4",
 "steelblue2", "cyan"}; 

// Lets read the input matrix.
int read_input(char matrix[][SIZE], int dist[][SIZE], char out_name[50]){
    int n;
    FILE *p;
    
    printf("Enter the name of the file: ");
    scanf("%s", out_name);
    p = fopen(out_name, "r");
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

// The output is important but mostly another standard procedure.
void write_output(char matrix[][SIZE], int n, char out_name[50], int colors[SIZE]){
	int i, j;
	char file2[50];
	strcpy(file2, out_name);
	strcpy(file2 + strlen(file2)-4, "-coloured.dot");
    FILE *q;
    q = fopen(file2, "w");
    fprintf(q, "graph BFS{\n");
    for(i=0; i<n; i++){
        // writing the color of the vertex to be shown.
        fprintf(q, "\t%d[color = %s, style=filled];\n", i, color_name[colors[i]]);
        int flag = 0;
        for(j=i+1; j<n; j++){
            if(matrix[i][j] == '1'){
            	fprintf(q, "\t%d -- %d;\n", i, j);
            }
        }
        if(!flag){
            fprintf(q, "\t%d\n", i);
        }
    }
    fprintf(q, "}\n");
    fclose(q);
}
