#include <iostream>
#include <cassert>
#include <queue>
using namespace std;


class AVLTree {
private:
	struct BinaryNode {
		int data { };
		int height { };
		int count {1} ;
		BinaryNode* left { };
		BinaryNode* right { };

		BinaryNode(int data) :
				data(data) {
		}

		int ch_height(BinaryNode* node) {	// child height
			if (!node)
				return -1;			// -1 for null
			return node->height;	// 0 for leaf
		}
		
		int ch_count(BinaryNode*node ){
			if (!node ) return 0 ;
			return node->count;
		}

		int update() {	// call in end of insert function
			 height = 1 + max(ch_height(left), ch_height(right));
		    count = 1 + ch_count(left) + ch_count (right) ;
		}
		int balance_factor() {
			return ch_height(left) - ch_height(right);
		}
	};

	BinaryNode *root { };

	///////////////////////////
	bool search(int target, BinaryNode* node) {
		if(!node)
			return false;

		if (target == node->data)
			return true;

		if (target < node->data)
			return search(target, node->left);

		return search(target, node->right);
	}

	BinaryNode* right_rotation(BinaryNode* Q) {
		cout << "right_rotation " << Q->data << "\n";
		BinaryNode* P = Q->left;
		Q->left = P->right;
		P->right = Q;
		Q->update();
		P->update();
		return P;
	}

	BinaryNode* left_rotation(BinaryNode* P) {
		cout << "left_rotation " << P->data << "\n";
		BinaryNode* Q = P->right;
		P->right = Q->left;
		Q->left = P;
		P->update();
		Q->update();
		return Q;
	}

	BinaryNode* balance(BinaryNode* node) {
		if (node->balance_factor() == 2) { 			// Left
			if (node->left->balance_factor() == -1)	// Left Right?
				node->left = left_rotation(node->left);	// To Left Left

			node = right_rotation(node);	// Balance Left Left
		} else if (node->balance_factor() == -2) {
			if (node->right->balance_factor() == 1)
				node->right = right_rotation(node->right);

			node = left_rotation(node);
		}
		return node;
	}

	BinaryNode* insert_node(int target, BinaryNode* node) {
		if (target < node->data) {
			if (!node->left)
				node->left = new BinaryNode(target);
			else	// change left. update left as it might be balanced
				node->left = insert_node(target, node->left);
		} else if (target > node->data) {
			if (!node->right)
				node->right = new BinaryNode(target);
			else
				node->right = insert_node(target, node->right);
		}
		node->update();
		return balance(node);
	}

	BinaryNode* min_node(BinaryNode* cur) {
		while (cur && cur->left)
			cur = cur->left;
		return cur;
	}

	BinaryNode* delete_node(int target, BinaryNode* node) {
		if (!node)
			return nullptr;

		if (target < node->data)
			node->left = delete_node(target, node->left);
		else if (target > node->data)
			node->right = delete_node(target, node->right);
		else {
			BinaryNode* tmp = node;

			if (!node->left && !node->right)	// case 1: no child
				node = nullptr;
			else if (!node->right) 	// case 2: has left only
				node = node->left;		// connect with child
			else if (!node->left)	// case 2: has right only
				node = node->right;
			else {	// 2 children: Use successor
				BinaryNode* mn = min_node(node->right);
				node->data = mn->data;	// copy & go delete
				node->right = delete_node(node->data, node->right);
				tmp = nullptr;	// Don't delete me. Successor will be deleted
			}
			if (tmp)
				delete tmp;
		}
		if (node) {
			node->update();
			node = balance(node);
		}
		return node;
	}

	bool is_bst(BinaryNode* node) {
		bool left_bst = !node->left || node->data > node->left->data && is_bst(node->left);

		if (!left_bst)
			return false;

		bool right_bst = !node->right || node->data < node->right->data && is_bst(node->right);
		return right_bst;
	}

	void verify() {
		assert(abs(root->balance_factor()) <= 1);
		assert(is_bst(root));
	}

	void print_inorder(BinaryNode* node) {
		if(!node)
			return;

		print_inorder(node->left);
		cout << node->data << " ";
		print_inorder(node->right);
	}


public:
	void insert_value(int target) {
		if (!root)
			root = new BinaryNode(target);
		else
			root = insert_node(target, root);

		verify();
	}

	void delete_value(int target) {
		if (root) {
			root = delete_node(target, root);
			verify();
		}
	}

	bool search(int target) {
		return search(target, root);
	}

	void print_inorder() {
		print_inorder(root);
	}

	void level_order_traversal() {
		if (!root)
			return;

		cout << "******************\n";
		queue<BinaryNode*> nodes_queue;
		nodes_queue.push(root);

		int level = 0;
		while (!nodes_queue.empty()) {
			int sz = nodes_queue.size();

			cout << "Level " << level << ": ";
			while (sz--) {
				BinaryNode*cur = nodes_queue.front();
				nodes_queue.pop();

				cout << cur->data << " ";
				if (cur->left)
					nodes_queue.push(cur->left);
				if (cur->right)
					nodes_queue.push(cur->right);
			}
			level++;
			cout << "\n";
		}
	}

pair<bool ,int>lower_bound_method(int target ,BinaryNode*node ,int mx_till_now=-1,bool flag=0){
     if (!node)  return {flag,mx_till_now} ;
     if (node->data == target) return {true,target} ;
    cout << "data "<< node->data<< endl ; 
    if (node->data>target) return lower_bound_method(target,node->left,node->data,true) ;
    if (node->data<target) return lower_bound_method(target,node->right,mx_till_now,flag) ;
   
    // return {flag,mx_till_now} ;

}
pair<bool , int > lower_bound (int target){
    if (root) return lower_bound_method(target,root) ;
    else return {false , -1 };
}


pair<bool,int>upper_bound_method(BinaryNode*node,int target,int mx_so_far=-1 , bool flag=0){
 if (!node)return {flag,mx_so_far};

 if (node->data>target) return upper_bound_method(node->left,target,node->data,true) ;
 else if (node->data <= target) return upper_bound_method(node->right,target,mx_so_far,flag) ;
}
pair<bool,int> Upper_Bound(int target){
    if (root) return upper_bound_method(root,target);
    else return {false,-1} ;
}

int upper_bound_count(int target , BinaryNode*node){
	if (!node) return 0 ;

	if (target < node->data) {
		int sum =1 ;
		if (node->right) 
		 sum += node->right->count ;
		 return sum + upper_bound_count(target ,node->left) ;

	}
	return upper_bound_count(target,node->right) ;
}

int count_inversion(const vector<int > &vec){
	int sum =0 ;

	for (int i=0 ;i<(int)vec.size() ;i++){
		insert_value(vec[i]) ;
		sum+=upper_bound_count(vec[i],root) ;
	}
	return sum ;
}



};


int main(){
	
}


