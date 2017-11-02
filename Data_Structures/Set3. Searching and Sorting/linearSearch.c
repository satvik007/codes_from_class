// IMPORTANT : COMPILE WITH THE FLAGS -lm SO THAT math.h library works.
// Satvik Choudhary
// 111601021

#include <stdio.h>
#include <string.h>
#include <math.h>

#define IN() freopen("in.txt", "r", stdin)
#define OUT() freopen("out.txt", "w", stdout)
#define epsilon 1e-9

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
    double target;
    printf("Enter the targeted value: ");
    scanf("%lf", &target);
    int flag = 0;
    for(i=0; i<n; i++){
        if(fabs(a[i] - target) <= epsilon) flag = 1;
    }
    if(flag == 1) printf("Yes number found!\n");
    else printf("NO the number was not found!\n");
    
}

