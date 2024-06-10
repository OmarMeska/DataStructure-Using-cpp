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
	Node(int data) : data(data) {}
	~Node() {
		cout << "Destroy value: " << data <<" at address "<< this<< "\n";
	}
};

class LinkedList {
private:
	Node *head { };
	Node *tail { };
	int length = 0;	// let's maintain how many nodes

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
	LinkedList(const LinkedList&) = delete;
	LinkedList &operator=(const LinkedList &another) = delete;

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
		cout << node->data << " ";
		if (node->next == nullptr)
			cout << "X ";
		else
			cout << node->next->data << " ";

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
		cout << "************\n"<<flush;
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
			assert(!tail->next);
		}
		int len = 0;
		Node* prev = nullptr;
		for (Node* cur = head; cur; prev = cur, cur = cur->next, len++)
			assert(len < 10000);	// Consider infinite cycle?
		assert(tail == prev);
		assert(length == len);
		assert(length == (int)debug_data.size());
	}

	////////////////////////////////////////////////////////////
 
    void delete_even_positions() {		// O(n) time - O(1) memory
		if (length <= 1)
			return;
		// maintain previous and delete its next (even order)
		for(Node *cur = head->next, *prv = head;cur;) {
			delete_next_node(prv);	// prev is odd, prev-next is even
			if (!prv->next)	// tail
				break;
			cur = prv->next->next;
			prv = prv->next;
		}
		debug_verify_data_integrity();
	}
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

	void insert_end(int value) {
		Node* item = new Node(value);
		add_node(item);

		if (!head)
			head = tail = item;
		else
			tail->next = item, tail = item;
	}

	////////////////////////////////////////////////////////////
	void delete_first() {
		if (head) {
			//Move to next in the list
			// and remove current
			Node* cur = head;
			head = head->next;

			delete_node(cur);

			if (!head)	// data integrity!
				tail = nullptr;
		}
		debug_verify_data_integrity();
	}
    void swap_pairs() {
        assert(length >=2 ) ;
        Node*first = head ;
        Node*second = head->next ;
        while (first and second)
        {
            swap (first->data , second->data) ;
         if (second->next and second->next->next) {   first= second->next ;
               second= second->next->next;}
               else break;
        }
        
    }

    void reverse() {		// O(n) time - O(1) memory
		if (length <= 1)
			return;

		tail = head;
		Node *prv = head;
		head = head->next;
		while (head) {
			// store & reverse link
			Node* next = head->next;
			head->next = prv;

			// move step
			prv = head;
			head = next;
		}
		// Finalize head and tail
		head = prv;
		tail->next = nullptr;

		debug_verify_data_integrity();
	}

    void embed_after(Node* node, int value) {
		// Add a node with value between node and its next
		Node* item = new Node(value);
		++length;
		debug_add_node(item);

		item->next = node->next;
		node->next = item;
	}

	void insert_sorted(int value) {		// O(n) time - O(1) memory
		// 3 special cases for simplicity
		if (!length || value <= head->data)
			insert_front(value);
		else if (tail->data <= value)
			insert_end(value);
		else {
			// Find the node I am less than. Then I am before it
			for (Node *cur = head, *prv = nullptr; cur; prv = cur, cur = cur->next) {
				if (value <= cur->data) {
					embed_after(prv, value);
					break;
				}
			}
		}
		debug_verify_data_integrity();

		// This idea is used in Insertion Sort Algorithm
	}
    

	// Bug fixing for this function
	void delete_next_node(Node* node) {
		Node* to_delete = node->next;
		bool is_tail = to_delete == tail;
		// node->next in middle to delete
		node->next = node->next->next;
		delete_node(to_delete);

		if(is_tail)
			tail = node;
	}
    void insert_front(int value) {
		Node* item = new Node(value);
		++length;
		debug_add_node(item);

		item->next = head;
		head = item;

		if(length == 1)
			tail = head;

		debug_verify_data_integrity();
	}

	void delete_node_with_key(int value) {	// O(n) time - O(1) memory
		if (!length)
			cout << "Empty list!\n";
		else if (head->data == value)
			delete_first();
		else {
			for (Node *cur = head, *prv = nullptr; cur; prv = cur, cur = cur->next) {
				if(cur->data == value) {
					delete_next_node(prv);	// connect prv with after
					break;
				}
			}
			cout<<"Value not found!\n";
		}
		debug_verify_data_integrity();
	}

   Node* get_previous(Node* target) {		// O(n) time - O(1) memory
		for (Node *cur = head, *prv = nullptr; cur; prv = cur, cur = cur->next) {
			if (cur == target)	// memory wise
				return prv;
		}
		return nullptr;	// still more steps needed - NOT found
	}

    void left_rotate (int k) {
         if (!head or head == tail) return; 
          k = k%length ;
        //   cout << length << '\n' ;

          while (k--) {
            Node * prev = get_previous(tail) ;
             tail->next = head ;
             head = tail ;
            prev->next =nullptr ;
            tail =prev ;
          }
    }

	void swap_head_tail() {		// O(n) time - O(1) memory
		// 0 or 1 node. We can use length also if(length <= 1)
		if (!head || !head->next)
			return;

		if (length == 2) {	// Fix
			swap(tail, head);
			head->next = tail;
			tail->next = nullptr;
			return;
		}

		Node* prv = get_previous(tail);	// node before tail

		// Let's make current tail as head
		// Link tail to the 2nd node
		tail->next = head->next;

		// Let's make current head as tail
		// Link tail's previous to head
		prv->next = head;
		head->next = nullptr;

		swap(tail, head);	// Set new head and tail

		debug_verify_data_integrity();
	}

    void remove_duplicates (){
        int arr[100010]{} ;
        if (!head or head == tail) return ;
        Node*cur = head ;
        Node*prev = nullptr ;
        while (cur ) {
            //  cout << cur->data << " " << arr[cur->data] << '\n' ;
            if (arr[cur->data]){
                prev->next =cur->next ;
                 auto temp = cur->next ;
                 delete cur ;
                 cur = temp ;
                 continue; 
            }
            arr[cur->data]++ ;
        prev = cur ;
        cur = cur->next ;
        }
    }

   	void delete_last_occurrence(int target) {		// O(n) time - O(1) memory
		if (!length)
			return;

		Node* delete_my_next_node = nullptr;
		bool is_found = false;

		// Find the last one and remove it

		for (Node *cur = head, *prv = nullptr; cur; prv = cur, cur = cur->next) {
			if (cur->data == target)
				is_found = true, delete_my_next_node = prv;
		}
		if (is_found) {
			if (delete_my_next_node)
				delete_next_node(delete_my_next_node);
			else
				// if prv is null, then found at head
				delete_first();
		}
		debug_verify_data_integrity();
	}
   void move_node_to_back(Node*prev) {
    auto node = prev->next ;
    prev->next = node->next ;
    node->next = nullptr ;
    tail->next = node ;
    tail =node ;
   }
   void move_back(int value){
    if (!head) return ;

       for (Node*cur=head,*prev=nullptr ;cur; ) {
            if (cur->data ==value) {
                 if (!prev) {
                    cout << "heare\n";
                    auto temp = head->next ;
                    head->next = nullptr ;
                 tail->next = head ;
                 tail= head ;
                 head= temp ;
                 cur = head ;
                 continue;

                 }else move_node_to_back(prev) ;
            }
            prev=cur,cur=cur->next;
       }
   }
   int Max(Node*head = nullptr,bool is_first =true){

  if (is_first) {
    return this->Max(this->head ,false) ;
  
  if (!head->next) return head->data ;

  return max (head->data , this->Max(head->next ,false))
 ;   }
 }

