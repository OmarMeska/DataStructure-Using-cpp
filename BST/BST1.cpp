#include <bits/stdc++.h>
using namespace std;

deque <int> next_greater_idx(deque<int>v) {
    stack<int>pos ;
    for (int i=0 ;i<(int)v.size();i++){
        while(!pos.empty() and v[i] >v[pos.top()]) {
            v[pos.top()] = i;
            pos.pop() ;
        }
        pos.push(i) ;
    }
    while (!pos.empty()){
        v[pos.top()] =v.size() ;
        pos.pop() ;
    }
    return v;
}

class BinarySearchTree {
public:
	int data { };
	BinarySearchTree* left { };
	BinarySearchTree* right { };
    BinarySearchTree* parent {}  ;

public:

	BinarySearchTree(int data , BinarySearchTree*parent = nullptr) :
      parent(parent),data(data) {
	}

    BinarySearchTree(deque<int>&preorder ,int start =0 ,int end =-1){
        if (end == -1 )end = preorder.size()-1 ;
        data= preorder[start] ;

        for (int i=start+1 ;i<=end+1 ;i++) {
            if (start+1 == end +1 or preorder[i] > data){
                if (start+1 <= i-1) // there is a left tree 
                          left = new BinarySearchTree(preorder,start+1 , i-1) ;
                if (i<= end )
                 right =new BinarySearchTree(preorder,i , end);
              break;
            }
        }
    }

    BinarySearchTree(deque<int>&preorder ,const deque<int>&next_greater ,int start =0 , int end =-1 ){
        if (end ==-1 ) end = (int)preorder.size()-1 ;

        data = preorder[start] ;

        int split = next_greater[start] ;

        if (split > end )
           split = end +1 ;

         if (start +1 <=split -1 ) // there is  a left tree 
         left = new BinarySearchTree(preorder,next_greater,start+1 , split-1) ;
         if (split <= end )
         right =new BinarySearchTree(preorder,next_greater,split,end) ;

    }

   bool next_between(deque<int>&preorder,int min, int max){
    if (preorder.empty()) return false ;
    return min<preorder[0] and preorder[0]<max ;
   }
    BinarySearchTree(deque<int>&preorder ,int min =0, int max =1001){
    data = preorder[0] ;
    preorder.pop_front() ;

    if (next_between(preorder,min,data))
     left = new BinarySearchTree(preorder,min,data) ;

     if (next_between(preorder,data,max)) 
     right = new BinarySearchTree(preorder,data,max) ;


    }

    BinarySearchTree(deque<int> &preroder):BinarySearchTree(preroder,next_greater_idx(preroder)){

    }

	void print_inorder() {
		if (left)
			left->print_inorder();
	
        cout << "my data " << data << " ";	
        cout << " parent.data  " ;
        if (parent) cout << parent->data << " \n"; 
        else cout << " NULL \n" ;
    
		if (right)
			right->print_inorder();
	}
	
    ////////////////////////////////////////////

	void insert(int target ) {
    
		if (target < data) {
			if (!left){
				left = new BinarySearchTree(target,this);
           
                }
			else
				left->insert(target );
		} else if(target > data){
			if (!right){
				right = new BinarySearchTree(target,this);
                }
			else
				right->insert(target);
		} // else: exists already
	}

	bool search(int target) {	// tail recursion
		if (target == data)
			return true;

		if (target < data)
			return left && left->search(target);

		return right && right->search(target);
	}

      int tree_height(){
         int res = 0;
         if (left) res = max (res , 1+left->tree_height()) ;
         if (right) res = max (res , 1+right->tree_height()) ;
         return res ;
      }

    bool search_iterative(int target){
           BinarySearchTree*cur = this ;
           int h = cur->tree_height() ;
           while(h--){
            if (cur->data == target) return true; 
            else if (cur->data > target) cur = cur->left ;
            else if (cur ->data <target) cur = cur->right ;
            }
            return false ;
    }

    bool is_bst(){
        if (!left and !right) return true ;
        if (left) if (left->data > data ) return false ;
        if (right) if (right->data < data) return false ;
        // if (left->data > data or right->data < data ) return false ;
        bool res = 1 ;
        if (left){
           res = left->is_bst() ;
        }
               
        if (right){
            res = res && right->is_bst() ;
        }
        return res ;
    }

