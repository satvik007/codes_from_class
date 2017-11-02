#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define inf 1000000000
#define IN freopen("in.txt", "r", stdin) // Two useful functions which take input from file as if it comes from stdin
#define OUT freopen("out.txt", "w", stdout) // Very helpful in debugging 

int lo[10005]; // temporary arrays required when merging two arrays.
int hi[10005];
int b[10005];
int a[101][101];
int n;

void merge(int left, int right){
	int mid = (left+right)/2;
	int u = 0;
	int v = 0;
	int i = 0;
	for(i=left*n; i<mid*n+n; i++){
		lo[u++] = b[i];
	}
	lo[u] = inf;
	for(i=mid*n+n; i<right*n+n; i++){
		hi[v++] = b[i];
	}
	hi[v] = inf;
	u = 0; v = 0;
	for(int i=left*n; i<right*n+n; i++){
		if(lo[u] < hi[v]){
			b[i] = lo[u++];
		}
		else {
			b[i] = hi[v++];
		}
	}
}

void merge_rec(int left, int right){
	if(left < right){
		merge_rec(left, (left+right)/2);
		merge_rec((left+right)/2+1, right);
		merge(left, right);
	}
}

int main(){
	//OUT;
	int i = 0, j = 0;
	printf("Enter n: ");
	scanf("%d", &n);
	printf("Enter the elements: \n");
	int notasc = 0;
    for(i=0; i<n; i++){
        for(j=0; j<n; j++) {
            scanf("%d", &a[i][j]);
            if(i>0){
                if(a[i-1][j] > a[i][j]) notasc = 1; // input not ascending
            }
            if(j>0){
                if(a[i][j-1] > a[i][j]) notasc = 1; // input not ascending
            }
        }
        a[i][n] = inf;
    }
    // The input is neither ascending and it is neither descending.
    if(notasc) {
        printf("Input not valid.\n :(");
        return 1;
    }
    for(i=0; i<n; i++){
    	for(j=0; j<n; j++){
    		b[i*n+j] = a[i][j];
    	}
    }
    //for(int i=0; i<n*n; i++) printf("%d ", b[i]); printf("\n");
    merge_rec(0, n-1);
    for(int i=0; i<n*n; i++) printf("%d ", b[i]); printf("\n");
    return 0;
}