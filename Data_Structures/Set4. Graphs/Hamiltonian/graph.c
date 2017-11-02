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
            if(matrix[i][j] == '1') dist[i][j] = 1;
            else dist[i][j] = 0;
        }
    }
    return n;
}

void write_output(char matrix[][105], int n, char colors1[][100]){
    char file2[50];
    printf("Enter the name of the output file: ");
    scanf("%s", file2);
    FILE *q;
    q = fopen(file2, "w");
    fprintf(q, "graph BFS{\n");
    for(int i=0; i<n; i++){
        // writing the color of the vertex to be shown.
        //fprintf(q, "\t%d [color=%s, style=filled]\n", i, colors[color[i]]);
        int flag = 0;
        for(int j=i+1; j<n; j++){
            if(matrix[i][j] == '1'){ // black edge.
                flag = 1;
                fprintf(q, "\t%d -- %d ;\n", i, j);
            }
                // nice handpicked colors in edges.
            else if(matrix[i][j] != '0'){
                flag = 1;
                fprintf(q, "\t%d -- %d[color = %s];\n", i, j, colors1[matrix[i][j]]);
            }
        }
        if(!flag){
            fprintf(q, "\t%d\n", i);
        }
    }
    fprintf(q, "}\n");
    fclose(q);
}
