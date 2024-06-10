#include<bits/stdc++.h>
using namespace std;

class BinaryTree {
private:
	int data { };
	BinaryTree* left { };
	BinaryTree* right { };

public:
	BinaryTree(int data) :
			data(data) {
	}

 BinaryTree (deque<int>&preorder,deque<int>&inorder ,int start_inorder =0 ,int end_inorder=-1){
     if (end_inorder == -1 )end_inorder = inorder.size()-1 ;
    int root_data =preorder.front() ;
    preorder.pop_front( ) ;

    for (int i = start_inorder ; i <= end_inorder ; i++){
      if (inorder[i] ==data){
                if (i>start_inorder) 
             left = new BinaryTree(preorder,inorder,start_inorder,i-1) ;
       if (i<end_inorder) 
               right  = new BinaryTree(preorder,inorder,i+1,end_inorder) ;
        break;
      }
    }
 }

  BinaryTree(string postfix){
    stack<BinaryTree*> tree ;

    for (int i=0 ;i<postfix.length() ;i++){
        BinaryTree*cur = new BinaryTree(postfix[i]);
        if (!isdigit(postfix[i])){
          cur->right = tree.top() ;
          tree.pop() ;
          cur->left  =tree.top() ;
          tree.pop() ;
        }
        tree.push(cur) ;
    }
 
     this->left = tree.top()->left ;
    this-> right = tree.top()->right ;
    this->data = tree.top()->data ;

  }

	void print_inorder() {
		if(left)
			left->print_inorder();
		cout << data << " ";
		if(right)
			right->print_inorder();
	}

	void add(vector<int> values, vector<char> direction) {
		assert(values.size() == direction.size());
		BinaryTree* current = this;
		// iterate on the path, create all necessary nodes
		for (int i = 0; i < (int) values.size(); ++i) {
			if (direction[i] == 'L') {
				if (!current->left)
					current->left = new BinaryTree(values[i]);
				else
					assert(current->left->data == values[i]);
				current = current->left;
			} else {
				if (!current->right)
					current->right = new BinaryTree(values[i]);
				else
					assert(current->right->data == values[i]);
				current = current->right;
			}
		}
	}

    int tree_max () {
        int mx1 = INT16_MIN ;
        int mx2 = INT16_MIN ;
        if (left) 
         mx1 = left->tree_max() ;
         if (right) 
          mx2 = right->tree_max () ;
        
        return max (data,max (mx1,mx2)) ;
    }

    int tree_height(){
      
        int res1=0 ;

        if (left) 
            res1 = 1+left->tree_height() ;

        if (right) 
     res1 = max(res1,1+right->tree_height ()) ;
        
        return res1 ;
    }

   int total_nodes() {
    int counter =1 ;
    if (left)
        counter +=  left->total_nodes();
    if (right) 
     counter +=  right->total_nodes() ;

     return counter ;
   }

   int total_leaves(){
   if (!left and !right) return 1 ;
   int counter =0; 
    if (left) counter +=left->total_leaves() ;
    if (right) counter +=right->total_leaves() ;
   return counter ;
   }

  bool is_exists (int value ){
    if (data == value )return true  ;
    if (left  )return left->is_exists(value) ;
    if (right )return  right->is_exists(value) ;
return false ;
  }

  bool is_perfect(){
    if ((left and !right) or (!left and right)) return false ;
    if (!left and !right) return true ;
    return left->is_perfect() and right->is_perfect() ; 
  
  }
 
 bool is_just_num() {
		// If it has no children, then it is just a number
		return !left && !right;
	}
 void print_inorder_expression() {
		if (left) {
			if (!left->is_just_num())
				cout << "(";
			left->print_inorder_expression();
			if (!left->is_just_num())
				cout << ")";
		}

		cout << data;

		if (right) {
			if (!right->is_just_num())
				cout << "(";
			right->print_inorder_expression();
			if (!right->is_just_num())
				cout << ")";
		}
	}

