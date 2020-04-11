#include <bits/stdc++.h>

using namespace std;

int difa = -1;
int difb = -1;
int samea = -1;
int sameb = -1;

int valdiffa;
int valdiffb;
int valsamea;
int valsameb;

bool query(vector<int> & arr, int & l, int & r, int & q, int b){
    if(l>r){
	return true;
    }
    if((q%10)!=0 || q==0 ){
	cout << l+1 << endl;
	cin >> arr[l];
	cout << r+1 << endl;
	cin >> arr[r];
	l++;
	r--;
	q+=2;
	if(difa == -1 && difb == -1){
	    for(int h=0; h<l; ++h){
		int va = arr[h];
		int vb = arr[b-1-h];
		if(va!=vb){
		    difa = h;
		    difb = b-1-h;
		    valdiffa = va;
		    valdiffb = vb;
		    break;
		}
	    }
	}
	if(samea == -1 && sameb == -1){
	    for(int h=0; h<l; ++h){
		int va = arr[h];
		int vb = arr[b-1-h];
		if(va==vb){
		    samea = h;
		    sameb = b-1-h;
		    valsamea = va;
		    valsameb = vb;
		    break;
		}
	    }
	}
    }else{
	//need to check
	bool bitflip;
	if(samea!=-1 && sameb!=-1){
	    cout << samea+1 << endl;
	    int answer;
	    cin >> answer;
	    if(answer!=valsamea){ //bit flip
		bitflip = true;
		for(int h=0; h<b; ++h){
		    arr[h] = arr[h] == 0 ? 1 : 0;
		}
		assert(valsameb==0 || valsameb==1);
		assert(valsamea==0 || valsamea==1);
		assert(valdiffb==0 || valdiffb==1);
		assert(valdiffa==0 || valdiffa==1);
		valsamea = valsamea == 0 ? 1 : 0;
		valsameb = valsameb == 0 ? 1 : 0;
		valdiffa = valdiffa == 0 ? 1 : 0;
		valdiffb = valdiffb == 0 ? 1 : 0;
	    }else{
		bitflip = false;
	    }
	    q++;
	}
	if(samea!=-1){ //checked bit flip
	    if(bitflip){ //bit flip
		//check reversal
		if(difa!=-1 && difb!=-1){
		    cout << difa+1 << endl;
		    int answer;
		    cin >> answer;
		    if(answer!=valdiffa){
			//apply reversal
			for(int h=0; h<b/2; ++h){
			    std::swap(arr[h], arr[b-1-h]);
			}
			std::swap(valdiffa, valdiffb);
		    }
		    q++;
		}
	    }else{ //no bit flip
		//check reversal
		if(difa!=-1 && difb!=-1){
		    cout << difa+1 << endl;
		    int answer;
		    cin >> answer;
		    if(answer!=valdiffa){
			//apply reversal
			for(int h=0; h<b/2; ++h){
			    std::swap(arr[h], arr[b-1-h]);
			}
			std::swap(valdiffa, valdiffb);
		    }
		    q++;
		}
	    }
	}else{ //unknown bit flip status
	    //check reversal
	    if(difa!=-1 && difb!=-1){
		cout << difa+1 << endl;
		int answer;
		cin >> answer;
		if(answer!=valdiffa){
		    //apply reversal
		    for(int h=0; h<b/2; ++h){
			std::swap(arr[h], arr[b-1-h]);
		    }
		    std::swap(valdiffa, valdiffb);
		}
		q++;
	    }
	}
	if(q%2==1){
	    cout << 1 << endl;
	    int dummy;
	    cin >> dummy;
	    q++;
	}
    }

    return l > r;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    int t, b;
    cin >> t >> b;

    for(int i=0; i<t; ++i){
	int q = 0;
	vector<int> arr(b,0);
	int l=0;
	int r=b-1;
        difa = -1;
	difb = -1;
	samea = -1;
	sameb = -1;
	while(1){
	    bool answer = query(arr,l,r,q,b);
	    if(answer){
		for(auto v: arr){
		    cout << v;
		}
		cout << endl;
		string ret;
		cin >> ret;
		if(ret!="Y"){
		    exit(0);
		}else{
		    break;
		}
	    }
	}
    }
}
