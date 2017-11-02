// Satvik Choudhary
// 111601021

#include <stdio.h>
#include <stdlib.h>

int a[20][20];
int b[20][20];

int main(){
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	int n, m, i, j, k;
	printf("Enter the row and column heights respectively: ");
	scanf("%d%d", &n, &m);
	printf("Enter the elements: ");
	for(i=0; i<n; i++){
		for(j=0; j<m; j++){
			scanf("%d", &a[i][j]);
			b[i][j] = a[i][j];
		}
	}
	for(i=0; i<n; i++){
		for(j=0; j<m; j++){
			// if any 0 element is detected.
			if(b[i][j] == 0) {
				//making the row 0.
				for(k=0; k<m; k++){
					a[i][k] = 0;
				}
				// making the column 0.
				for(k = 0; k<n; k++){
					a[k][j] = 0;
				}
			}
		}
	}
	for(i=0; i<n; i++){
		for(j=0; j<m; j++){
			printf("%d ", a[i][j]);
		}
		printf("\n");
	}
	return 0;
}
