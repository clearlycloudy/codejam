#include <bits/stdc++.h>

using namespace std;

class node {
public:
    node * parent;
    node * left;
    node * right;
    int l, r;
    set<int> items;
    int count;
    node(int l, int r) : l(l), r(r), left(nullptr), right(nullptr), count(0) {
	assert(l<=r);
    }
    ~node(){
	if(this->left){
	    delete this->left;
	}
	if(this->right){
	    delete this->right;
	}
    }
    bool is_good(){
	if(this->count>2){
	    return false;
	}
	bool ret = true;
	if(this->left){
	    ret = ret && this->left->is_good();
	}
	if(!ret){
	    return false;
	}
	if(this->right){
	    ret = ret && this->right->is_good();
	}
	return ret;
    }
    bool is_valid_intersect(){
	return items.size() <= 2;
    }
    bool is_leaf(){
	return this->left == nullptr && this->right == nullptr;
    }
    bool is_valid_leaf(){
	assert(items.size()!=0);
	return items.size() == 1;
    }
    set<int> get_items(){
	return items;
    }
    bool intersect(int left, int right){
	assert(left<=right);
	return this->l < right && this->r > left;
    }
    bool node_is_left(int left, int right){
	assert(left<=right);
	return this->r <= left;
    }
    bool node_is_right(int left, int right){
	assert(left<=right);
	return this->l >= right;
    }
    void insert(int left, int right, set<int> ids, int ccount){
	if(this->intersect(left, right)){
	    
	    int intersect_l = std::max(left, this->l);
	    int intersect_r = std::min(this->r, right);

	    int left_l = std::min(left,this->l);
	    int left_r = intersect_l;

	    int right_r = std::max(right,this->r);
	    int right_l = intersect_r;
	    
	    assert(left_l<=left_r);
	    assert(right_l<=right_r);
	    assert(intersect_l<=intersect_r);
	    assert(left_r<=intersect_l);
	    assert(intersect_r<=right_l);
		    
	    //shrink current node range to intersection:
	    int old_l = this->l;
	    int old_r = this->r;
	    
	    this->l = intersect_l;
	    this->r = intersect_r;
	    
	    if(left_l<left_r){
		if(this->left){
		    if(old_l==left_l){
			this->left->insert(left_l,left_r, this->items, this->count);
		    }else{
			this->left->insert(left_l,left_r, ids, ccount);
		    }
		}else{
		    this->left = new node(left_l,left_r);
		    this->left->parent = this;
		    if(old_l==left_l){
			this->left->items = this->items;
			this->left->count = this->count;
		    }else{
			this->left->items = ids;
			this->left->count = 1;
		    }
		}		
	    }

	    if(right_l<right_r){
		if(this->right){
		    if(old_r==right_r){
			this->right->insert(right_l,right_r, this->items, this->count);
		    }else{
			this->right->insert(right_l,right_r, ids, ccount);
		    }
		}else{
		    this->right = new node(right_l,right_r);
		    this->right->parent = this;
		    if(old_r==left_r){
			this->right->items = this->items;
			this->right->count = this->count;
		    }else{
		        this->right->items = ids;
			this->right->count = 1;
		    }
		}
	    }

	    if(intersect_l<intersect_r){//non-empty intersection, add ids
		for(auto j : ids){
		    this->items.insert(j);
		}
		this->count += ccount;
	    }
	}else{
	    if(this->node_is_left(left, right)){//current node is on left
		if(this->right){
		    this->right->insert(left,right,ids, ccount);
		}else{
		    this->right = new node(left,right);
		    this->right->parent = this;
		    this->right->items = ids;
		    this->right->count = ccount;
		}
	    }else if(this->node_is_right(left, right)){//current node is on right
		if(this->left){
		    this->left->insert(left,right,ids, ccount);
		}else{
		    this->left = new node(left,right);
		    this->left->parent = this;
		    this->left->items = ids;
		    this->left->count = ccount;
		}
	    }else{
		assert(false);
	    }
	}
    }
    void print() const {
	cout << "[" << this->l << "," << this->r << "), count: " << this->count << ", ids: {";
	for(auto h: this->items){
	    cout << h << " ";
	}
	cout << "}" <<endl;
	
	if(this->left){
	    cout << "l: ";
	    this->left->print();
	}
	if(this->right){
	    cout << "r: ";
	    this->right->print();
	}
    }
    void collect(unordered_map<int,int> & assign,
		 unordered_map<int,pair<int,int>> & activities,
		 int & a_assign, int & b_assign){

	//traverse wrt. activity times in non-decreasing order
	if(this->left){   
	    this->left->collect(assign, activities, a_assign, b_assign);
	}

	if(a_assign>=0){
	    int start = activities[a_assign].first;
	    int end = activities[a_assign].second;
	    if(!this->intersect(start,end)){
		a_assign = -1;
	    }
	}

	if(b_assign>=0){
	    int start = activities[b_assign].first;
	    int end = activities[b_assign].second;
	    if(!this->intersect(start,end)){
		b_assign = -1;
	    }
	}
	
	for(auto h: items){ //per activity id
	    assert(h>=0);
	    auto it = assign.find(h);
	    if(it==assign.end()){ //unassigned activity found
		if(a_assign == -1){
		    assign[h] = 0;
		    a_assign = h;
		}else{
		    assert(b_assign == -1);
		    assign[h] = 1;
		    b_assign = h;
		}
	    }else{ //already assigned
	    }
	}
	
	if(this->right){
	    this->right->collect(assign, activities, a_assign, b_assign);
	}
    }
};

int main(){
    int t;
    cin >> t;
    for(int i=0; i<t; ++i){
        int n;
	cin >> n;
	node * root = nullptr;
        unordered_map<int,pair<int,int>> activities;
	for(int j=0; j<n; ++j){
	    int s,e;
	    cin >> s >> e;
	    activities[j] = {s,e};
	    if(nullptr==root){
		root = new node(s,e);
		root->count = 1;
		root->items = {j};
	    }else{
		root->insert(s,e,{j},1);
	    }
	}
	// cout << "t:" << i << "--------" << endl;
	// root->print();

	if(!root->is_good()){
	    printf("Case #%d: ", i+1);
	    printf("IMPOSSIBLE\n");
	}else{
	    printf("Case #%d: ", i+1);
	    unordered_map<int,int> assign; //map activity -> person
	    int person_a_cur = -1;
	    int person_b_cur = -1;
	    root->collect(assign, activities, person_a_cur, person_b_cur);
	    for(int j = 0; j < n; ++j){
	        int person = assign[j];
	    // for(auto const & act: assign){
		if(person==0){
		    printf("C");
		}else{
		    printf("J");
		}
	    }
	    printf("\n");
	}
        delete root;
    }
}
