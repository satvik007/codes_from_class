#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector <int> vi;

#define t 3

struct Node {
    int n;
    int key[2 * t + 2];
    Node *c[2 * t + 2];
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
        if(res.first != NULL){
            if(flag)
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
            btreePrintTreeWrapper();
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
        btreePrintTreeWrapper();
    }
    void btreePrintTree(Node* x, string prev_str){
        if(x->leaf){
            cout << prev_str << "{";
            for(int i=1; i<=x->n; i++) cout << x->key[i] << " "; cout << "}\n";
        } else{
            for(int i=1; i<=x->n; i++){
                cout << prev_str << "----.\n";
                btreePrintTree(x -> c[i], prev_str + "    |");
                cout << prev_str << x -> key[i] << "\n";
            }
            cout << prev_str << "----.\n";
            btreePrintTree(x -> c[x->n+1], prev_str + "    |");
        }
    }
    void btreePrintTreeWrapper(){
        for(int i=0; i<50; i++) cout << "*"; cout << "\n";
        btreePrintTree(root, "|");
        for(int i=0; i<50; i++) cout << "*"; cout << "\n";
        flush(cout);
    }
    void btreeDeleteWrapper(int val, bool flag){
        auto res = btreeSearch(root, val, 1);
        if(res.first == NULL){
            if(flag) cout << "The value is not present.\n";
            return;
        }
        btreeDelete(root, val);
        if(flag)
            btreePrintTreeWrapper();
    }
    int btreePredHelper(Node* x){
        if(x->leaf) return x -> key[x->n];
        return btreePredHelper(x->c[x->n+1]);
    }
    int btreeSuccHelper(Node* x){
        if(x->leaf) return x -> key[1];
        return btreeSuccHelper(x->c[1]);
    }
    void btreeMergeChild(Node* x, int index){
        Node *c1 = x->c[index], *c2 = x->c[index+1];
        c1->key[c1->n+1] = x->key[index];
        for(int i=c1->n+2; i <= (c1->n+1+c2->n); i++){
            c1 -> key[i] = c2->key[i - c1->n - 1];
            c1 -> c[i] = c2->c[i - c1->n - 1];
        }
        c1 -> n += c2 -> n + 1;
        c1 -> c[c1->n+1] = c2 -> c[c2->n+1];

        for(int i=index; i < x->n; i++){
            x->key[i] = x->key[i+1];
            x->c[i+1] = x->c[i+2];
        }
        x->n--;
        if(x == root && x->n == 0) root = c1;
        delete c2;
    }
    void btreeDelete(Node* x, int k){
        if(x->leaf){
            for(int i=1; i <= x->n; i++){
                if(x->key[i] == k){
                    for(int j=i; j<x->n; j++){
                        x->key[j] = x->key[j+1];
                    }
                    x->n --;
                    return;
                }
            }
        }
        for(int i=1; i<= x->n; i++){
            if(x -> key[i] == k){
                if(x->c[i]->n >= t){
                    int pred = btreePredHelper(x->c[i]);
                    btreeDelete(x->c[i], pred);
                    x->key[i] = pred;
                }else if(x->c[i+1]->n >= t){
                    int succ = btreeSuccHelper(x->c[i+1]);
                    btreeDelete(x->c[i+1], succ);
                    x->key[i] = succ;
                }else{
                    btreeMergeChild(x, i);
                    btreeDelete(x->c[i], k);
                }
                return;
            }
        }
        int ind = 0;
        for(int i=1; i <= x->n; i++){
            if(x->key[i] > k){
                ind = i;
                break;
            }
        }
        if(!ind) ind = x->n + 1;
        if(x->c[ind]->n >= t)
            btreeDelete(x->c[ind], k);
        else{
            if(ind != 1 && x->c[ind-1]->n >= t){
                btreeMoveRight(x, ind);
                btreeDelete(x->c[ind], k);
            }else if(ind != x->n+1 && x->c[ind+1]->n >= t){
                btreeMoveLeft(x, ind);
                btreeDelete(x->c[ind], k);
            }else{
                btreeMerge(x, ind);
                btreeDelete(x->c[max(1, ind-1)], k);
            }
        }
    }
    void btreeMoveRight(Node* x, int ind){
        Node *c1 = x->c[ind-1], *c2 = x->c[ind];
        c2->c[c2->n+2] = c2->c[c2->n+1];
        for(int i=c2->n; i>=1; i--){
            c2->c[i+1] = c2->c[i];
            c2->key[i+1] = c2->key[i];
        }
        c2->key[1] = x->key[ind-1];
        c2->c[1] = c1->c[c1->n+1];
        x->key[ind-1] = c1->key[c1->n];
        c1->n--; c2->n++;
    }
    void btreeMoveLeft(Node* x, int ind){
        Node *c1 = x->c[ind], *c2 = x->c[ind+1];
        c1->key[c1->n+1] = x->key[ind];
        c1->c[c1->n+2] = c2->c[1];
        c1->n++;
        x->key[ind] = c2->key[1];
        for(int i=1; i<c2->n; i++){
            c2->key[i] = c2->key[i+1];
            c2->c[i] = c2->c[i+1];
        }
        c2->c[c2->n] = c2->c[c2->n+1];
        c2->n--;
    }
    void btreeMerge(Node* x, int ind) {
        if (ind == 1)
            btreeMergeChild(x, 1);
        else
            btreeMergeChild(x, ind - 1);
    }
    void btreeDeleteAll(){
        while(root->n){
            int v = rand() % 100;
            cout << v << " ";
            flush(cout);
            btreeDeleteWrapper(v, true);
        }
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
        cout << "Enter 5 to delete a key.\n";
        cout << "Enter 6 to exit.\n";

        int ord; cin >> ord;
        int u, v;
        switch(ord){
            case 1: cout << "Enter the new key value: ";
                cin >> u; current.btreeInsert(u, true); break;
            case 2: cout << "Enter the key value to be searched: ";
                cin >> u; current.btreeSearchWrapper(u); break;
            case 3: current.insertNRandom(); break;
            case 4: current.btreePrintTreeWrapper(); break;
            case 5: cout << "Enter the key to be deleted: ";
                cin >> u; current.btreeDeleteWrapper(u, true); break;
            case 6: flag = false; break;
            default: cout << "Wrong value entered. Don't worry just try again.\n";
        }
    }
    return 0;
}