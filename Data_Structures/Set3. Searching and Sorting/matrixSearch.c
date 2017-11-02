/* Satvik Choudhary
 * 111601021
 * 2D matrix search
 * Complexity (n log (m)) where m = max(row, col) and n = min(row, col);
 */

#include <stdio.h>
#include <stdlib.h>

#define IN freopen("in.txt", "r", stdin) // Treats file input as stdin.
#define OUT freopen("out.txt", "w", stdout) // Treats stdout as file output.
#define swap(a, b) {int temp = a; a = b; b = temp;}

// binary_search for ascending data on a col keeping row constant.
int bs_asc_row(int a[100][100], int row, int len, int target){
    int lo = 0;
    int hi = len-1;
    int mid;
    while(lo <= hi){
        mid = lo + (hi - lo)/2;
        if(target == a[row][mid]) return 1;
        if(a[row][mid] > target) hi = mid-1;
        else lo = mid+1;
    }
    return 0;
}
// binary_search for ascending data on a row keeping col constant.
int bs_asc_col(int a[100][100], int col, int len, int target){
    int lo = 0;
    int hi = len-1;
    int mid;
    while(lo <= hi){
        mid = lo + (hi - lo)/2;
        if(target == a[mid][col]) return 1;
        if(a[mid][col] > target) hi = mid-1;
        else lo = mid+1;
    }
    return 0;
}

// binary_search for descending data on a col keeping row constant.
int bs_des_row(int a[100][100], int row, int len, int target){
    int lo = 0;
    int hi = len-1;
    int mid;
    while(lo <= hi){
        mid = lo + (hi - lo)/2;
        if(target == a[row][mid]) return 1;
        if(a[row][mid] < target) hi = mid-1;
        else lo = mid+1;
    }
    return 0;
}

// binary_search for descending data on a row keeping col constant.
int bs_des_col(int a[100][100], int col, int len, int target){
    int lo = 0;
    int hi = len-1;
    int mid;
    while(lo <= hi){
        mid = lo + (hi - lo)/2;
        if(target == a[mid][col]) return 1;
        if(a[mid][col] < target) hi = mid-1;
        else lo = mid+1;
    }
    return 0;
}

int search_2d(int a[100][100], int n, int m, int target){
    int order = 0; // order = 1 => ascending; order = 0 => descending.
    int i = 0;
    if(a[0][0] < a[0][m-1]) order = 1; // ascending.

    // better to search for every row.
    if(n<=m){
        if(order == 1){
            // calling binary search for every row for ascending data.
            for(i=0; i<n; i++)
                if(bs_asc_row(a, i, m, target)) return 1;
        }
        else{
            // calling binary search for every row for descending data.
            for(i=0; i<n; i++)
                if(bs_des_row(a, i, m, target)) return 1;
        }
    }

        // better to search for every col.
    else{
        // calling binary search for every col for descending data.
        if(order == 1){
            for(i=0; i<m; i++)
                if(bs_asc_col(a, i, n, target)) return 1;
        }
            // calling binary search for every col for descending data.
        else{
            for(i=0; i<m; i++)
                if(bs_des_col(a, i, n, target)) return 1;
        }
    }
    return 0;
}

int main(){
    //IN;
    //OUT;
    int n, m;
    printf("Enter the row len and col len: ");
    scanf("%d%d", &n, &m);
    int i, j;
    int a[100][100];
    printf("Enter the elements: ");
    int notasc = 0;
    int notdes = 0;
    for(i=0; i<n; i++){
        for(j=0; j<m; j++) {
            scanf("%d", &a[i][j]);
            if(i>0){
                if(a[i-1][j] > a[i][j]) notasc = 1; // input not ascending
                if(a[i-1][j] < a[i][j]) notdes = 1; // input not descending
            }
            if(j>0){
                if(a[i][j-1] > a[i][j]) notasc = 1; // input not ascending
                if(a[i][j-1] < a[i][j]) notdes = 1; // input not descending
            }
        }
    }
    // The input is neither ascending and it is neither descending.
    if(notasc && notdes) {
        printf("Input not valid.\n :(");
        return 1;
    }
    int target;
    printf("Enter the target value: ");
    scanf("%d", &target);
    int found = search_2d(a, n, m, target);
    if(found == 1) printf("The value was found. :)\n");
    else printf("The value was not found. :(\n");
    return 0;
}
