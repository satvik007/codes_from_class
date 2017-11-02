/* Satvik Choudhary
 * 111601021
 * Bubble sort
 */


// Standard C libraries included.
#include <stdio.h>
#include <stdlib.h>

#define inf 1000000000 // Value of the sentinentel. 
#define IN freopen("in.txt", "r", stdin) // Two useful functions which take input from file as if it comes from stdin
#define OUT freopen("out.txt", "w", stdout) // Very helpful in debugging and checking cases. I would recommend this 
// even for checking out programs it will simplify the work of the checkers.
#define swap(a, b) {int temp = a; a = b; b = temp;}

void bubbleSort(int* a, int n){
    int i = 0;
    int j = 0;
    for(i=0; i<n; i++){ // n*n = max number of operations in worst case when the array is sorted in descending order.
        for(j=0; j<n-1; j++){
            if(a[j] > a[j+1]) swap(a[j], a[j+1]); // swap if left element has greater value than the right.
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
    bubbleSort(a, n); // bubbleSort call for full array sorting.
    for(i=0; i<n; i++){
        printf("%d\n", a[i]);
    }
    return 0;
}
