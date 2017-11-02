// Satvik Choudhary
// 111601021

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char a[50];
char b[50];

int main(){
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	int i = 0;
	printf("Enter the strings: ");
	scanf(" %s", a);
	scanf(" %s", b);
	int n = strlen(a);
	int m = strlen(b);
	if(m != n){
		printf("Not a rotation as sizes not equal.\n");
		return 1;
	}
	// concatenating a at the end of itself.
	// If a rotation exists b will be found in 2a.
	for(int i =0 ;i<n; i++){
		a[n+i] = a[i];
	}
	char* p = strstr(a, b);
	if(p != 0) printf("Yes a rotation exists.\n");
	else printf("Not a rotation.\n");
	return 0;
}
