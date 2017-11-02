#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int palindrome(char* a, int i, int size){
    if(i>size/2) return 1; // i safely crossed the middle of the array implies a palindrome.
    if(a[i] != a[size - i -1]) return 0; // sure that the number is not a palindrome.
    else return palindrome(a, i+1, size); // not sure bit will check further in the array.
}

int main(){
    char a[100];
    printf("Enter the string: ");
    scanf("%[^\n]", a);
    if(palindrome(a, 0, strlen(a))) printf("The string is a palindrome.\n");
    else printf("The string is not a palindrome.\n");
    return 0;
}
    
