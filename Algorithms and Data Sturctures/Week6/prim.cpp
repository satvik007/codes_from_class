#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector <int> vi;
typedef pair <int, int> ii;
#define maxn 105
#define inf (int)1e9

int cost[maxn], parent[maxn];
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
    int location[capacity];
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
        swap(arr[1], arr[size]);
        location[arr[size].second] = inf;
        size--;
        minHeapify(1);
    }
    void insert(ii val){
        arr[++size] = val;
        location[val.second] = size;
        siftUp(size);
    }
    void siftUp(int p){
        int temp = p;
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
        int tem = location[x.second];
        location[x.second] = location[y.second];
        location[y.second] = tem;
    }
};

class PriorityQueue{
public:
    static const int capacity = 105;
    Heap current;
    PriorityQueue () {
        for(int i=0; i<current.capacity; i++){
            current.location[i] = inf;
        }
    }
    void push(ii val){
        if(current.size == current.capacity){
            cerr << "Priority Queue can't accomodate more.\n";
        }else {
            current.insert(val);
        }
    }
    ii top(){
        if(current.size == 0) cout << "Priority Queue is empty.\n";
        else return current.extractMin();
    }
    void pop(){
        if(current.size == 0) cout << "Priority Queue is empty.\n";
        else current.deleteMin();
    }
    bool empty(){
        return current.size == 0;
    }
    void decreaseKey(ii val){
        int loc = current.location[val.second];
        if(current.arr[loc].first > val.first){
            current.arr[loc].first = val.first;
            current.siftUp(loc);
        }
    }
};

Dlist graph[maxn];
void take_input(){
    cin >> n >> m;
    int u, v, w;
    for(int i=0; i<m; i++){
        cin >> u >> v >> w;// u--; v--;
        DlistAddAtBack(&graph[u], {v, w});
        DlistAddAtBack(&graph[v], {u, w});
    }
    //cin >> src;// src--;
}
void test_input(){
	cout << "The input adjacency list: \n";
    for(int i=0; i<n; i++){
        cout << i << " - ";
        Node* current = graph[i].root1;
        while(current != NULL){
            ii v = current->data;
            cout << v.first<< " ";
            current = current -> next;
        }
        cout << endl;
    }
}

char colors[4][100] = {"black", "red"};
void write_output(){
    char name[100] = {"out.dot"};
    FILE *p = fopen(name, "w");
    fprintf(p, "graph Dijkstra{\n");
    for(int i=0; i<n; i++){
        if(i == src)
            fprintf(p, "\t%d[color = yellow, style = filled];\n", i);
        else
            fprintf(p, "\t%d;\n", i);
        Node* current = graph[i].root1;
        while(current != NULL){
            ii v = current->data;
            if(v.first > i){
                fprintf(p, "\t%d -- %d[color = %s, label = %d];\n", i, v.first, colors[parent[i] == v.first ||
                                                                                       parent[v.first] == i], v.second);
            }
            current = current->next;
        }
    }
    fprintf(p, "}\n");
    fclose(p);

    cout << endl << "The edges of the MST are: \n";
    for(int i=0; i<n; i++){
    	if(i != src){
    		cout << min(i, parent[i]) << " - " << max(parent[i], i) << "   -    " << cost[i] << endl;
    	}
    }
    cout << "\nThe output dot file is ready.\n";
}

void prims_algorithm(){
	src = 0;
	memset(parent, -1, sizeof parent);
	for(int i=0; i<n; i++) 
		cost[i] = inf;
	cost[src] = 0;
	PriorityQueue pq; pq.push({0, src});
	for(int i=0; i<n; i++){
		if(i != src)
			pq.push({inf, i});
	}
	ii v, ui;
	bitset <maxn> visited;
	int mstwt = 0;
	while(!pq.empty()){
		ui = pq.top(); pq.pop();
		if(visited[ui.second]) continue;
		mstwt += ui.first;
		visited[ui.second] = true;
		Node* current = graph[ui.second].root1;
		while(current != NULL){
			v = current -> data;
			if(!visited[v.first] && cost[v.first] > v.second){
				cost[v.first] = v.second;
				parent[v.first] = ui.second;
				pq.decreaseKey({v.second, v.first});
			}
			current = current -> next;
		}
	}
	cout << "\nThe weight of the MST is " << mstwt << ".\n";
}

int main(){
    take_input();
    test_input();
    prims_algorithm();
    write_output();
}