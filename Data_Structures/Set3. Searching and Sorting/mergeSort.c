/* Satvik Choudhary
 * 111601021
 * Using sentinentals (very large value dummy elements) mergeSort algorithm for sorting in ascending order.
 */


// Standard C libraries included.
#include <stdio.h>
#include <stdlib.h>

#define inf 1000000000 // Value of the sentinentel. 
#define IN freopen("in.txt", "r", stdin) // Two useful functions which take input from file as if it comes from stdin
#define OUT freopen("out.txt", "w", stdout) // Very helpful in debugging and checking cases. I would recommend this 
// even for checking out programs it will simplify the work of the checkers.


int left[10000]; // temporary arrays required when merging two arrays.
int right[10000];

void merge(int* a, int lo, int hi); // function prototype of merge.

// mergeSort function divides the array into two smaller parts and then merges them in O(n);
void mergeSort(int* a, int lo, int hi){ // O(n log(n))
    if(lo < hi){ // More than 1 element in the array
        mergeSort(a, lo, (lo+hi)/2);   // left part sorted.
        mergeSort(a, (lo+hi)/2+1, hi); // right part sorted.
        merge(a, lo, hi); // full array from lo to hi is sorted.
    }
}
void merge(int* a, int lo, int hi){
    int mid = (lo+hi)/2;
    for(int i=lo; i<= mid; i++){ // copying into left 
        left[i-lo] = a[i];
    }
    left[mid-lo+1] = inf; // sentinental in left array
    for(int i=mid+1; i<= hi; i++){ // copying into right
        right[i-mid-1] = a[i];
    }
    right[hi-mid] = inf; // sentinental in right array.
    int x = 0;
    int y = 0;
    for(int i=lo; i<= hi; i++){
        if(left[x] < right[y]){
            a[i] = left[x++];  // left array element is smaller so it is inserted.
        }
        else{
            a[i] = right[y++]; // right array element is smaller so it is inserted.
        }
    } 
    return;
}

int main(){
    //IN;
    //OUT;
    int n;
    printf("Enter the length of array: ");
    scanf("%d", &n);
    int i = 0;
    int a[100000];
    printf("Enter the elements: ");
    for(i=0; i<n; i++){
        scanf("%d", &a[i]);
    }
    mergeSort(a, 0, n-1); // mergeSort call for full array sorting.
    for(i=0; i<n; i++){
        printf("%d\n", a[i]);
    }
    return 0;
}
