#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef long long ll;
ll fibo[100];
        
// fibonacci function 
ll fibonacci(int n){
    if(n == 0) fibo[n] = 0;
    else if(n == 1) fibo[n] = 1;
    else {
        if(fibo[n] != -1);
        else fibo[n] = fibonacci(n-1) + fibonacci(n-2); // assigning then values to the memoization array
    }
    return fibo[n];
}

int main(){
    int n;
    memset(fibo, -1, sizeof(fibo));
    printf("Enter n: ");
    scanf("%d", &n);
    if(n>92) printf("Number is too large for this lang. Try again!\n");// Any number greater than this can't be represented using long long int.
    else {
        fibo[n] = fibonacci(n);
        int i=0;
        for(i=0; i<=n; i++) printf("%d. %lld\n", i, fibo[i]);
    }
    return 0;
}
