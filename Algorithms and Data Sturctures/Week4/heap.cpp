#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class Heap{
public:
    static const int cap = 100;
    int n, arr[cap];
    Heap(int N){
        cout << "Enter " << N << "elements: \n";
        for(int i=1; i<=N; i++){
            cin >> arr[i];
        }
        n = N;
        build_heap(N);
    }
    int parent(int p){
        return p / 2;
    }
    int left(int p) {
        return 2*p;
    }
    int right(int p){
        return 2 * p + 1;
    }
    void build_heap(int N){
        for(int i=N/2; i>=1; i--){
            minHeapify(i);
        }
    }
    void display(){
        for(int i=1; i<=n; i++) cout << arr[i] << " "; cout << endl;
    }
    void minHeapify(int p){
        int l = left(p);
        int r = right(p);
        int smallest = p;
        if(l <= n && arr[l] < arr[smallest]) smallest = l;
        if(r <= n && arr[r] < arr[smallest]) smallest = r;
        if(smallest != p){
            swap(arr[p], arr[smallest]);
            minHeapify(smallest);
        }
    }
    void insert(int data){
        arr[n+1] = data; n++;
        int index = n;
        while(index != 1){
            int p = parent(index);
            if(arr[index] < arr[p]){
                swap(arr[index], arr[p]);
                index = p;
            }else break;
        }
    }
    int delete_min(){
        int temp = arr[1];
        swap(arr[1], arr[n]); n--;
        minHeapify(1);
        return temp;
    }
    int extract_min(){
        return arr[1];
    }
    void heap_sort(){
        int N = n;
        for(int i=1; i<=N; i++){
          cout << delete_min() << " ";
        }
        cout << endl;
        n = N;
        build_heap(N);
        //display();
    }
    void magic_tree(){
        int current = 1;
        int val = 0;
        for(int k = 1; current <= n; k<<=1){
            if(k != 1) val += 24/k;
            cout << string(val, ' ');
            for(int i = current; i<current+k && i <= n; i++){
                cout << setw(48/k) << arr[i];
            }
            cout << "\n\n\n";
            current += k;
        }
    }
};

int main(){
    cout << "Enter the number of elements you would like to enter: ";
    int n; cin >> n;
    Heap sourabh(n);
    while(true){
        cout << "Enter 1 to add another element.\n";
        cout << "Enter 2 to delete the minimum element.\n";
        cout << "Enter 3 to perform heap sort.\n";
        cout << "Enter 4 to display the magic tree.\n";
        cout << "Enter 5 to display the array.\n";
        cout << "Enter 6 to exit.\n";
        int val; cin >> val;
        if(val == 6) break;
        switch(val){
            case 1: cout << "Enter the new number: ";
                int new1;
                cin >> new1;
                sourabh.insert(new1);
                break;
            case 2: cout << "Your wish is granted.\n";
                sourabh.delete_min();
                break;
            case 3: cout << "This wish is granted. Below is the sorted list.\n";
                sourabh.heap_sort();
                break;
            case 4: cout << "We appreciate your patience.\n";
                sourabh.magic_tree();
                break;
            case 5: sourabh.display();
                break;
            default: cout << "What do you really want man.\n";
                break;
        }
    }
    cout << "Have a good day.\n";
    return 0;
}
