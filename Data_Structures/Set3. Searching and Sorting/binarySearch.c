// IMPORTANT : COMPILE WITH THE FLAGS -lm SO THAT math.h library works.
// Satvik Choudhary
// 111601021

#include <stdio.h>
#include <string.h>
#include <math.h>

#define IN() freopen("in.txt", "r", stdin)
#define OUT() freopen("out.txt", "w", stdout)
#define epsilon 1e-6

int binary_search(double a[], int len, double target){
    int lo = 0;
    int hi = len-1;
    int mid = lo + (hi - lo)/2;
    while(lo < hi){
        mid = lo + (hi - lo)/2;
        if(fabs(target - a[mid] ) < epsilon){
            return 1;
        }
        else if(a[mid]+epsilon > target ) {
            hi = mid-1;
        }
        else{
            lo = mid+1;
        }
    }
    if(fabs(a[lo]-target) < epsilon ) return 1;
    else return 0;
}

int main(){
    //IN();
    //OUT();
    printf("Enter the length of the array: ");
    int n;
    int i=0;
    scanf("%d", &n);
    double a[100];
    printf("Enter the values: ");
    for(i=0; i<n; i++){
        scanf("%lf", &a[i]);
    }
    int flag2 = 0;
    for(i=0; i<n-1; i++) {
        if(a[i] > a[i+1]) flag2 = 1;
    }
    if(flag2 == 1){
        printf("Numbers not sorted: \n");
        return 0;
    }
    double target;
    printf("Enter the targeted value: ");
    scanf("%lf", &target);
    int flag = 0;
    flag = binary_search(a, n, target);
    if(flag == 1) printf("Yes number found!\n");
    else printf("NO the number was not found!\n");

}