    void get_inorder(vector<int> &val){
    if (left) left->get_inorder(val) ;
      val.push_back(data) ;
      if (right)right->get_inorder(val) ;
   }
   
    bool is_bst2(){
    vector<int> vals ;
    get_inorder(vals) ;
    vector<int> sorted_vals=vals ;
    sort(sorted_vals.begin(),sorted_vals.end());
  return sorted_vals == vals ;
    }

    int kth_smallest(int &k) {
        if (k==0) return -1234;
        if (left) {
            int res = left-> kth_smallest(k) ;
          if (k==0) return res ;
        }
        k-=1 ;
        if (k==0) return data ;

        if (right) {
             int res = right->kth_smallest(k) ;
             if(k==0) return res ;
        }
        return -1234 ;

    }

  int LCA(int x ,int y){
     if (x <= data and y >=data) return data ;
     if (x <data and y <data) return left->LCA(x,y) ;
     if(x>data and y > data) return right->LCA(x,y) ;
  }

  int min_value() {
		BinarySearchTree* cur = this;
		while (cur && cur->left)
			cur = cur->left;
		return cur->data;
	}

	// BinarySearchTree* get_next(vector<BinarySearchTree*> &ancestors) {
	// 	if (ancestors.size() == 0)
	// 		return nullptr;
	// 	BinarySearchTree* node = ancestors.back();	// last element
	// 	ancestors.pop_back();
	// 	return node;
	// }

   BinarySearchTree* find_chain( int target) {

		if (target == data)
			return this;

		if (target < data){
            if (left)  return left->find_chain(target) ;
            else return nullptr ;
        }
        if (target> data) { 
            if (right) return right ->find_chain(target ) ;
            else return nullptr ;
        }
	}

	pair<bool, int> successor(int target) {
		BinarySearchTree * child = find_chain(target) ;
        if (!child) return make_pair(false,-1) ;


		if (child->right)	// must have be in min of right
			return make_pair(true, child->right->min_value());

		BinarySearchTree* parent_child = child->parent;

		// Cancel chain of ancestors I am BIGGER than them
		while (parent_child && parent_child->right == child)
			child = parent_child, parent_child = parent_child->parent;

		if (parent_child)	//
			return make_pair(true, parent_child->data);
		return make_pair(false, -1);
	}

    void successor_queries(deque<int>&queries,vector<int>&answer,vector<int>&traversal){
        if (queries.empty()) return ;

        if (left and queries.front()<data){
            left->successor_queries(queries,answer,traversal) ;
            if (queries.empty()) return ;
        }

        if (!traversal.empty() and traversal.back() == queries.front()) {
            answer.push_back(data) ;
            queries.pop_front();
            if (queries.empty()) return ;
        }
        traversal.push_back(data) ;

        if (right and queries.front()>=data){
             right->successor_queries(queries,answer,traversal) ;
           
        }
    }

 

};

 bool is_degenerate(vector<int>&preorder){
    vector<int>inorder = preorder ;
    sort(inorder.begin() , inorder.end())  ;
    int first = 0 , last = inorder.size()-1 ;
    for(int i=0 ;i<preorder.size() and first<=last ;i++){
         if (inorder[first] == preorder[i])first++ ;
         else if (inorder[last] == preorder[i]) last -- ;
         else return false ;
    }
    return true ;
  }

BinarySearchTree * build_balanced_bst_tree(vector<int>&values , int start =0 , int end =-1) {
if (end ==-1 ) end = values.size()-1 ;
int mid = start+(end-start) /2 ;
BinarySearchTree * tree = new BinarySearchTree(values[mid]) ;
if (mid > start) tree->left = build_balanced_bst_tree(values,start,mid -1);
if (mid<end) tree->right = build_balanced_bst_tree(values,mid+1,end) ;
 return tree ;
} 

int main() {
	BinarySearchTree tree(50);
	tree.insert(20);
	tree.insert(45);
	tree.insert(70);
	tree.insert(73);
	tree.insert(35);
	tree.insert(15);
	tree.insert(60);
 
     vector<int> answer  ;
     vector<int>traversal ;
     deque<int> q {15,20,45,70,73} ;

     tree.successor_queries(q , answer,traversal) ;
     for (auto i : answer) cout << i << ' ' ;
      cout<< endl ;
    for(auto i: traversal ) cout << i << ' ' ;

    cout << "\nbye\n" ;
	return 0;
}

