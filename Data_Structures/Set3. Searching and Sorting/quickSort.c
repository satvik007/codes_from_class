/* Satvik Choudhary
 * 111601021
 * quickSort
 */

// Standard C libraries included.
#include <stdio.h>
#include <stdlib.h>

#define inf 1000000000 // Value of the sentinentel. 
#define IN freopen("in.txt", "r", stdin) // Two useful functions which take input from file as if it comes from stdin
#define OUT freopen("out.txt", "w", stdout) // Very helpful in debugging and checking cases. I would recommend this 
// even for checking out programs it will simplify the work of the checkers.
#define swap(a, b) {int temp = a; a = b; b = temp;}

int partitionFunc(int* a, int left, int right, int pivot){
    int lp = left;   // left pointer 
    int rp = right+1; // right pointer
    while(1){
        while(a[++lp] < pivot && lp < right); // move left until left pointer points to element less than pivot.
        while(rp>left && a[--rp] > pivot); // move right until right pointer points to element greater than pivot.
        if(lp >= rp) break; // complete array is divided into two parts.
        else swap(a[lp], a[rp]); // swap the elements pointed to by left and right pointers.
    }
    swap(a[rp], a[left]); // finally swap the pivot value.
    return rp; // returning the new index of the pivot.
}

void quickSort(int* a, int left, int right){
    if(left < right){
        int pivot = a[left];
        int partition = partitionFunc(a, left, right, pivot); // partition the array on two sides of the pivot.
        quickSort(a, left, partition-1); // sort the left part of the partitioned array.
        quickSort(a, partition+1, right); // sort the right part of the partitioned array.
    }
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
    quickSort(a, 0, n-1); // quickSort call for full array sorting.
    for(i=0; i<n; i++){
        printf("%d\n", a[i]);
    }
    return 0;
}
