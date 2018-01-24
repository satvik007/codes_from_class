#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector <int> vi;

int main (){
	FILE * pFile, *hFile;
	char name[100] = {"input.bin"};
	char human[100] = {"input.txt"};
	pFile = fopen(name, "wb");
	hFile = fopen(human, "w");
	int n; printf("Enter n: ");
	scanf("%d", &n);
	int temp=n;
	//fwrite(&temp, sizeof (temp), sizeof (temp), pFILE);
	srand(100);
	for(int i=0; i<n; i++){
		temp = rand () % 1000000;
		fwrite(&temp, sizeof (temp), 1, pFile);
		fprintf(hFile, "%d\n", temp);
	}
	fclose (pFile); fclose(hFile);
	return 0;
}
