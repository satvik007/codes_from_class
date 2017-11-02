/* Satvik Choudhary
 * 111601021
 * Search in a rotated array of numbers.
 */

#include <stdio.h>

#define IN freopen("in.txt", "r", stdin) // Treats file input as stdin.
#define OUT freopen("out.txt", "w", stdout) // Treats stdout as file output.

// finds the point where 
int findStart(int *a, int len){
    int lo = 0;
    int hi = len-1;
    if(a[lo] < a[hi]) return 0;
    int mid;
    while(lo <= hi){
        mid = lo + (hi - lo)/2;
        if(a[mid-1] > a[mid]) return mid;
        if(a[mid] > a[hi]) lo = mid+1;
        else hi = mid;
    }
    return 0;
}

int binary_search(int *a, int lo, int hi, int target){
    if(lo < 0) return -1;
    int mid;
    while(lo <= hi){
        mid = lo + (hi - lo)/2;
        if(target == a[mid]) return mid;
        if(a[mid] > target) hi = mid-1;
        else lo = mid+1;
    }
    return -1;
}

int findRotate(int *a, int len, int target){
    int start = findStart(a, len);
    int res1 = binary_search(a, 0, start-1, target);
    int res2 = binary_search(a, start, len-1, target);
    if(res1 < 0 && res2 < 0) return -1;
    else if(res1 >= 0) return res1;
    else return res2;
}

int main(){
    IN;
    OUT;
    int n, i;
    printf("Enter the len of array: ");
    scanf("%d", &n);
    int a[1000];
    printf("Enter the elements: ");
    for(i=0; i<n; i++){
        scanf("%d", &a[i]);
    }
    int target;
    printf("Enter the target: ");
    scanf("%d", &target);
    int found = findRotate(a, n, target);
    if(found == -1) printf("The target could not be found. :(\n");
    else printf("The target was found and its index is %d. :)\n", found);

}
