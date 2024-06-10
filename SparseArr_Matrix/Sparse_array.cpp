#include <iostream>
#include <cassert>
#include <climits>

#include <vector>		// for debug
#include <algorithm>
#include <sstream>
using namespace std;

struct Node {
	int data { };
	int index {};
	Node* next { };
	Node* prev { };	 // Previous node!

	Node(int data , int index) : data(data),index(index) {}

	void set(Node* next, Node* prev) {
		this->next = next;
		this->prev = prev;
	}

	~Node() {
		cout << "Destroy value: " << data << " at address " << this << "\n";
	}
};

class ArrayLinkedList {
private:
	Node *head { };
	Node *tail { };
	int length = 0;

	// let's maintain how many nodes

	

public:

	// Below 2 deletes prevent copy and assign to avoid this mistake
	ArrayLinkedList() {
	}
    ArrayLinkedList(int length):length(length){

	}
	ArrayLinkedList(const ArrayLinkedList&) = delete;
	ArrayLinkedList &operator=(const ArrayLinkedList &another) = delete;

     void set_value(int data,int index){
       insert_sorted(index,data) ;
	 }
	void insert_sorted(int index,int data) {		// O(n) time - O(1) memory
		if (  !head || index <= head->index )
			insert_front(data ,index);
		else if (tail->index <= index)
			insert_end(data,index);
		else {
			// Find the node I am less than. Then I am before it
			for (Node *cur = head; cur; cur = cur->next) {
				if (index <= cur->index) {
					embed_after(cur->prev, index , data);
					break;
				}
			}
		}
	// This idea is used in Insertion Sort Algorithm
	}
	void insert_end(int value,int index) {
		Node* item = new Node(value,index);

		if (!head)
			head = tail = item;
		else {
			link(tail, item);
			tail = item;
		}
	}

	void insert_front(int value,int index) {
		cout << "this is ";
		Node* item = new Node(value,index);

		if (!head)
			head = tail = item;
		else {
			link(item, head);
			head = item;
		}
	}
	void embed_after(Node* node_before, int index , int data) {
		// Add a node with value between node and its next
		Node* middle= new Node(data ,index);
	

		Node* node_after = node_before->next;
		link(node_before, middle);
		link(middle, node_after);
	}
	void link(Node* first, Node*second) {
		if(first)
			first->next = second;
		if(second)
			second->prev = first;
	}

	void set_position(int index, int data) {
		for(Node*cur = head ; cur ; cur=cur->next){
			if (cur->index == index) {cur->data =data;break;}
		}
	} 
	int get_position(int index) {
		for (Node*cur = head ;cur ;cur=cur->next) {
			if (cur->index == index) return cur->data ;
		}
		return -1 ;
	}


    void print(){
		
		Node*cur = head ;
		for (int i = 0 ;i<length;i++){
		  if (!cur or cur->index!=i) cout << 0  << ' ' ;  	       
	      else if (cur->index == i) {cout << cur->data << ' ';cur=cur->next;}
		}
	}
	
		
	void print_non_zero() {
		for (Node* cur = head; cur; cur = cur->next)
			cout << cur->data << " ";
		cout << "\n";
	}

	

};

void test1() {
	ArrayLinkedList list1(10) ;
	list1.set_value(5,5);
	list1.set_value(20,2);
	list1.set_value(70,7);
	list1.set_value(40,4);
  list1.print() ; 
  cout << endl; 
  list1.print_non_zero() ;
}



int main() {
	test1();

	// must see it, otherwise RTE
	cout << "\n\nNO RTE\n";

	return 0;
}

