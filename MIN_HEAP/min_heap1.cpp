#include<vector>
#include<iostream>
#include<cassert>
using namespace std;

class MinHeap {
private:
	int *array { };
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
		if (child_pos == 0 || array[par_pos] < array[child_pos])
			return;

		swap(array[child_pos], array[par_pos]);
		heapify_up(par_pos);
	}

	void heapify_down(int parent_pos) {	// O(logn)
		int child_pos = left(parent_pos);
		int right_child = right(parent_pos);

		if (child_pos == -1) // no children
			return;
		// is right smaller than left?
		if (right_child != -1 && array[right_child] < array[child_pos])
			child_pos = right_child;

		if (array[parent_pos] > array[child_pos]) {
			swap(array[parent_pos], array[child_pos]);
			heapify_down(child_pos);
		}
	}

	void heapify() {	// O(n)
		for (int i = size / 2 - 1; i >= 0; --i)
			heapify_down(i);
	}

public:
	MinHeap() {
		array = new int[capacity] { };
		size = 0;
	}

	MinHeap(const vector<int> &v) {
		assert((int )v.size() <= capacity);
		array = new int[capacity] { };
		size = v.size();

		for (int i = 0; i < (int) v.size(); ++i)
			array[i] = v[i];

		heapify();
	}

	~MinHeap() {
		delete[] array;
		array = nullptr;
	}

	void push(int key) {
		assert(size + 1 <= capacity);
		array[size++] = key;
		heapify_up(size - 1);
	}

	void pop() {
		assert(!isempty());
		array[0] = array[--size];
		heapify_down(0);
	}

	int top() {
		assert(!isempty());
		return array[0];
	}

	bool isempty() {
		return size == 0;
	}

    void print_less_than(int val ,int parent_pos =0){
        if (parent_pos == -1 or array[parent_pos]>=val) return ;
        cout << array[parent_pos] << " " ;
        print_less_than(val,left(parent_pos)) ;
        print_less_than(val,right(parent_pos)) ;
    }
    bool is_heap(int parent_index){
       	if (parent_index == -1)
			return true;

		int left_child = left(parent_index);
		int right_child = right(parent_index);

		if (left_child != -1 && array[parent_index] > array[left_child])
			return false;

		if (right_child != -1 && array[parent_index] > array[right_child])
			return false;

		return is_heap(left_child) && is_heap(right_child);
  }
    bool is_heap_array(int *p ,int n){
        int * old_arr =array ;
        int old_size = size ;
           
           array = p ;
           size = n ;
        bool result = is_heap(0) ;
   
        array =old_arr ;
        size = old_size ;

        return result;

    }
    
    void heap_sort(int *p, int n) {	// O(nlogn)
		if (n <= 1)
			return;

		int* old_arr = array;
		int old_size = size;

		size = n;
		array = p;

		heapify();	// O(n)

		while (size--) {	// O(nlogn)
			swap(array[0], array[size]);
			heapify_down(0);
		}

		// reverse
		for (int i = 0; i < n / 2; ++i)
			swap(array[i], array[n-i-1]);

		size = old_size;
		array = old_arr;
	}

};

void creat_heap_nlogn() {
	MinHeap heap;

	vector<int> v { 2, 17, 22, 10, 8, 37,
		14, 19, 7, 6, 5, 12, 25, 30 };

	for (int i = 0; i < v.size(); ++i)
		heap.push(v[i]);

	while (!heap.isempty()) {
		cout << heap.top() << " ";
		heap.pop();
    }

	// 2 5 6 7 8 10 12 14 17 19 22 25 30 37
}

void creat_heap_n() {
	vector<int> v { 2, 17, 22, 10, 8, 37, 14, 19, 7, 6, 5, 12, 25, 30 };
	MinHeap heap(v);
    int *p = new int [13]{2,12,7,6,22,14,19,10,17,8,37,25,30} ;
    
    cout << heap.is_heap_array(p,13) ;
       cout << endl ;
      heap.print_less_than(10) ;
       cout << endl ;
	while (!heap.isempty()) {
		cout << heap.top() << " ";
		heap.pop();
	}
}

int main() {
	creat_heap_n();

	return 0;

}
