#include <bits/stdc++.h>

int arr[100][100];

int main(){
    using namespace std;
    int t;
    cin >> t;
    for(int i=0; i<t; ++i){
	int n;
	cin >> n;
	int r =  0;
	int c = 0;
	for(int j=0; j<n; ++j){
	    int counts_in_row[100] = {0};
	    for(int k=0; k<n; ++k){
		int v;
		cin >> v;
		arr[j][k] = v;
		counts_in_row[v-1]++;
	    }
	    for(int k=0; k<n; ++k){
		if(counts_in_row[k] > 1){
		    r++;
		    break;
		}
	    }
	}
	int trace = 0;
	for(int j=0; j<n; ++j){
	    trace += arr[j][j];
	}

	for(int k=0; k<n; ++k){
	    int counts_in_col[100] = {0};
	    for(int j=0; j<n; ++j){
		int v = arr[j][k];
		counts_in_col[v-1]++;
	    }
	    for(int j=0; j<n; ++j){
		if(counts_in_col[j] > 1){
		    c++;
		    break;
		}
	    }
	}
        printf("Case #%d: %d %d %d\n", i+1, trace, r, c);
    }
}
