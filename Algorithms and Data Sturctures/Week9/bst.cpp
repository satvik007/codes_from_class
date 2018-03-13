#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector <int> vi;

#define inf (int)1e9

struct Node{
    Node *left, *right, *parent;
    int data;
    Node(){}
};

/*
1. Searching for a key (say "found" if key is present in the tree and "not found" otherwise
2. Inserting a key (avoid duplicates)
3. Findminkey
4. InOrderTravelsal
5. PostOrderTraversal
5. FindPreedingKey (should print "no predecessor" if the key given is the minimum otherwise print the preceding key in inorder traversal. )
6. DeleteKey
7. PrintTree
*/

struct trunk{
    trunk *prev;
    string str;
    trunk(trunk *prev, string str) {
        this->prev = prev;
        this->str = str;
    }
};
void show_trunks(trunk *p){
    if (p == nullptr)
        return;
    show_trunks(p->prev);
    std::cout<< p->str ;
}

class BST{
public:
    Node* root;
    BST(){
        root = NULL;
    }
    Node* find(int val){
        Node* temp = root;
        while(true){
            if(temp == NULL) return NULL;
            if(val == temp -> data) return temp;
            if(val > temp -> data){
                temp = temp -> right;
            }else{
                temp = temp -> left;
            }
        }
    }
    Node* insertKey(int val){
        Node* temp = root;
        Node* new1 = new Node;
        new1 -> data = val;
        new1->left = NULL;
        new1->right = NULL;
        if(temp == NULL){
            root = new1;
            return new1;
        }
        while(true){
            if(temp -> data < val){
                if(temp -> right == NULL){
                    temp -> right = new1;
                    new1 -> parent = temp;
                    return new1;
                }else{
                    temp = temp->right;
                }
            }else if(temp -> data > val){
                if(temp -> left == NULL){
                    temp -> left = new1;
                    new1 -> parent = temp;
                    return new1;
                }else{
                    temp = temp -> left;
                }
            }else{
                // delete new1;
                return temp;
            }
        }
    }
    Node* findMinKey(Node* current){
        Node* temp = current;
        if(temp == NULL) return temp;
        while(temp -> left != NULL){
            temp = temp -> left;
        }
        return temp;
    }
    void inOrderTraversal(){
        helperInOrder(root); cout << "\n";
    }
    void helperInOrder(Node *current){
        if(current == NULL) return;
        helperInOrder(current->left);
        cout << current -> data << " ";
        helperInOrder(current->right);
    }
    void postOrderTraversal(){
        helperPostOrder(root); cout << "\n";
    }
    void helperPostOrder(Node* current){
        if(current == NULL) return;
        helperPostOrder(current -> left);
        helperPostOrder(current->right);
        cout << current -> data << " ";
    }
    Node* findPrecedingKey(int val){
        Node* temp = find(val);
        if(temp == NULL) return temp;
        if(temp -> left != NULL){
            temp = temp -> left;
            while(temp -> right != NULL){
                temp = temp -> right;
            }
            return temp;
        }else{
            while(temp != root){
                if(temp -> parent -> left != temp){
                    return temp -> parent;
                }
                temp = temp -> parent;
            }
            return NULL;
        }
    }
    void transplant(Node* u, Node* v){
        if(u->parent == NULL)
            root = v;
        else if(u == u->parent->left)
            u->parent->left = v;
        else u -> parent -> right = v;
        if(v != NULL)
            v->parent = u->parent;
    }
    void deleteKey(int val){
        Node* temp = find(val);
        if(temp == NULL) return;
        if(temp->left == NULL){
            transplant(temp, temp->right);
            free(temp);
        }else if(temp -> right == NULL){
            transplant(temp, temp->left);
        }else{
            Node* y = findMinKey(temp -> right);
            if(y -> parent != temp){
                transplant(y, y->right);
                y->right = temp->right;
                y->right->parent = y;
            }
            transplant(temp, y);
            y->left = temp->left;
            y->left->parent = y;
        }
    }
    void printTree(Node* current, trunk* prev, bool is_left){
        if(current == nullptr) return ;
        string prev_str = "    ";
        trunk *tnk = new trunk(prev , prev_str);
        printTree(current->right , tnk , true);
        // if(prev == nullptr) tnk->str = "---";
        if(!prev) tnk->str = "-->";
        else if(is_left) {
            tnk->str = ".-->";
            prev_str = "   |";
        } else {
            tnk->str = "`-->";
            prev->str = prev_str;
        }
        show_trunks(tnk);
        cout<<current->data<<endl;
        //if(prev!=nullptr) { prev->str = prev_str; }
        if(prev) { prev->str = prev_str; }
        tnk->str = "   |";
        printTree(current->left , tnk , false);
        delete tnk;
    }
    void insertNKeys(){
        cout << "How many keys to insert: ";
        int numKeys; cin >> numKeys;
        for(int i=0; i<numKeys; i++){
            int u; cin >> u;
            insertKey(u);
        }
    }
    void insertRandomNumbers(){
        cout << "How many keys to insert: ";
        int numKeys; cin >> numKeys;
        for(int i=0; i<numKeys; i++){
            insertKey(rand() % 100);
        }
    }
    void printTree(){
        printTree(root, nullptr, false);
    }
};

int main(){
    //ios_base::sync_with_stdio(false);
    //cin.tie(nullptr);
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    BST satvik;
    while(true){
        cout << "Enter 1 to search a key:\n";
        cout << "Enter 2 to insert a key:\n";
        cout << "Enter 3 to find min key:\n";
        cout << "Enter 4 to show in Order Traversal:\n";
        cout << "Enter 5 to show post Order Traversal:\n";
        cout << "Enter 6 to find preceding key:\n";
        cout << "Enter 7 to delete a key:\n";
        cout << "Enter 8 to insert multiple keys:\n";
        cout << "Enter 9 to show the tree:\n";
        cout << "Enter 10 to exit the program:\n";
        cout << "Enter 11 to insert some random numbers:\n";
        int u, v, w;
        cin >> u;
        if(u == 1){
            cout << "Enter the value to be searched: ";
            cin >> v;
            if(satvik.find(v) != NULL) cout << "The value is found.\n";
            else cout << "Not found.\n";
        }else if(u == 2){
            cout << "Enter the key to be inserted: ";
            cin >> v;
            satvik.insertKey(v);
            satvik.printTree();
        }else if(u == 3){
            Node* cur = satvik.findMinKey(satvik.root);
            if(cur == NULL){
                cout << "The BST is empty.\n";
            }else{
                cout << cur -> data << "\n";
            }
        }else if(u == 4){
            satvik.inOrderTraversal();
        }else if(u == 5){
            satvik.postOrderTraversal();
        }else if(u == 6){
            cout << "Enter the current key value: "; cin >> v;
            Node* cur = satvik.findPrecedingKey(v);
            if(cur == NULL){
                cout << "The value you entered doesn't exist in the BST\n or \nIt is the smallest value.\n";
            }else{
                cout << "The preceding key is: " << cur -> data << "\n";
            }
        }else if(u == 7){
            cout << "Enter the value to be deleted: "; cin >> v;
            satvik.deleteKey(v);
            satvik.printTree();
        }else if(u == 8){
            satvik.insertNKeys();
            satvik.printTree();
        }else if(u == 9){
            satvik.printTree();
        }else if(u == 10){
            break;
        }else if(u == 11){
            satvik.insertRandomNumbers();
            satvik.printTree();
        }else {
            cout << "Wrong choice. Try again:\n";
        }
        cout << "\n";
    }
    return 0;
}