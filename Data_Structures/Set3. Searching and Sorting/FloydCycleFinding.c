// Satvik Choudhary
// 111601021
// Floyd algorithm taken from CP3 #Steven Halim

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int first;
char string[200];

int f(int x){
    return x+2;
}

// function int f(int x) is defined earlier
// 1st part: finding k*mu, hare’s speed is 2x tortoise’s
int floydCycleFinding(int x0) {
    // f(x0) is the node next to x0
    int tortoise = f(x0), hare = f(f(x0));
    while (string[tortoise] != string[hare]) {
        tortoise = f(tortoise); hare = f(f(hare));
    }
    // 2nd part: finding mu, hare and tortoise move at the same speed
    int mu = 0; hare = x0;
    while (string[tortoise] != string[hare]) {
        tortoise = f(tortoise); hare = f(hare); mu++;
    }
    printf("Cycle first found at %dth character ", mu);
    // 3rd part: finding lambda, hare moves, tortoise stays
    int lambda = 1; hare = f(tortoise);
    while (string[tortoise] != string[hare]) {
        hare = f(hare); lambda++;
    }
    return (lambda);
}

int main()
{
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    char c;
    printf("Enter your string: ");
    scanf("%[^\n]", string);
    printf("%s\n", string);
    printf("and the cycle length is %d\n", floydCycleFinding(-1));
    return 0;
}