void odd_pos_even_pos() {		// O(n) time - O(1) memory
		if (length <= 2)
			return;

		Node* first_even = head->next;
		Node* cur_odd = head;

		while (cur_odd->next && cur_odd->next->next) {
			Node* next_even = cur_odd->next;
			// connect odd with odd and even with even
			cur_odd->next = cur_odd->next->next;
			next_even->next = next_even->next->next;
			cur_odd = cur_odd->next;
			// for odd length, tail is changed to last even node
			if (length % 2 == 1)
				tail = next_even;
		}
		// connect last odd with the first even
		cur_odd->next = first_even;

		debug_verify_data_integrity();
	}

	void insert_after(Node *src, Node* target) {
		// Given node src, link target after it with my list before/after
		assert(src && target);
		target->next = src->next;
		src->next = target;
		debug_add_node(target);
		++length;
	}

	void insert_alternate(LinkedList &another) {		// O(n) time - O(1) memory
		if (!another.length)
			return;

		if (!length) {
			// copy data
			head = another.head;
			tail = another.tail;
			length = another.length;
			debug_data = another.debug_data;

		} else {
			// Iterate one by one, add node in right place
			// If this ended first, then we link the remain in this list
			Node* cur2 = another.head;
			for (Node* cur1 = head; cur1 && cur2;) {
				Node* cur2_next_temp = cur2->next;
				insert_after(cur1, cur2);
				another.length--;
				cur2 = cur2_next_temp;

				if (cur1 == tail) {
					tail = another.tail;
					cur1->next->next = cur2;
					length += another.length;
					break;

					// there is a missing thing here
					// we need to add remaining nodes to debug data
					// let's skip
				}
				cur1 = cur1->next->next;
			}
		}

		another.head = another.tail = nullptr;
		another.length = 0;
		another.debug_data.clear();
		debug_verify_data_integrity();
	}
};

void test1() {
	cout << "\n\ntest1\n";
	LinkedList list;

	list.insert_front(1);
	list.insert_front(8);
	list.insert_front(2);
	list.insert_front(1);
	list.insert_front(6);
	list.insert_front(1);
    
	list.print();
    cout << list.Max() ;
	// list.print();
	// some actions


	
	list.debug_print_list("********");
}

void test2() {
	cout << "\n\ntest2\n";
	LinkedList list;

	list.insert_end(1);
	list.insert_end(2);
	list.delete_node_with_key(10);
	list.delete_node_with_key(1);
	list.delete_node_with_key(2);

	// some actions
	list.print();

	string expected = "";
	string result = list.debug_to_string();
	if (expected != result) {
		cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
		assert(false);
	}
	list.debug_print_list("********");
}

void test3() {
	cout << "\n\ntest3\n";
	LinkedList list;

	list.insert_end(1);
	list.insert_end(2);
	list.insert_end(3);
	list.insert_end(4);
	list.delete_node_with_key(4);

	// some actions
	list.print();

	string expected = "1 2 3";
	string result = list.debug_to_string();
	if (expected != result) {
		cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
		assert(false);
	}
	list.debug_print_list("********");
}

int main() {
	test1();
	// test2();
	// test3();

	// must see it, otherwise RTE
	cout << "\n\nNO RTE\n";

	return 0;
}

