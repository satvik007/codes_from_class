// Satvik Choudhary
// 111601021

// Added the required libraries.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//#include "satvik.h"

// Taking input from file as if it comes from stdin
#define IN(file) freopen(file".txt", "r", stdin)
#define OUT(file) freopen(file".dot", "w", stdout)

int main(){
	char file1[50];
	char file2[50];
	printf("Enter the name of the input file: ");
	scanf("%s", file1);
	printf("Enter the name of the output file: ");
	scanf("%s", file2);
	FILE *p, *q;
	char name[50];
	char type[50];
	p = fopen(file1, "r");
	q = fopen(file2, "w");
	fscanf(p, "%s\n%s\n", name, type);
	int n;
	fscanf(p, "%d\n", &n);
	char matrix[100][100];
	int i = 0;
	for(i=0; i<n; i++){
		fscanf(p, "%s\n", matrix[i]);
		//printf("%s\n", matrix[i]);
	}
	
	int j = 0;
	fprintf(q, "graph %s{\n", name);
	for(i=0; i<n; i++){
		int flag = 0;
		for(j=i+1; j<n; j++){
			if(matrix[i][j] == '1'){
				flag = 1;
				fprintf(q, "\t%d -- %d ;\n", i, j);
			}
		}
		// Lone vertex
		if(!flag){
			fprintf(q, "\t%d\n", i);
		}
	}
	fprintf(q, "}\n");
	fclose(p); fclose(q);
	return 0;
}
