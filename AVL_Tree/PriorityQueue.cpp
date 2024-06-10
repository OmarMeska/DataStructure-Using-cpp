#include <iostream>
#include <cassert>
#include <queue>
#include<bits/stdc++.h>
using namespace std;

struct BinaryNode {
		int data { };
		int height { };
		int count {1} ;
		BinaryNode* left { };
		BinaryNode* right { };
        vector<int> values ;

		BinaryNode(int data , int value ) :
				data(data) {
                    values.push_back(value) ;
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
class AVLTree {
private:
	

	BinaryNode *root { };

	///////////////////////////
	bool search(int key, BinaryNode* node) {
		if(!node)
			return false;

		if (key == node->data)
			return true;

		if (key < node->data)
			return search(key, node->left);

		return search(key, node->right);
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

	BinaryNode* insert_node(int key , int value, BinaryNode* node) {
		if (key < node->data) {
			if (!node->left)
				node->left = new BinaryNode(key , value);
			else	// change left. update left as it might be balanced
				node->left = insert_node(key , value , node->left);
		} else if (key > node->data) {
			if (!node->right)
				node->right = new BinaryNode(key, value );
			else
				node->right = insert_node(key , value , node->right);
		}else if (key == node ->data)
            node->values.push_back(value) ;
        
		node->update();
		return balance(node);
	}

	BinaryNode* min_node(BinaryNode* cur) {
		while (cur && cur->left)
			cur = cur->left;
		return cur;
	}

	BinaryNode* delete_node(int key , BinaryNode* node) {
		if (!node)
			return nullptr;

		if (key < node->data)
			node->left = delete_node(key , node->left);
		else if (key > node->data)
			node->right = delete_node(key , node->right);
		else {
			BinaryNode* tmp = node;

			if (!node->left && !node->right){
				 cout << " this is the root " << node ->data<< "\n" 
				 ;
				node = nullptr;}
			else if (!node->right) 	// case 2: has left only
				node = node->left;		// connect with child
			else if (!node->left)	// case 2: has right only
				node = node->right;
			else {	// 2 children: Use successor
				BinaryNode* mn = min_node(node->right);
				node->data = mn->data;	// copy & go delete
				node->right = delete_node(node->data , node->right);
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
	void insert_value(int value , int key) {
		if (!root)
			root = new BinaryNode(key,value );
		else
			root = insert_node(key,value, root);

		verify();
	}

	void delete_value(int key) {
		if (root) {
			root = delete_node(key, root);
 
			if (root)verify();
		}
	}

	bool search(int key) {
		return search(key, root);
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

pair<bool ,int>lower_bound_method(int key ,BinaryNode*node ,int mx_till_now=-1,bool flag=0){
     if (!node)  return {flag,mx_till_now} ;
     if (node->data == key) return {true,key} ;
    cout << "data "<< node->data<< endl ; 
    if (node->data>key) return lower_bound_method(key,node->left,node->data,true) ;
    if (node->data<key) return lower_bound_method(key,node->right,mx_till_now,flag) ;
   
    // return {flag,mx_till_now} ;

}
pair<bool , int > lower_bound (int key){
    if (root) return lower_bound_method(key,root) ;
    else return {false , -1 };
}


pair<bool,int>upper_bound_method(BinaryNode*node,int key,int mx_so_far=-1 , bool flag=0){
 if (!node)return {flag,mx_so_far};

 if (node->data>key) return upper_bound_method(node->left,key,node->data,true) ;
 else if (node->data <= key) return upper_bound_method(node->right,key,mx_so_far,flag) ;
}
pair<bool,int> Upper_Bound(int key){
    if (root) return upper_bound_method(root,key);
    else return {false,-1} ;
}

int upper_bound_count(int key , BinaryNode*node){
	if (!node) return 0 ;

	if (key < node->data) {
		int sum =1 ;
		if (node->right) 
		 sum += node->right->count ;
		 return sum + upper_bound_count(key ,node->left) ;

	}
	return upper_bound_count(key,node->right) ;
}

// int count_inversion(const vector<int > &vec){
// 	int sum =0 ;

// 	for (int i=0 ;i<(int)vec.size() ;i++){
// 		insert_value(vec[i]) ;
// 		sum+=upper_bound_count(vec[i],root) ;
// 	}
// 	return sum ;
// }

  BinaryNode* get_max(BinaryNode*node){
         
         while (node and node->right) 
          node = node ->right ;
    return node;
  }
BinaryNode* get_root() {
    return root ;
}


};

class PriorityQueue {
 private : 
 AVLTree  my_tree ;
 int size =0 ;
 public: 
 PriorityQueue():my_tree(){}
  
 void enqueue(int value ,int key) {
    my_tree.insert_value(value,key) ;
	size ++ ;
 } 
 int dequeue(){
    BinaryNode*values = my_tree.get_max(my_tree.get_root()) ;
   int x = values->values.back();
     values->values.pop_back() ;
	if (!values->values.size()) {size -- ; my_tree.delete_value(values->data) ;}

   return x ;
 }

 bool isempty() {
	return size==0 ;
 }

 void print(){
	my_tree.level_order_traversal() ;
	cout << endl << endl ;
 }

};

int main() {
	 PriorityQueue tasks ;
	 tasks.enqueue(321 ,3 ) ;
	 tasks.enqueue(221 ,2 ) ;
	 tasks.enqueue(113 ,1 ) ;
     cout << tasks.dequeue() << endl ;
     cout << tasks.dequeue() << endl ;
	 tasks.enqueue(331 ,3 ) ;
	 tasks.enqueue(772 ,7 ) ;
	 tasks.enqueue(661 ,6 ) ;
 	     tasks.enqueue(999,9) ;
     tasks.enqueue(3245,3) ;
     tasks.enqueue(10000,1) ;  
	  tasks.enqueue(511,5) ;
     tasks.enqueue(23,2) ;



   while (!tasks.isempty())
         cout << tasks.dequeue() << endl ;
	  cout << "\n\n Byye\n\n" ;
    
//    while (!tasks.isempty())  cout << tasks.dequeue() <<  ' ' << flush ;
	return 0;
}




/*


 Level 0: 0
 Level 1: 1
 ******************
 Level 0: 1
 Level 1: 0 2
 ******************
 Level 0: 1
 Level 1: 0 2
 Level 2: 3
 ******************
 Level 0: 1
 Level 1: 0 3
 Level 2: 2 4
 ******************
 Level 0: 3
 Level 1: 1 4
 Level 2: 0 2 5
 ******************
 Level 0: 3
 Level 1: 1 5
 Level 2: 0 2 4 6
 ******************
 Level 0: 3
 Level 1: 1 5
 Level 2: 0 2 4 6
 Level 3: 7
 ******************
 Level 0: 3
 Level 1: 1 5
 Level 2: 0 2 4 7
 Level 3: 6 8
 ******************
 Level 0: 3
 Level 1: 1 7
 Level 2: 0 2 5 8
 Level 3: 4 6 9
 ******************
 Level 0: 3
 Level 1: 1 7
 Level 2: 0 2 5 9
 Level 3: 4 6 8 10
 ******************
 Level 0: 7
 Level 1: 3 9
 Level 2: 1 5 8 10
 Level 3: 0 2 4 6 11
 ******************
 Level 0: 7
 Level 1: 3 9
 Level 2: 1 5 8 11
 Level 3: 0 2 4 6 10 12
 ******************
 Level 0: 7
 Level 1: 3 11
 Level 2: 1 5 9 12
 Level 3: 0 2 4 6 8 10 13
 ******************
 Level 0: 7
 Level 1: 3 11
 Level 2: 1 5 9 13
 Level 3: 0 2 4 6 8 10 12 14
 ******************
 Level 0: 7
 Level 1: 3 11
 Level 2: 1 5 9 13
 Level 3: 0 2 4 6 8 10 12 14
 Level 4: 15
 ******************
 Level 0: 7
 Level 1: 3 11
 Level 2: 1 5 9 13
 Level 3: 0 2 4 6 8 10 12 15
 Level 4: 14 16
 ******************
 Level 0: 7
 Level 1: 3 11
 Level 2: 1 5 9 15
 Level 3: 0 2 4 6 8 10 13 16
 Level 4: 12 14 17
 ******************
 Level 0: 7
 Level 1: 3 11
 Level 2: 1 5 9 15
 Level 3: 0 2 4 6 8 10 13 17
 Level 4: 12 14 16 18
 ******************
 Level 0: 7
 Level 1: 3 15
 Level 2: 1 5 11 17
 Level 3: 0 2 4 6 9 13 16 18
 Level 4: 8 10 12 14 19
 ******************
 Level 0: 7
 Level 1: 3 15
 Level 2: 1 5 11 17
 Level 3: 0 2 4 6 9 13 16 19
 Level 4: 8 10 12 14 18 20
 ******************
 Level 0: 7
 Level 1: 3 15
 Level 2: 1 5 11 19
 Level 3: 0 2 4 6 9 13 17 20
 Level 4: 8 10 12 14 16 18 21
 ******************
 Level 0: 7
 Level 1: 3 15
 Level 2: 1 5 11 19
 Level 3: 0 2 4 6 9 13 17 21
 Level 4: 8 10 12 14 16 18 20 22
 ******************
 Level 0: 15
 Level 1: 7 19
 Level 2: 3 11 17 21
 Level 3: 1 5 9 13 16 18 20 22
 Level 4: 0 2 4 6 8 10 12 14 23
 ******************
 Level 0: 15
 Level 1: 7 19
 Level 2: 3 11 17 21
 Level 3: 1 5 9 13 16 18 20 23
 Level 4: 0 2 4 6 8 10 12 14 22 24
 ******************
 Level 0: 15
 Level 1: 7 19
 Level 2: 3 11 17 23
 Level 3: 1 5 9 13 16 18 21 24
 Level 4: 0 2 4 6 8 10 12 14 20 22 25
 ******************
 Level 0: 15
 Level 1: 7 19
 Level 2: 3 11 17 23
 Level 3: 1 5 9 13 16 18 21 25
 Level 4: 0 2 4 6 8 10 12 14 20 22 24 26
 ******************
 Level 0: 15
 Level 1: 7 23
 Level 2: 3 11 19 25
 Level 3: 1 5 9 13 17 21 24 26
 Level 4: 0 2 4 6 8 10 12 14 16 18 20 22 27
 ******************
 Level 0: 15
 Level 1: 7 23
 Level 2: 3 11 19 25
 Level 3: 1 5 9 13 17 21 24 27
 Level 4: 0 2 4 6 8 10 12 14 16 18 20 22 26 28
 ******************
 Level 0: 15
 Level 1: 7 23
 Level 2: 3 11 19 27
 Level 3: 1 5 9 13 17 21 25 28
 Level 4: 0 2 4 6 8 10 12 14 16 18 20 22 24 26 29
 ******************
 Level 0: 15
 Level 1: 7 23
 Level 2: 3 11 19 27
 Level 3: 1 5 9 13 17 21 25 29
 Level 4: 0 2 4 6 8 10 12 14 16 18 20 22 24 26 28 30
 ******************
 Level 0: 15
 Level 1: 7 23
 Level 2: 3 11 19 27
 Level 3: 1 5 9 13 17 21 25 29
 Level 4: 0 2 4 6 8 10 12 14 16 18 20 22 24 26 28 30
 Level 5: 31
 ******************
 Level 0: 15
 Level 1: 7 23
 Level 2: 3 11 19 27
 Level 3: 1 5 9 13 17 21 25 29
 Level 4: 0 2 4 6 8 10 12 14 16 18 20 22 24 26 28 31
 Level 5: 30 32


 */
