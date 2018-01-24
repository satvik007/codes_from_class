#include <iostream>
#include <cstdio>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

using namespace std;
typedef long long ll;

#define maxn 105
#define inf (int)1e9

struct Node{
    int data;
    struct Node* next;
    struct Node* prev;
};
struct Dlist{
    Node* root1;
    Node* root2;
    int size;
};

int n, visited[maxn], cnt1, cnt2, root;
Dlist graph[maxn];
int topo[maxn], cycle[maxn];
bool flag;

void DlistAddAtBack(Dlist* current, int val){
    Node* new1 = (Node*) malloc (sizeof (Node*));
    new1->data = val;
    current->size += 1;
    new1->next = NULL;
    new1->prev = NULL;
    if(current->root1 == NULL){
        current->root1 = new1;
        current->root2 = new1;
    }
    else{
        current->root2->next = new1;
        new1->prev = current->root2;
        current->root2 = new1;
    }
}
void take_input(){
    char name[50];
    cout << "Enter the name of the input file: ";
    scanf("%s", name);
    FILE *p = fopen(name, "r");
    fscanf(p, "%d", &n);
    int u;
    for(int i=0; i<n; i++){
        while(true){
            fscanf(p, "%d", &u);
            DlistAddAtBack(&graph[i], u);
            if(u == -1) break;
        }
    }
    fclose(p);
}
bool dfs(int u){
    if(flag) return true;
    visited[u] = 1; cycle[cnt2++] = u;
    for(auto current = graph[u].root1; current->data != -1; current = current -> next){
        int v = current->data;
        if(!visited[v]){
            if(dfs(v)) return true;
        }
        if(visited[v] == 1) {
            flag = true; root = v;
            cycle[cnt2++] = v;
            return true;
        }
    }
    visited[u] = 2;
    topo[cnt1++] = u;
    cnt2--;
    return false;
}
void call_dfs(){
    memset(visited, 0, sizeof visited);
    cnt1 = cnt2 = 0; flag = false;
    for(int i=0; i<n; i++){
        if(!visited[i]) dfs(i);
        if(flag) break;
    }
    if(flag) {
        cout << "The graph is not a DAG.\n";
        int k=0;
        for(k=0; k<cnt2; k++) if(cycle[k] == root) break;
        for(; k< cnt2; k++) cout << cycle[k] << " "; cout << endl;
    }else{
        cout << "The topological order:\n";
        for(int i=cnt1-1; i>=0; i--) cout << topo[i] << " "; cout << endl;
    }
}

void test_input(){
    cout << n << endl;
    for(int i=0; i<n; i++){
        for(auto current = graph[i].root1; current->data != -1; current = current-> next){
            cout << current->data << " ";
        }
        cout << endl;
    }
}

void print_output(){
    cout << "Enter the name of the output dot file: ";
    char name[50];
    cin >> name;
    FILE *p = fopen(name, "w");
    fprintf(p, "digraph BFS{\n");
    //test_input();
    for(int i=0; i<n; i++){
        fprintf(p, "\t%d;\n", i);
        Node* current = graph[i].root1;
        while(current != NULL && current->data != -1){
            fprintf(p, "\t%d -> %d;\n", i, current->data);
            current = current->next;
        }
    }
    fprintf(p, "}\n");
    fclose(p);
}

int main(){
    //ios_base::sync_with_stdio(false);
    //cin.tie(nullptr);
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    take_input();
    test_input();
    call_dfs();
    print_output();
    return 0;
}