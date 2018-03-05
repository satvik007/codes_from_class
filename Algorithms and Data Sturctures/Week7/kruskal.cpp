#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define maxn 500010

struct edges{
    int u, v, w;
    bool operator < (edges x){
        return w < x.w;
    }
};

edges a[maxn];
edges temp[maxn];

int n, m;
int visited[maxn];

void merge(int left, int right){
    int mid = (left + right)/2;
    for(int i = left; i<=right; i++) temp[i] = a[i];
    int u = left;
    int v = mid + 1;
    int k = u;
    while (u != mid+1 && v != right+1){
        if(temp[u] < temp[v]){
            a[k++] = temp[u++];
        }else{
            a[k++] = temp[v++];
        }
    }
    while(u != mid+1){
        a[k++] = temp[u++];
    }
    while(v != right+1){
        a[k++] = temp[v++];
    }
}
void mergeSort(int left, int right){
    if(left < right){
        mergeSort(left, (left+right)/2);
        mergeSort((left+right)/2 + 1, right);
        merge(left, right);
    }
}
class UnionFind{
public:
    int p[maxn], rank[maxn];
    UnionFind(int n){
        for(int i=0; i<n; i++){
            p[i] = i;
            rank[i] = 0;
        }
    }
    bool isSameSet(int i, int j){
        return findSet(i) == findSet(j);
    }
    int findSet(int i){
        int v = i, temp;
        while(i != p[i]) p[i] = p[p[i]], i = p[i];
        while(v != i){
            temp = p[v]; p[v] = i; v = temp;
        }
        return i;
    }
    void unionSet(int i, int j){
        i = findSet(i), j = findSet(j);
        if(i != j){
            if(rank[i] < rank[j]) p[i] = j;
            else{
                p[j] = i;
                if(rank[i] == rank[j]) rank[i]++;
            }
        }
    }
};
void read_input(){
    cin >> n >> m;
    int u, v, w;
    for(int i=0; i<m; i++){
        cin >> u >> v >> w;
        a[i] = {u, v, w};
    }
    mergeSort(0, m-1);
}
void kruskal(){
    memset(visited, 0, sizeof visited);
    UnionFind current(n);
    int mst = 0;
    for(int i=0; i<m; i++){
        if(!current.isSameSet(a[i].u, a[i].v)){
            current.unionSet(a[i].u, a[i].v);
            visited[i] = 1;
            mst += a[i].w;
        }
    }
    cout << "Total weight of the MST is: " << mst << "\n";
}
void write_output(){
    cout << "\nThe edges of the MST are: \n";
    ofstream fout("out.dot");
    fout << "graph Dijkstra{\n";
    for(int i=0; i<m; i++){
        if(visited[i]) {
            cout << a[i].u << " - " << a[i].v << "  --  " << a[i].w << "\n";
            fout << "\t" << a[i].u << " -- " << a[i].v
                 << "[color = red, label = " << a[i].w <<"];\n";
        }else{
            fout << "\t" << a[i].u << " -- " << a[i].v
                 << "[color = black, label = " << a[i].w <<"];\n";
        }
    }
    fout << "}\n";
    cout << "\nOutput dot file is ready.\n";
}

int main(){
    read_input();
    kruskal();
    write_output();
}