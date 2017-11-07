#ifndef GRAPH_H
#define GRAPH_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 105

 
int read_input(char matrix[][SIZE], int dist[][SIZE], char out_name[50]);
void write_output(char matrix[][SIZE], int n, char out_name[50], int colors[SIZE]);

#endif
