#include <iostream>
#include <cassert>
#include <climits>

#include <vector>		// for debug
#include <algorithm>
#include <sstream>
using namespace std;

struct Node {
	int data { };
	Node* next { };
	Node* prev { };	 // Previous node!

	Node(int data) : data(data) {}

	void set(Node* next, Node* prev) {
		this->next = next;
		this->prev = prev;
	}

	~Node() {
		cout << "Destroy value: " << data << " at address " << this << "\n";
	}
};

class LinkedList {
private:
	Node *head { };
	Node *tail { };
	int length = 0;

	// let's maintain how many nodes

	vector<Node*> debug_data;	// add/remove nodes you use

	void debug_add_node(Node* node) {
		debug_data.push_back(node);
	}
	void debug_remove_node(Node* node) {
		auto it = std::find(debug_data.begin(), debug_data.end(), node);
		if (it == debug_data.end())
			cout << "Node does not exist\n";
		else
			debug_data.erase(it);
	}

public:

	// Below 2 deletes prevent copy and assign to avoid this mistake
	LinkedList() {
	}
	// LinkedList(const LinkedList&) = delete;
	// LinkedList &operator=(const LinkedList &another) = delete;

	void debug_print_address() {
		for (Node* cur = head; cur; cur = cur->next)
			cout << cur << "," << cur->data << "\t";
		cout << "\n";
	}

	void debug_print_node(Node* node, bool is_seperate = false) {
		if (is_seperate)
			cout << "Sep: ";
		if (node == nullptr) {
			cout << "nullptr\n";
			return;
		}

		if (node->prev == nullptr)
			cout << "X\t";
		else
			cout << node->prev->data << "\t";

		cout << " <= [" <<node->data << "]\t => \t";

		if (node->next == nullptr)
			cout << "X\t";
		else
			cout << node->next->data << "\t";

		if (node == head)
			cout << "head\n";
		else if (node == tail)
			cout << "tail\n";
		else
			cout << "\n";
	}
	void debug_print_list(string msg = "") {
		if (msg != "")
			cout << msg << "\n";
		for (int i = 0; i < (int) debug_data.size(); ++i)
			debug_print_node(debug_data[i]);
		cout << "************\n" << flush;
	}

	string debug_to_string() {
		if (length == 0)
			return "";
		ostringstream oss;
		for (Node* cur = head; cur; cur = cur->next) {
			oss << cur->data;
			if (cur->next)
				oss << " ";
		}
		return oss.str();
	}

	void debug_verify_data_integrity() {
		if (length == 0) {
			assert(head == nullptr);
			assert(tail == nullptr);
		} else {
			assert(head != nullptr);
			assert(tail != nullptr);
			if (length == 1)
				assert(head == tail);
			else
				assert(head != tail);
			assert(!head->prev);
			assert(!tail->next);
		}
		int len = 0;
		for (Node* cur = head; cur; cur = cur->next, len++) {
			if (len == length-1)	// make sure we end at tail
				assert(cur == tail);
		}

		assert(length == len);
		assert(length == (int )debug_data.size());

		len = 0;
		for (Node* cur = tail; cur; cur = cur->prev, len++) {
			if (len == length-1)	// make sure we end at head
				assert(cur == head);
		}
		cout << "\n";
	}
	////////////////////////////////////////////////////////////

	void print() {
		for (Node* cur = head; cur; cur = cur->next)
			cout << cur->data << " ";
		cout << "\n";
	}

	// These 2 simple functions just to not forget changing the vector and length
	void delete_node(Node* node) {
		debug_remove_node(node);
		--length;
		delete node;
	}

	void add_node(Node* node) {
		debug_add_node(node);
		++length;
	}

	void link(Node* first, Node*second) {
		if(first)
			first->next = second;
		if(second)
			second->prev = first;
	}

	void insert_end(int value) {
		Node* item = new Node(value);
		add_node(item);

		if (!head)
			head = tail = item;
		else {
			link(tail, item);
			tail = item;
		}
		debug_verify_data_integrity();
	}

	void insert_front(int value) {
		Node* item = new Node(value);
		add_node(item);

		if (!head)
			head = tail = item;
		else {
			link(item, head);
			head = item;
		}
		debug_verify_data_integrity();
	}

	void print_reversed()  {
		for (Node* cur = tail; cur; cur = cur->prev)
			cout << cur->data << " ";
		cout << "\n";
	}

