/*
* Creator : Satvik Choudhary
* Roll No : 111601021
* IMPORTANT : In case of errors please compile with "g++ -std=c++14 bellmanFord.cpp"
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair <int, int> ii;
#define maxn 100000
#define inf (int)1e9

struct Edges{
    int u, v, w;
};

int n, m, src;
Edges edgeList[maxn];
int dist[maxn], parent[maxn], temp[maxn];

void take_input(){
    cin >> n >> m;
    int u, v, w;
    for(int i=0; i<m; i++){
        cin >> u >> v >> w;
        edgeList[i] = {u, v, w};
    }
    cin >> src;
}

void bellmanFord(){
    memset(parent, -1, sizeof parent);
    for(int i=0; i<n; i++) dist[i] = inf;
    dist[src] = 0;
    for(int i=0; i<n-1; i++) {
        bool flag = false;
        for (int j = 0; j < m; j++) {
            if (dist[edgeList[j].u] != inf && dist[edgeList[j].v] > dist[edgeList[j].u] + edgeList[j].w) {
                dist[edgeList[j].v] = dist[edgeList[j].u] + edgeList[j].w;
                parent[edgeList[j].v] = edgeList[j].u;
                flag = true;
            }
        }
        if (!flag) break;
    }
    bool flag = false;
    for(int j=0; j<m; j++){
        if(dist[edgeList[j].u] != inf && dist[edgeList[j].v] > dist[edgeList[j].u] + edgeList[j].w){
            flag = true; break;
        }
    }
    if(flag) cout << "There is a negative cycle in the graph.\n";
    else{
        cout << "The distances are: \n";
        for(int i=0; i<n; i++){
            if(dist[i] != inf)
                cout << i << " -- " << left << setw(10) << dist[i] << "   ";
            else 
                cout << i << " -- " << left << "inf          ";
            int t = i, k = 0;
            while(t != src && parent[t] != -1){
                temp[k++] = t;
                t = parent[t];
            }
            temp[k++] = src;
            if(dist[i] == inf) cout << "no path\n";
            else{
                for(int j=k-1; j>=0; j--) cout << temp[j] << " "; cout << "\n";
            }
        }
    }
}

int main(){
    take_input();
    bellmanFord();
}