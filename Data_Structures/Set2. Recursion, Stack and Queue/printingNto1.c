// Its too simple and there is nothing worth commenting.
#include <stdio.h>
#include <stdlib.h>

void print(int n){
    if(n<0) return;
    printf("%d\n", n);
    print(n-1);
    return;
}
int main(){
    int n;
    printf("Enter n: ");
    scanf("%d", &n);
    print(n);
    return 0;
}
