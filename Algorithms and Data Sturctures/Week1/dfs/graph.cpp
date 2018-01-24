// Satvik Choudhary
// 111601021

#include <bits/stdc++.h>
#include <string.h>
#include "graph.h"
#include "dlist.h"
// tree (red)   back (black)       forward(blue)         cross(green)
char colors[100][100] = {"red", "black", "blue", "green"};

void read_input(Dlist matrix[maxn], int &n){
    FILE *p;
    char filename[50];
    printf("Enter the name of the file: ");
    scanf("%s", filename);
    p = fopen(filename, "r");
    fscanf(p, "%d\n", &n);
    int i, j;
    int u;
    for(i=0; i<n; i++){
    	for(j =0; ; j++){
    		fscanf(p, "%d", &u); 
            // Add the read element in an adjacency list with -1 
            // as the end of the list.
            DlistAddAtBack(&matrix[i], (u-1 >= -1) ? u - 1 : -1);
    		if(u == -1) break;
    	}
    }
    fclose(p);
}

void write_output(Dlist matrix[maxn], Dlist graph[maxn], const int n){
	int i, j;
    char file2[50];
    printf("Enter the name of the output dot file: ");
    scanf("%s", file2);
    FILE *q;
    q = fopen(file2, "w");
    fprintf(q, "digraph BFS{\n");
    for(i=0; i<n; i++){
        Node* current = matrix[i].root1;
        Node* colcurr = graph[i].root1;
    	while(current != NULL && current->data != -1){
    	   fprintf(q, "\t%d -> %d [color=%s];\n", i+1, current->data+1, colors[colcurr->data - 1]);
    	   current = current->next;
           colcurr = colcurr->next;
        }	
    }	
    fprintf(q, "}\n");
    fclose(q);
    std::cout << "The colors are as follows:\n";
    std::cout << "\033[1;41mtree edge\033[0m\n";
    std::cout << "\033[1;40mback edge\033[0m\n";
    std::cout << "\033[1;44mforward edge\033[0m\n";
    std::cout << "\033[1;42mcross edge\033[0m\n";
}