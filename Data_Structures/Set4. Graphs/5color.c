// Satvik Choudhary
// 111601021

// useful standard libraries included.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

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
            if(matrix[i][j] == '1') copy[i][j] = 1;
            else copy[i][j] = 0;
        }
    }
}
// roses are red , sky is blue , I am happy and I wish so are you.
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
// finds the vertex which has degree less than equal to 5 and not 0.
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

// mark the alternating colored edges into a new dist matrix with inf implying not connected.
void biconnect(int u, int v){
	// making all the edges as inf.
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++) dist[i][j] = inf;
        dist[i][i] = 0;
    }
    // making all the edges one which have the alternate color propery 
    // i.e. edge between vertices whose colors are color(x) and color(y).
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(copy[i][j]){
                if(color[i] == color[u] && color[j] == color[v] || color[j] == color[u] && color[i] == color[v]){
                    dist[i][j] = 1; dist[j][i] = 1;
                }
            }
        }
    }
}

// not using bfs just to shorten the length of the code. Using Floyd Warshall instead.
int connected(int u, int v){
    for(int k=0; k<n; k++)
        for(int i=0; i<n; i++)
            for(int j=0; j<n; j++)
                dist[i][j] = min(dist[i][j], dist[i][k]+dist[k][j]);
    if(dist[u][v] != inf) return 1;
    return 0;
}

// reversing the colors corresponding to color(u) and color(v) in the connected component
// that starts from u and comprises of alternate edges as explained above biconnect function.
void reverse(int u, int v){
    int col1 = color[u];
    int col2 = color[v];
    for(int i=0; i<n; i++){
        if(dist[u][i] != inf){
            if(color[i] == col1) color[i] = col2;
            else color[i] = col1;
        }
    }
}
// a simple recursion based function which colors the vertex
void color_graph(){
    memset(color, -1, sizeof color); // important when assigning the alterante colored edges.
    int index = lessThanFive(); // vertex with degree less than 5.
    if(index == -1) return;
    int current[100] = {}; // store the edges that we are gonna delete.
    for(int i=0; i<n; i++){
        current[i] = copy[index][i];
        copy[index][i] = 0; copy[i][index] = 0; // deleting the edges of the vertex to be deleted.
    }
    color_graph(); // calling recursively with the edges already deleted.
    for(int i=0; i<n; i++){
    	// reassigning the deleted edges.
        copy[index][i] = current[i]; copy[i][index] = current[i]; 
    }
    int status[5] = {};
    int exist[5], k = 0;
    for(int i=0; i<n; i++){
        if(current[i]){
        	// if the edge that was deleted created an isolated vertex on the other end.
        	if(color[i] == -1) color[i] = 0;
        	status[color[i]] = 1;  // detecting the colors that are used.
        	exist[k++] = i; // required only when all 5 colors are unique.
		} 
    }
    for(int i=0; i<5; i++){
        // finding the missing color when atleast one of the 5 colored vertex is not a neighour.
        if(!status[i]){
            color[index] = i;
            return;
        }
    }
    // choosing all 2 color combinations 
    for(int i=0; i<4; i++){
        for(int j=i+1; j<5; j++){
        	// mark the alternate colored edges.
            biconnect(exist[i], exist[j]);
            // checking connected component.
            if(!connected(exist[i], exist[j])){
            	// if not connected reverse the coloring.
                reverse(exist[i], exist[j]);
                // finally color the vertex which this function is all about the vertex which was
                // deleted.
                color[index] = color[exist[i]];
                return;
            }
        }
    }
}

int main(){
    read_input();
    color_graph();
    write_output();
    return 0;
}
