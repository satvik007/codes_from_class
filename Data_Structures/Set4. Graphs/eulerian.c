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

// struct to be used for circular linked list.
struct Node{
    int data;
    struct Node* next;
};
typedef struct Node* Node;

char matrix[100][100]; // matrix to store the adjacency matrix
int dist[100][100]; // matrix on which operations happen.
int n, start; // n - size, start - starting vertex.
Node root, current; // root - starting node, current - temp. node;
int k = 0;

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
    printf("Enter the starting node: ");
    scanf("%d", &start);
    fclose(p);
    // initialising the dist matrix.
    for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            if(matrix[i][j] == '1') dist[i][j] = 1;
            else dist[i][j] = 0;
        }
    }
}
// nice colors though not used here.
char colors[100][100] = {"red", "deepskyblue1", "limegreen",
                         "darkslategray",
                         "darkorange1", "darkorange1", "gold"};

// checks if the graph is eulerian.
int checkEuler(){
    int i, j, k;
    int counter;
    int floyd[100][100];
    int empty[100];
    memset(empty, 0, sizeof(empty));
    // checking if all the vertices have even degree.
    for(i=0; i<n; i++){
        counter = 0;
        for(j=0; j<n; j++){
            if(matrix[i][j] == '1') counter++;
        }
        if(counter % 2)
            return 1;
        if(counter == 0) empty[i] = 1;
    }
    // preparing floyd algorithm matrix.
    for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            if(dist[i][j] == 1) floyd[i][j] = 1;
            else floyd[i][j] = inf;
        }
        floyd[i][i] = 0;
    }
    // applying floyd algorithm.
    for(k=0; k<n; k++)
        for(i=0; i<n; i++)
            for(j=0; j<n; j++)
                floyd[i][j] = min(floyd[i][j], floyd[i][k]+floyd[k][j]);
    // checking connectivity between vertices which are not isolated.
    // Ideally there should not be disconnected components. Isolated vertices are being allowed here.
    for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            if(floyd[i][j] == inf && !(empty[i] || empty[j])){
                return 1;
            }
        }
    }
    return 0;
}
// prints the circular linked list.
void printList(Node root){
    Node curr = root;
    int flag = 1;
    while((root != curr || flag) && root != NULL){
        flag = 0;
        printf("%d ", root->data);
        root = root->next;
    }
    printf("\n");
}
// adds a node to the next and returns its pointer.
Node addNode(Node temp, int i){
    Node new1 = (Node) malloc (sizeof(Node));
    new1->data = i;
    temp->next = new1;
    temp = new1;
    return temp;
}
// on a cycle traverse a node which has unused edges.
Node traverse(){
    Node parent = (Node) malloc (sizeof(Node)); // parent of this new cycle.
    parent->data = current->data; // parent now looks like the current node of which it is a duplicate.
    Node temp = parent;
    int flag = 1;
    int val;
    int flag2 = 0;
    int i = 0;
    // building a circular list by adding elements until parent is again obtained.
    while(temp->data != parent->data || flag){
        flag = 0;
        for(i=0; i<n; i++){
            val = temp->data;
            if(dist[val][i] && i == parent->data) {
                dist[val][parent->data] = 0; // edge is now used.
                dist[parent->data][val] = 0; // ...
                matrix[i][val] = (char)k; // for colors in output.
                matrix[val][i] = (char)k; // ...
                flag2 = 1;
                break;
            }
            if(dist[val][i]) {
                dist[val][i] = 0; // used edge.
                dist[i][val] = 0; // ...
                matrix[i][val] = (char)k; // coloring in output.
                matrix[val][i] = (char)k; // ...
                temp = addNode(temp, i);
                break;
            }
        }
        if(flag2) break;
    }
    temp->next = parent;
    k++;
    return parent;
}
// find Eulerian tour.
void findPath(){
    // node marking the start.
    root = (Node) malloc (sizeof(Node));
    root->next = root;
    root->data = start;
    int val, i, flag = 1;
    Node temp, temp2;
    // runs the following algorithm again and again for built up path till there are unused edges.
    while(flag){
        flag = 0;
        current = root;
        int flag2 = 1;
        // current stands for the vertex that we keep on iterating on checking if unused edges are there.
        while(current != root || flag2){
            flag2 = 0;
            val = current->data;
            for(i=0; i<n; i++){
                // unused edge found.
                if(dist[val][i]){
                    temp2 = current->next;
                    temp = traverse();
                    current->next = temp->next;
                    temp->next = temp2;
                    flag = 1;
                    break;
                }
            }
            //if(flag) break;
            // move on to the next vertex.
            current = current->next;
        }
    }
    printf("Congrats Mr Euler your path exists.\n");
    printList(root);
    printf("Now there will be an output file showing different cycles in different colors.\n");
}
// writing output in a dot file format.
void write_output(){
    char file2[50];
    printf("Enter the name of the output file: ");
    scanf("%s", file2);
    FILE *q;
    q = fopen(file2, "w");
    fprintf(q, "graph BFS{\n");
    for(int i=0; i<n; i++){
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

int main(){
    read_input();
    if(checkEuler()) printf("I am sorry Mr Euler.\n");
    else findPath();
    write_output();
    return 0;
}
