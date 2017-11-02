// Satvik Choudhary
// 111601021
// 10.64.1.174
// Serial number c
// Question 1
// Assumption - numbers are positive integers including 0 and we can print extra zeros in the front.
// Logic is to check modulo of successive powers of 2 if the modulo is 0 it means a larger power of 2 exists.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Array to store the final binary string.
char a[50];

void binary(int x, int n){
	if(x == 0){ // if only 0 is present.
		a[n] = '0';
		a[n+1] = '\0';
		return;
	}
	//printf("%d  ", (1<<n));
	//printf("%d\n", (x % (1<<n))); 
	if(x % (1<<n) != 0){ // if modulo comes out to be 1.
		a[n] = '1';
	}
	else a[n] = '0'; // if modulo is 0.
	binary(x - x % (1<<n), n+1); // recursive call to the function.
}	

int main(){
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	memset(a, '0', sizeof(a)); // clearing the array out of garbage values.
	int x;
	scanf("%d", &x);
	binary(x, 0);  // first call of the function.
	int size = 18;
	int i = 0;
	for(i = size - 1; i>0; i--){
		printf("%c", a[i]);
	}
	printf("\n");
	return 0;
}
