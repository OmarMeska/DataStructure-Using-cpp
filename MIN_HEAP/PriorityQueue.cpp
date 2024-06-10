#include<vector>
#include<iostream>
#include<cassert>
using namespace std;

class MaxHeap {
private:
	int *array { };
    int *array_values {} ;
	int size { };
	int capacity { 1000 };


	int left(int node) {
		int p = 2 * node + 1;
		if (p >= size)
			return -1;
		return p;
	}
	int right(int node) {
		int p = 2 * node + 2;
		return p >= size ? -1 : p;
	}
	int parent(int node) {
		return node == 0 ? -1 : (node - 1) / 2;
	}

	void heapify_up(int child_pos) {
		// stop when parent is smaller (or no parent)
		int par_pos = parent(child_pos);
		if (child_pos == 0 || array[par_pos] > array[child_pos])
			return;

		swap(array[child_pos], array[par_pos]);
        swap(array_values[child_pos],array_values[par_pos]);
		heapify_up(par_pos);
	}

	void heapify_down(int parent_pos) {	// O(logn)
		int child_pos = left(parent_pos);
		int right_child = right(parent_pos);

		if (child_pos == -1) // no children
			return;
		// is right smaller than left?
		if (right_child != -1 && array[right_child] > array[child_pos])
			child_pos = right_child;

		if (array[parent_pos] < array[child_pos]) {
			swap(array[parent_pos], array[child_pos]);
			swap(array_values[parent_pos], array_values[child_pos]);

			heapify_down(child_pos);
		}
	}

	void heapify() {	// O(n)
		for (int i = size / 2 - 1; i >= 0; --i)
			heapify_down(i);
	}

public:
	MaxHeap() {
		array = new int[capacity] { };
        array_values = new int[capacity]{};
		size = 0;
	}

	MaxHeap(const vector<int> &v) {
		assert((int )v.size() <= capacity);
		array = new int[capacity] { };
		size = v.size();

		for (int i = 0; i < (int) v.size(); ++i)
			array[i] = v[i];

		heapify();
	}

	~MaxHeap() {
        delete []array_values;
		delete[] array;
        array_values = nullptr ;
		array = nullptr;
	}

	void push(int key , int val) {
		assert(size + 1 <= capacity);
		array[size] = key;
		array_values[size++]= val ;
        heapify_up(size - 1);
	}

	void pop() {
		assert(!isempty());
        int pos= --size ;
		array[0] = array[pos];
        array_values[0] = array_values [ pos];
		heapify_down(0);
	}

	int top() {
		assert(!isempty());
		return array_values[0];
	}

	bool isempty() {
		return size == 0;
	}
};

class PriorityQueue { 
  private :
   MaxHeap maxHeap;
 
 public :
 PriorityQueue():maxHeap(){

 }
 void enqueue(int val, int priority){
   maxHeap.push(priority,val) ;
 }

 int dequeue(){
    int x = maxHeap.top() ;
    maxHeap.pop() ;
    return x ;
 }

 bool isempty() {
    return maxHeap.isempty() ;
 }
};


int main() {
 PriorityQueue tasks ;
 tasks.enqueue(11,1) ;
 tasks.enqueue(33,3) ;
 tasks.enqueue(22,2) ;
 tasks.enqueue(31,3) ;
 tasks.enqueue(77,7) ;
 
 cout << tasks.dequeue() << endl ;
 cout << tasks.dequeue() << endl ;
  cout << endl << endl ;

 tasks.enqueue(14,1) ;
 tasks.enqueue(26,2) ;
 tasks.enqueue(36,3) ;
 tasks.enqueue(41,4) ;
 tasks.enqueue(55,5) ;

  cout << tasks.dequeue() << endl;
  cout << tasks.dequeue() << endl;
  cout << endl << endl ;
  
 tasks.enqueue(32,3) ;
 tasks.enqueue(58,5) ;

  while (!tasks.isempty())
   cout << tasks.dequeue() << endl;
	return 0;

}
