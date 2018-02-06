#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector <int> vi;
typedef pair <int, int> ii;
#define maxn 105
#define inf (int)1e9

int dist[maxn], parent[maxn];
int n, m, src;

struct Node{
    ii data;
    Node* next;
    Node* prev;
};
struct Dlist{
    Node* root1;
    Node* root2;
    int size;
};
void DlistAddAtBack(Dlist* current, ii val){
    Node* new1 = new Node;
    new1 -> data = val;
    if(current->root1 == NULL){
        current->root1 = new1;
        current->root2 = new1;
        current->size = 1;
    }else{
        current->root2->next = new1;
        current -> root2 = new1;
        current->size++;
    }
}

class Heap{
public:
    static const int capacity = 105;
    ii arr[capacity];
    int size;
    Heap(){
        size = 0;
    }
    void buildHeap(){
        for(int i=n/2; i>=1; i--) minHeapify(i);
    }
    void minHeapify(int p){
        int l = left(p);
        int r = right(p);
        int smallest = p;
        if(l <= size && arr[l] < arr[smallest]) smallest = l;
        if(r <= size && arr[r] < arr[smallest]) smallest = r;
        if(smallest != p){
            swap(arr[smallest], arr[p]);
            minHeapify(smallest);
        }
    }
    ii extractMin(){
        return arr[1];
    }
    void deleteMin(){
        swap(arr[1], arr[size]); size--;
        minHeapify(1);
    }
    void insert(ii val){
        arr[++size] = val;
        int temp = size;
        while(temp != 1){
            if(arr[parent(temp)] > arr[temp]){
                swap(arr[parent(temp)], arr[temp]);
                temp = parent(temp);
            }else break;
        }
    }
    int left(int p){return (p << 1);}
    int right(int p){return (p << 1 | 1);}
    int parent(int p){return (p >> 1);}
    void swap(ii &x, ii &y){
        ii temp = x; x = y; y = temp;
    }
};
class PriorityQueue{
public:
    Heap current;
    void push(ii val){
        if(current.size == current.capacity){
            cerr << "Priority Queue can't accomodate more.\n";
        }else {
            current.insert(val);
        }
    }
    ii top(){
        if(current.size == 0) cout << "Priority Queue is empty brother.\n";
        else return current.extractMin();
    }
    void pop(){
        if(current.size == 0) cout << "Priority Queue is empty brother.\n";
        else current.deleteMin();
    }
    bool empty(){
        return current.size == 0;
    }
};

Dlist graph[maxn];
void take_input(){
    cin >> n >> m;
    int u, v, w;
    for(int i=0; i<m; i++){
        cin >> u >> v >> w; u--; v--;
        DlistAddAtBack(&graph[u], {v, w});
        DlistAddAtBack(&graph[v], {u, w});
    }
    cin >> src; src--;
}
void test_input(){
    for(int i=0; i<n; i++){
        cout << i + 1 << " - ";
        Node* current = graph[i].root1;
        while(current != NULL){
            ii v = current->data;
            cout << v.first + 1<< " ";
            current = current -> next;
        }
        cout << endl;
    }
}
void dijkstra(){
    memset(parent, -1, sizeof parent);
    for(int i=0; i<n; i++) dist[i] = inf;
    dist[src] = 0;
    PriorityQueue pq; pq.push({0, src});
    ii ui; int u;
    while(!pq.empty()){
        ui = pq.top(); pq.pop();
        u = ui.second;
        if(ui.first > dist[u]) continue;
        Node* current = graph[u].root1;
        while(current != NULL){
            ii v = current->data;
            if(dist[v.first] > dist[u] + v.second){
                dist[v.first] = dist[u] + v.second;
                parent[v.first] = u;
                pq.push({dist[v.first], v.first});
            }
            current = current -> next;
        }
    }
    for(int i=0; i<n; i++) {
        cout << i + 1 << " " << dist[i] << "\n";
    }
}
char colors[4][100] = {"black", "red"};
void write_output(){
    char name[100];
    cout << "Enter the name of the output dot file.\n";
    cin >> name;
    FILE *p = fopen(name, "w");
    fprintf(p, "graph Dijkstra{\n");
    for(int i=0; i<n; i++){
        if(i == src)
            fprintf(p, "\t%d[color = yellow, style = filled];\n", i+1);
        else
            fprintf(p, "\t%d;\n", i+1);
        Node* current = graph[i].root1;
        while(current != NULL){
            ii v = current->data;
            if(v.first > i){
                fprintf(p, "\t%d -- %d[color = %s, label = %d];\n", i+1, v.first+1, colors[parent[i] == v.first ||
                        parent[v.first] == i], v.second);
            }
            current = current->next;
        }
    }
    fprintf(p, "}\n");
    fclose(p);
}

int main(){
    take_input();
    test_input();
    dijkstra();
    write_output();
}