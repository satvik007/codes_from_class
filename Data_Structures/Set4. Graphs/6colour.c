// Satvik Choudhary
// 111601021

// useful standard libraries included.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define inf 1000000000

int min(int a, int b){
    return (a <= b ? a : b);
}

char matrix[100][100]; // matrix to store the adjacency matrix
int dist[100][100]; // matrix on which operations happen.
int copy[100][100]; // ...
int n; // size of matrix.
int color[100]; // array to store colors of the vertices.
// reads adjacency matrix from file.
void read_input(){
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
            if(matrix[i][j] == '1') dist[i][j] = 1, copy[i][j] = 1;
            else dist[i][j] = 0, copy[i][j] = 0;
        }
    }
}
// nice colors though not used here.
char colors[100][100] = {"red", "deepskyblue1", "limegreen", "darkslategray",
                         "darkorange1", "darkorange1", "gold"};

// writing output in a dot file format.
void write_output(){
    char file2[50];
    printf("Enter the name of the output file: ");
    scanf("%s", file2);
    FILE *q;
    q = fopen(file2, "w");
    fprintf(q, "graph BFS{\n");
    for(int i=0; i<n; i++){
    	// writing the color of the vertex to be shown.
        fprintf(q, "\t%d [color=%s, style=filled]\n", i, colors[color[i]]);
        int flag = 0;
        for(int j=i+1; j<n; j++){
            if(matrix[i][j] == '1'){ // black edge.
                flag = 1;
                fprintf(q, "\t%d -- %d ;\n", i, j);
            }
                // nice handpicked colors in edges.
            else if(matrix[i][j] != '0'){
                flag = 1;
                fprintf(q, "\t%d -- %d[color = %s];\n", i, j, colors[matrix[i][j]]);
            }
        }
        if(!flag){
            fprintf(q, "\t%d\n", i);
        }
    }
    fprintf(q, "}\n");
    fclose(q);
}
// finds the vertex which has degree less than equal to 5.
int lessThanFive(){
    int counter;
    for(int i=0; i<n; i++){
        counter = 0;
        for(int j=0; j<n; j++){
            if(copy[i][j] == 1) counter++;
        }
        if(counter > 0 && counter <= 5) return i;
    }
    return -1;
}
// a simple recursion based function which colors the vertex 
//which has degree less than equal to 5 with the 6 th missing color.
void color_graph(){
	memset(color, 0, sizeof color);
    int index = lessThanFive();
    if(index == -1) return;
    int current[100] = {}; // store the edges that we are gonna delete.
    for(int i=0; i<n; i++){
        current[i] = copy[index][i]; // storing edge details before deleting.
        copy[index][i] = 0; copy[i][index] = 0; // deleting the edges.
    }
    // recursively calling the function to color the vertices 
    // after this edge has been deleted.
    color_graph();
    for(int i=0; i<n; i++){
        // restoring the deleted edges.
        copy[index][i] = current[i]; copy[i][index] = current[i]; 
    }
    int status[6] = {};
    for(int i=0; i<n; i++){
        if(current[i]) status[color[i]] = 1; // detecting the used colors.
    }
    for(int i=0; i<6; i++){
    	// finding the missing color.
        if(!status[i]){
            color[index] = i;
            break;
        }
    }
}

int main(){
    read_input();
    color_graph();
    write_output();
    return 0;
}
