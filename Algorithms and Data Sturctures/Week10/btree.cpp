#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector <int> vi;

#define t 3

struct Node{
    int n;
    int key[2*t+2];
    Node* c[2*t+2];
    bool leaf;
};

class Btree{
public:
    Node* root;
    int path[100];
    explicit Btree(){
        Node* x = allocateNode();
        x->leaf = true;
        x->n = 0;
        root = x;
    }
    Node* allocateNode(){
        Node* new1 = new Node;
        return new1;
    };
    pair<Node*, int> btreeSearch (Node* x, int k, int index) {
        int i = 1;
        while (i <= x->n and k > x->key[i])
            i++;
        if (i <= x->n and k == x->key[i]) {
            path[index] = i;
            return {x, i};
        }
        else if(x->leaf == true) return {NULL, 0};
        else{
            path[index] = i;
            return btreeSearch(x->c[i], k, index+1);
        }
    }
    void btreeSearchWrapper(int k){
        memset(path, -1, sizeof path);
        auto res = btreeSearch(root, k, 1);
        if(res.first == NULL){
            cout << k << " is not found.\n";
        }else{
            cout << k << " =   root";
            for(int i=1; ; i++){
                if(path[i+1] == -1) {
                    cout << ", index " << path[i] << ".\n";
                    break;
                }else{
                    cout << " -> child " << path[i];
                }
            }
        }
    }
    void btreeSplitChild(Node* x, int i){
        Node* z = allocateNode();
        Node* y = x -> c[i];
        z -> leaf = y -> leaf;
        z -> n = t - 1;
        for (int j=1; j<=t-1; j++)
            z -> key[j] = y -> key[j+t];
        if(!y -> leaf){
            for (int j=1; j<=t; j++)
                z -> c[j] = y -> c[j+t];
        }
        y->n = t-1;
        for(int j = x -> n+1; j >= i+1; j--)
            x->c[j+1] = x->c[j];
        x -> c[i+1] = z;
        for (int j = x -> n; j >= i; j--)
            x->key[j+1] = x->key[j];
        x->key[i] = y->key[t];
        x->n ++;
    }
    void btreeInsert(int k, bool flag){
        auto res = btreeSearch(root, k, 1);
        if(res.first != NULL && flag){
            cout << "This value is already present.\n";
            return;
        }
        Node* r = root;
        if(r -> n == 2 * t - 1){
            Node* s = allocateNode();
            root = s;
            s -> leaf = false;
            s -> n = 0;
            s -> c[1] = r;
            btreeSplitChild(s, 1);
            btreeInsertNonFull(s, k);
        }else{
            btreeInsertNonFull(r, k);
        }
        if(flag)
            printTreeWrapper();
    }
    void btreeInsertNonFull(Node* x, int k){
        int i = x->n;
        if(x -> leaf){
            while(i >= 1 and k < x->key[i]){
                x->key[i+1] = x->key[i];
                i--;
            }
            x -> key[i+1] = k;
            x -> n++;
        }else{
            while(i >= 1 and k < x->key[i])
                i -= 1;
            i += 1;
            if(x -> c[i] -> n == 2 * t - 1){
                btreeSplitChild(x, i);
                if(k > x->key[i])
                    i += 1;
            }
            btreeInsertNonFull(x->c[i], k);
        }
    }
    void insertNRandom(){
        cout << "How many to insert: ";
        int num; cin >> num;
        while(num--){
            int v = rand() % 100;
            cout << v << "\n";
            btreeInsert(v, false);
        }
        printTreeWrapper();
    }
    void printTree(Node* x, string prev_str){
        for(int i=1; i<=x->n; i++){
            if(!x->leaf){
                cout << prev_str << "----.\n";
                printTree(x -> c[i], prev_str + "    |");
            }
            cout << prev_str << x -> key[i] << "\n";
        }
        if(!x->leaf){
            cout << prev_str << "----.\n";
            printTree(x -> c[x->n+1], prev_str + "    |");
        }
    }
    void printTreeWrapper(){
        for(int i=0; i<50; i++) cout << "*"; cout << "\n";
        printTree(root, "|");
        for(int i=0; i<50; i++) cout << "*"; cout << "\n";
    }
};

int main(){
    //ios_base::sync_with_stdio(false);
    //cin.tie(nullptr);
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);

    Btree current;
    bool flag = true;
    while(flag){
        cout << "Enter 1 to insert 1 new key.\n";
        cout << "Enter 2 to search a key.\n";
        cout << "Enter 3 to insert n random keys.\n";
        cout << "Enter 4 to display tree.\n";
        cout << "Enter 5 to exit.\n";
        int ord; cin >> ord;
        int u, v;
        switch(ord){
            case 1: cout << "Enter the new key value: ";
                cin >> u; current.btreeInsert(u, true); break;
            case 2: cout << "Enter the key value to be searched: ";
                cin >> u; current.btreeSearchWrapper(u); break;
            case 3: current.insertNRandom(); break;
            case 4: current.printTreeWrapper(); break;
            case 5: flag = false; break;
            default: cout << "Wrong value entered. Don't worry just try again.\n";
        }
    }
    return 0;
}