#include <stdio.h>

void tower(int pre, int target, int n){
	if(n == 1) {
		printf("Move disk from %d to %d.\n", pre, target);
	}
	else{
		tower(pre, (3 - pre - target), n-1);
		printf("Move disk from %d to %d.\n", pre, target);
		tower((3 - pre - target), target, n-1);
	}
}

int main(){
	int n;
	printf("Enter the value on n: ");
	scanf("%d", &n);
	tower(0, 2, n);
	return 0;
}
