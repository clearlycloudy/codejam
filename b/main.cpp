#include <bits/stdc++.h>

int arr[100][100];

int main(){
    using namespace std;
    int t;
    cin >> t;
    for(int i=0; i<t; ++i){
	string s;
	cin >> s;
        vector<char> out;
	int prev_v = 0;
	for(auto c: s){
	    int v = c-'0';
	    int d = v-prev_v;
	    bool positive = d>0;
	    int d_abs = abs(d);
	    while(d_abs--!=0){
		out.push_back( positive ? '(' : ')' );
	    }
	    out.push_back((char)(v+'0'));
	    prev_v = v;
	}
	int v=0;
	int d = v-prev_v;
	while(d++!=0){
	    out.push_back(')');
	}
	
        printf("Case #%d: ", i+1);
	for(auto c: out){
	    printf("%c", c);
	}
	printf("\n");
    }
}