	void delete_front() {
		if(!head)
			return;
		Node* cur = head->next;
		delete_node(head);
		head = cur;

		// Integrity change
		if(head)
			head->prev = nullptr;
		else if(!length)
			tail = nullptr;

		debug_verify_data_integrity();
	}

	void delete_end() {
		if(!head)
			return;
		Node* cur = tail->prev;
		delete_node(tail);
		tail = cur;

		// Integrity change
		if(tail)
			tail->next = nullptr;
		else if(!length)
			head = nullptr;

		debug_verify_data_integrity();
	}

	Node* delete_and_link(Node* cur) {
		// remove this node, but connect its neighbors
		Node* ret = cur->prev;
		link(cur->prev, cur->next);
		delete_node(cur);

		return ret;
	}
     
    void delete_all_nodes_with_key(int key){
        if (!head) return ;
        else if (head->data==key and length ==1 )delete_front() ;
        else {
        Node*cur =head ;
       for ( ; cur ;){
        if (cur->data == key){
            if (!cur->prev){delete_front() ;cur = head ;continue; }
             else { cur = delete_and_link(cur);
            if (!cur->next  ){tail = cur ; break;}

             }
        }
        cur=cur->next ;
       }
         }
    } // another method
    void delete_all_nodes_with_keyV2(int value) {
		if (!length)
			return;

		insert_front(-value);	// insert dummy. assume -value no overflow

		for (Node *cur = head; cur;) {
			if (cur->data == value) {
				cur = delete_and_link(cur);
				if(!cur->next)
					tail = cur;
			}
			else
				cur = cur->next;
		}

		delete_front();

		debug_verify_data_integrity();
	}

    void delete_even_positions() {
        if (length<=1) return ;
        else {
            Node*cur = head->next ;
			while (cur) 
			{
				if (!cur->next) {delete_end() ; break;}
				/* code */
				Node*temp = nullptr ;
				if (cur->next->next) temp = cur->next->next ;

				 delete_and_link(cur) ;
				cur = temp ;
			}

			if (length == 1) head= tail ;
        }
    }
	void delete_odd_positions(){
		if (!length)return;
		if (length==1) delete_front() ;
		else {
			Node*cur=head ;
			head=head->next ;
			while (cur ){
				Node*temp =nullptr ;
				if (!cur->next){delete_end(); break;}
			    
				if (cur->next->next)temp= cur->next->next;

				delete_and_link(cur) ;
				cur =temp ;
			}
		}
	}

	void delete_node_with_key(int value) {
		if (!length)
			return;
		if (head->data == value)
			delete_front();
		else {
			for (Node *cur = head; cur; cur = cur->next) {
				if (cur->data == value) {
					cur = delete_and_link(cur);
					if (!cur->next)	// we removed last node!
						tail = cur;
					break;
				}
			}
		}
		debug_verify_data_integrity();
	}

	void embed_after(Node* node_before, int value) {
		// Add a node with value between node and its next
		Node* middle= new Node(value);
		++length;
		debug_add_node(middle);

		Node* node_after = node_before->next;
		link(node_before, middle);
		link(middle, node_after);
	}

	void insert_sorted(int value) {		// O(n) time - O(1) memory
		// 3 special cases for simplicity
		if (!length || value <= head->data)
			insert_front(value);
		else if (tail->data <= value)
			insert_end(value);
		else {
			// Find the node I am less than. Then I am before it
			for (Node *cur = head; cur; cur = cur->next) {
				if (value <= cur->data) {
					embed_after(cur->prev, value);
					break;
				}
			}
		}
		debug_verify_data_integrity();

		// This idea is used in Insertion Sort Algorithm
	}

	bool is_palindrome(){
		if (length<=1) return true ;
		else {
			Node*cur_head = head ;
			Node* cur_tail =tail ;
			while (cur_head != cur_tail){
				if (cur_head->data !=cur_tail->data) return false ;
				cur_head =cur_head->next ;
				cur_tail= cur_tail->prev;
			}
			return true ;
		}
	}

