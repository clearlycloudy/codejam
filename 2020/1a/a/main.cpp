#include <bits/stdc++.h>

int arr[100][100];

int main(){
    using namespace std;

    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);
    
    int t;
    cin >> t;
    for(int i=0; i<t; ++i){
	int n;
	cin >> n;
	// cout << "test: " << n << endl;
	vector<string> pref(n);
	vector<string> suf(n);
	vector<bool> exists_pref(n,false);
	vector<bool> exists_suf(n,false);
	vector<vector<string>> mid(n, vector<string>());
	for(int j=0; j<n; ++j){
	    string s;
	    cin >> s;
	    int l = -1;
	    int ll = -1;
	    vector<int> pos_star;
	    for(int k=0; k<s.size(); ++k){
		if(s[k]=='*'){
		    pos_star.push_back(k);
		    if(k>0 && l == -1){
			string preff = s.substr(0,k);
			pref[j]=preff;
			exists_pref[j]=true;
		    }
		    ll = l;
		    l = k;
		}
	    }
	    
	    if(l+1<s.size()){
		string suff = s.substr(l+1,s.size()-(l+1));
		suf[j]=suff;
		exists_suf[j]=true;
	    }

	    if(pos_star.size()>1){
		for(int k = 1; k < pos_star.size(); ++k){
		    int length = pos_star[k] - pos_star[k-1] - 1;
		    string m = s.substr(pos_star[k-1]+1, length);
		    assert(length>=0);
		    if(length>0){
			mid[j].push_back(m);
		    }
		}
	    }

	    // cout << "prefix: " << (!exists_pref[j] ? "empty" : pref[j]) << endl;
	    // cout << "suffix: " << (!exists_suf[j] ? "empty" : suf[j]) << endl;
	    // cout << "mid: ";
	    // if(mid[j].size()==0){
	    // cout << "empty" << endl;
	    // }else{
	    // 	for(auto m: mid[j]){
	    // 	    cout << m << " ";
	    // 	}
	    // 	cout << endl;
	    // }	    
	}
	int pref_longest = 0;
	int suf_longest = 0;
	int idx_pref_longest = -1;
	int idx_suf_longest = -1;
	for(int j=0; j<n; ++j){
	    if(pref_longest < pref[j].size()){
		// cout << "preflongest: " << pref[j].size() << endl;
		idx_pref_longest = j;
	    }
	    if(suf_longest < suf[j].size()){
		// cout << "suflongest: " << suf[j].size() << endl;
		idx_suf_longest = j;
	    }
	    pref_longest = pref_longest < pref[j].size() ? pref[j].size() : pref_longest;
	    suf_longest = suf_longest < suf[j].size() ? suf[j].size() : suf_longest;
	}
	bool valid = true;
	for(int h=0; h<pref_longest; ++h){
	    bool got = false;
	    char c;
	    for(int j=0; j<n; ++j){
		if(h>=pref[j].size()){
		    continue;
		}
		if(!got){
		    got = true;
		    c = pref[j][h];
		}else {
		    assert(h < pref[j].size());
		    if(c != pref[j][h]){
			// cout << "invalid 1: " << j << " " << h << ", " << c << " " << pref[j][h] << endl;
			valid = false;
			break;
		    }
		}
	    }
	}
	if(valid){
	    // cout << "suf check" << endl;
	    for(int j=0; j<n; ++j){
		reverse(suf[j].begin(), suf[j].end());
	    }
	    for(int h=0; h<suf_longest; ++h){
		bool got = false;
		char c;
		for(int j=0; j<n; ++j){
		    if(h>=suf[j].size()){
			continue;
		    }
		    if(!got){
			got = true;
			c = suf[j][h];
		    }else {
			if(c != suf[j][h]){
			    // cout << "invalid: " << j << " " << h << endl;
			    valid = false;
			    break;
			}else{
			    // cout << "suf match: " << c << " " << suf[j][h] << endl;
			}
		    }
		}
	    }
	    for(int j=0; j<n; ++j){
		reverse(suf[j].begin(), suf[j].end());
	    }
	}	
	
	if(valid){
	    string ans;
	    if(idx_pref_longest!=-1){
	        ans = pref[idx_pref_longest];
	    }
	    for(int j=0; j<n; ++j){
		for(auto m: mid[j]){
		    ans += m;
		}
	    }
	    if(idx_suf_longest!=-1){
		ans += suf[idx_suf_longest];
	    }
	    printf("Case #%d: %s\n", i+1, ans.c_str());
	}else{
	    printf("Case #%d: *\n", i+1);
	}

    }

	return 0;
}
