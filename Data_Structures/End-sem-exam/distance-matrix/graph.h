#ifndef GRAPH_H
#define GRAPH_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 105 // Assumed number of vertices in the test graph.

int read_input(char matrix[][SIZE], int dist[][SIZE]); // reading input from the adj matrix file.
void write_output(char matrix[][SIZE], int n); // not used in this program.

#endif