	Node*Find_the_middleV1(){
		if (!head or head == tail) return head ;
		else {
			Node*cur_head = head ;
			Node*cur_tail =tail ;
			while (cur_head != cur_tail and cur_head->next !=cur_tail)
			{
				cur_head = cur_head->next;
				cur_tail = cur_tail->prev ;
			}
			return cur_head;
		}
	}
	Node*Find_the_middleV2(){ 
		if (!head or head == tail) return head ;
		else {
			Node*cur_head =head ;
			Node*doubly_node = head->next->next ;
			while(cur_head){
				if (!doubly_node or !doubly_node->next or !doubly_node->next->next) return cur_head->next ;
         doubly_node = doubly_node->next->next;
		 cur_head=cur_head->next;
			} 
		}
	}
 

    Node* get_nth(int n){
		int cnt = 0;
		for (Node*cur= head ;cur ; cur=cur->next)
		   if (++cnt==n) return cur ;

		   return nullptr ;
	}
	void Swap_forward_with_backward(int k){
		if (k>length) return ;
       int kth_back = length - k +1 ;
	   if (k==kth_back)return ; // same node 
	   if (k>kth_back)swap(k,kth_back) ;

	   Node*first = get_nth(k) ;
	   Node*last = get_nth(kth_back) ;

       Node*first_prev = first->prev ;
	   Node*first_next = first->next ;

	   Node*last_prev = last ->prev ;
	   Node*last_next =  last->next;

	   if (k+1 == kth_back){ // consecutive (neighbours)
           link(first_prev,last) ;
		   link(last,first) ;
		   link(first,last_next);
	   }else {
		link(first_prev,last) ;
		link(last,first_next) ;
		link(last_prev,first) ;
		link(first,last_next);
	   }
	   if (k==1) 
	    swap(head,tail) ;

	}
	Node* get_nth_back(int n) {
		int cnt = 0;
		for (Node* cur = tail; cur; cur = cur->prev)
			if (++cnt == n)
				return cur;

		return nullptr;
	}

	void swap_forward_with_backward_mine(int k){
		
	Node* first = get_nth(k);
		Node* last = get_nth_back(k);

		if (first == last)
			return;	// same node or 2 null pointers

		if(first->prev == last)	// first is after it with 1 step exactly
			swap(first, last);	// swap to do same handling for neighbor nodes

		Node* first_prev = first->prev;
		Node* first_next = first->next;

		Node* last_prev = last->prev;
		Node* last_next = last->next;

		if (first->next == last) {	// Connectives
			link(first_prev, last);
			link(last, first);
			link(first, last_next);
		} else {
			link(first_prev, last);
			link(last, first_next);

			link(last_prev, first);
			link(first, last_next);
		}
		if (k == 1)
			swap(head, tail);
	   }

	   void reverse(){
		if (length<=1) return;
		int k=1 ;
		while(k<=length/2){
			Swap_forward_with_backward(k);
			k++;
		}
	   }
	   void reverse_V2() {
		if (length <= 1)
			return;

		Node* first = head, *second = head->next;
		while (second) {
			// Take copy of next move data
			Node* first_ = second, *second_ = second->next;
			link(second, first);				// reverse
			first = first_, second = second_;	// move
		}
		swap(head, tail);
		head->prev = tail->next = nullptr;

		debug_verify_data_integrity();
	}


	LinkedList merge_two_sorted_lists(LinkedList another){
 
		Node*p1 = head ,*p2=another.head;
		LinkedList new_list ;
		while(p1 and p2){
			if (p1->data < p2->data){
              new_list.insert_end(p1->data) ;
			p1=p1->next;
			}else {
              new_list.insert_end(p2->data) ;
 p2=p2->next;
			}
		}
		while(p1) {
			new_list.insert_end(p1->data) ;
		p1=p1->next;
		}
		while(p2) {
			new_list.insert_end(p2->data) ;
		p2=p2->next;
		}
	
		return new_list;
		


	}
	

};

void test1() {
	cout << "\n\ntest1\n";
	LinkedList list;

	list.insert_end(3);
	list.insert_end(4);
	list.insert_end(5);
	list.insert_end(6);
	list.insert_end(7);
	
   LinkedList list2 ;
   list2.insert_end(1);
   list2.insert_end(2);
   list2.insert_end(8);
   list2.insert_end(9);
   list2.insert_end(10);
   list2.insert_end(11);
	// list.insert_end(8);
   list.print();
   list2.print();
   LinkedList new_list=list.merge_two_sorted_lists(list2);
 cout << "printing new list\n";
   new_list.print();
       
	
	list.debug_print_list("********");
}



int main() {
	test1();

	// must see it, otherwise RTE
	cout << "\n\nNO RTE\n";

	return 0;
}