 void level_order_traversal() {
		queue<BinaryTree*> nodes_queue;
		nodes_queue.push(this);

		int level = 0;
		while (!nodes_queue.empty()) {
			int sz = nodes_queue.size();

			cout<<"Level "<<level<<": ";
			while(sz--) {
				BinaryTree*cur = nodes_queue.front();
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

 void level_order_traversal_sorted() {
		queue<BinaryTree*> nodes_queue;
		nodes_queue.push(this);
    priority_queue<int>pq ;
    pq.push(this->data );
		int level = 0;
		while (!nodes_queue.empty()) {
			int sz = nodes_queue.size();

			cout<<"Level "<<level<<": "; 
      while (!pq.empty()){
        cout << pq.top() <<  " " ;
        pq.pop() ;
      }
			while(sz--) {
				BinaryTree*cur = nodes_queue.front();
				nodes_queue.pop();
        //  cout << pq.top()<< " " ;
        //  pq.pop() ;

				// cout << cur->data << " ";
				if (cur->left){
					nodes_queue.push(cur->left);
          pq.push(cur->left->data);}
				if (cur->right){
					nodes_queue.push(cur->right);
			pq.push(cur->right->data);}}
     
			level++;
			cout << "\n";
		}
	}
  
 void print_level_order_traversal_recursive(int h){
  if (h==0) {cout << data <<  " " ; return ;}
  if (left) left->print_level_order_traversal_recursive(h-1) ;
  if (right) right->print_level_order_traversal_recursive(h-1) ; 
 }
 void level_order_traversal_recursive(){
  int h  = tree_height() ;
  for (int i=0 ;i<=h;i++) 
     { print_level_order_traversal_recursive(i) ;
     cout << endl ;}
 
 }

void level_order_traversal_spiral(){
  deque<BinaryTree*> nodes_queue;
  nodes_queue.push_front(this ) ;

  int level= 0;
  bool forward_level =true ;
  while (!nodes_queue.empty()) {
    int sz = nodes_queue.size() ;
    cout << "Level " << level << ':';
    while (sz-- ){
      BinaryTree*cur ;

      if (forward_level){
         cur = nodes_queue.front();
         nodes_queue.pop_front() ;
         if (cur->left) nodes_queue.push_back(cur->left) ;
         if (cur->right) nodes_queue.push_back(cur->right) ;
      } else {
        cur=nodes_queue.back() ;
        nodes_queue.pop_back();

        if (cur->right)
         nodes_queue.push_front(cur->right) ;
         if (cur->left) 
          nodes_queue.push_front(cur->left);
      }

      cout << cur->data << ' ' ;
      
    }
    level ++ ;
     cout << "\n" ;
  }
}

~BinaryTree(){
   cout << data << " deleted " << endl;
clear() ;
}

void clear() {
 if (left ){delete left; left = NULL ;} 
 if (right){delete right ;right = NULL ;}
}

void print_inorder_iterative(){
  stack<pair<BinaryTree*,bool>>st ;
  st.push({this,false});
  while(!st.empty()){
     pair<BinaryTree*,bool >cur = st.top();
     st.pop();
     if (cur.second == true) cout << cur.first->data << endl ;
     else {
      if (cur.first->right) st.push({cur.first->right,false}) ;
      st.push({cur.first ,true}) ;
      if (cur.first->left )st.push({cur.first->left,false}) ;
           }

  }
}

void traverse_left_boundry(){
  cout << data << " " ;
  if (left) left->traverse_left_boundry() ;
  else if (right) right->traverse_left_boundry() ;
  
}

void print_preorder_complete() {
		cout<<data<<" ";

		if (left)
			left->print_preorder_complete();
		else
			cout<<"-1 ";	// 2 null pointers

		if (right)
			right->print_preorder_complete();
		else
			cout<<"-1 ";	// 2 null pointers
	}

	string parenthesize() {
		string repr = "(" + to_string(data);
    
		if (left)
			repr += left->parenthesize();
		else
			repr += "()";	// null: no child

		if (right)
			repr += right->parenthesize();
		else
			repr += "()";	// null: no child
		repr += ")";

		return repr;
	}

	string parenthesize_canonical() {
		string repr = "(" + to_string(data);

		vector<string> v;

		if (left)
			v.push_back(left->parenthesize_canonical());
		else
			v.push_back("()");

		if (right)
			v.push_back(right->parenthesize_canonical());
		else
			v.push_back("()");

		sort(v.begin(), v.end());
		for (int i = 0; i < (int)v.size(); ++i)
			repr += v[i];

		repr += ")";

		return repr;
	}

};

int main() {
	BinaryTree tree(1);
     tree.add({4,9,10},{'L','L','L'});
     tree.add({4,9,11},{'L','L','R'});
     tree.add({4,5},{'L','R'});
     tree.add({6,7,8},{'R','R','R'});
     tree.add({6,3,2},{'R','L','L'});

  tree.level_order_traversal_sorted() ;
	return 0;
}

