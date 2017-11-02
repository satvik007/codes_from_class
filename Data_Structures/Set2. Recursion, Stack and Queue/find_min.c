#include <stdio.h>
#include <stdlib.h>

double min(double*a , int index, int size){
    if(size - index == 1) return a[index]; // if only one element is there to check.
    double current = min(a, index+1, size); // min of all the elements that come after the current element.
    if(a[index] < current) return a[index];
    else return current;
}

int main(){
    int n = 10;
    double a[10];
    int i=0;
    printf("Enter 10 real numbers: ");
    for(i=0; i<n; i++) scanf("%lf", &a[i]);
    printf("\n");
    printf("%lf\n", min(a, 0, 10));
    return 0;   
}
