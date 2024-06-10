#include <iostream>
#include <cassert>
#include <queue>
#include <bits/stdc++.h>
using namespace std;


class AVLTree {
private:
	struct BinaryNode {
		string data { };
		int height { };
		int count {1} ;
		vector<string>prefixes ; 

        BinaryNode* left { };
		BinaryNode* right { };

		BinaryNode(string data) :
				data(data) {
                    for(int i=0 ;i<data.size() ;i++){
                        prefixes.push_back(data.substr(0,i+1)) ;
                    }
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
	bool search_string(string target, BinaryNode* node) {
		if(!node)
			return false;

		if (target == node->data)
			return true;

		if (target < node->data)
			return search_string(target, node->left);

		return search_string(target, node->right);
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

	BinaryNode* insert_node(string target, BinaryNode* node) {
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

	BinaryNode* delete_node(string target, BinaryNode* node) {
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

    bool search_prefix(string target, BinaryNode*node){
        if (!node) return false  ;
       
        if (target>node->data)return search_prefix(target,node->right) ;
        if (target<=node->data){
          auto f = find(node->prefixes.begin() , node->prefixes.end() , target) ;
          if (f!=node->prefixes.end()){
            return true ;
          }else return search_prefix(target,node->left) ;
        }
    }

public:
	void insert_value(string target) {
		if (!root)
			root = new BinaryNode(target);
		else
			root = insert_node(target, root);

		verify();
	}

	void delete_value(string target) {
		if (root) {
			root = delete_node(target, root);
			verify();
		}
	}

	bool word_exist(string target) {
		return search_string(target, root);
	}
    bool prefix_exist(string target){
        if (root) return search_prefix(target,root) ;
        else return false ;
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



};


int main(){
	AVLTree tree ;
    tree.insert_value("abcd") ;
    tree.insert_value("xyz") ;

     cout << tree.word_exist("abcd" ) << endl ;
     cout << tree.word_exist("ab" ) << endl ;
     cout << tree.prefix_exist("ab" ) << endl ;
     cout << tree.word_exist("xyz" ) << endl ;

  tree.insert_value("ab") ;
  tree.insert_value("balme") ;
   cout << tree.word_exist("ab" ) << endl ;
     cout << tree.prefix_exist("ba" ) << endl ;
}


