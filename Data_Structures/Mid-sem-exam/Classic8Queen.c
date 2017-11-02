// Satvik Choudhary
// 111601021
// 10.64.1.174
// Serial number c
// Question 4
// Assumption - Answers in the file out.txt. I am just giving the row numbers of queens for each successive columns. To get the answer in terminal just comment the freopen function in main 2nd line.
// Logic - recursive search or backtracking using bitmask.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef long long ll;

ll bit[100];
int k = 0;
ll one = 1;

void queen(ll mask, int size){
	int i = 0, j, solve, m, n;
	if(size == 8){
		solve = 1;
		for(i=0; i<64; i++){
			if(mask & (one << i)) {
				for(j=i+1; j<64; j++){
					if(mask & (one << j)){
						if(i/8 == j/8) solve = 0;
						if(i%8 == j%8) solve = 0;
						if(i%8 - i/8 == j%8 - j/8) solve = 0;
						if(i%8 + i/8 == j%8 + j/8) solve = 0;
					}
				}
			}
			
		}
		if(solve){
			bit[k++] = mask;
		}
		return;
	}
	//printf("infinite. %lld\n", mask);
	for(i = 0; i<8; i++){
		solve = 0;
		for(j = 0; j<size; j++){
			if(mask & (one << (j*8+i))) solve = 1;
		}
		if(!solve) queen(mask | (one << (size*8 + i)), size+1);
	}
	
}

int main(){
	//freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	memset(bit, 0, sizeof(bit));
	k = 0;
	queen(0, 0);
	printf("Total number of solutions is - %d\n", k);
	printf("These solutions should be interpreted as row number for each successive column from left to right. And I am using 1 based indexing.\n");
	int i = 0;
	for(i = 0; i<k; i++){
		for(int j = 0; j<64; j++){
			if(bit[i] & (one << (j))) {
				printf("%d", (j%8+1));
			}
		}
		printf("\n");
	}
	
	printf("\n");
	int b[8][8];
	for(i = 0; i<k; i++){
		memset(b, 0, sizeof(b));
		for(int j = 0; j<64; j++){
			if(bit[i] & (one << j)) b[j/8][j%8] = 1; 
		}
		printf("%d\n", i);
		int le, ri;
		for(le = 0; le < 8; le++){
			for(ri = 0; ri < 8; ri++){
				printf("%d", b[le][ri]);
			}
			printf("\n");
		}
		printf("\n");
	}
	return 0;
}






