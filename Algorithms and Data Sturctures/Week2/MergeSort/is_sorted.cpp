#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector <int> vi;

int main(){
	//ios_base::sync_with_stdio(false);
	//cin.tie(nullptr);
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	char file[100];
	printf("Enter the name of the file: ");
	scanf("%s", file);
	FILE *f1 = fopen(file, "r");
	printf("Enter n: ");
	int n; scanf("%d", &n);
	int last; fscanf(f1, "%d", &last);
	int current;
	int flag = 0;
	for(int i=1; i<n; i++){
		fscanf(f1, "%d", &current);
		if(current < last) {
			cout << "Not Sorted." << endl;
			cout << i << " " << last << " " << current << endl;
			flag = 1; break;
		}
		last = current;
	}
	if(!flag) cout << "Sorted." << endl;
	fclose (f1);
	return 0;
}