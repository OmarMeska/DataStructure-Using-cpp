#include <iostream>
#include <cassert>
using namespace std;

class Vector {
private:
	int *arr { nullptr };
	int size { 0 };			// user size
	int capacity { };		// actual size

	void expand_capacity() {
		// Double the actual array size
		capacity *= 2;
		cout << "Expand capacity to "
				<< capacity << "\n";
		int *arr2 = new int[capacity] { };
		for (int i = 0; i < size; ++i)
			arr2[i] = arr[i];	// copy data

		swap(arr, arr2);
		delete[] arr2;
	}

public:


	Vector(int size) :
			size(size) {
		if (size < 0)
			size = 1;
		capacity = size + 10;
		// The actual size array will
		// be bigger than needed
		arr = new int[capacity] { };
	}

	~Vector() {
		delete[] arr;
		arr = nullptr;
	}

	int get_size() {
		return size;
	}

	int get(int idx) {
		assert(0 <= idx && idx < size);
		return arr[idx];
	}

	void set(int idx, int val) {
		assert(0 <= idx && idx < size);
		arr[idx] = val;
	}

	void print() {
		for (int i = 0; i < size; ++i)
			cout << arr[i] << " ";
		cout << "\n";
	}

	int find(int value) {
		for (int i = 0; i < size; ++i)
			if (arr[i] == value)
				return i;
		return -1;	// -1 for NOT found
	}
	int find_transposition(int value) {
		for (int i=0 ;i<size ;i++){
			if (arr[i] == value){
                   if (i!=0){ swap(arr[i],arr[i-1]);return i-1 ;}				
			       return i ;
			}
		}
	}

	int get_front() {
		return arr[0];
	}

	int get_back() {
		return arr[size - 1];
	}

	void push_back(int value) {
		// we can't add any more
		if (size == capacity)
			expand_capacity();
		arr[size++] = value;
	}
	void insert(int idx, int value) {
		assert(0 <= idx && idx < size);

		// we can't add any more
		if (size == capacity)
			expand_capacity();

		// Shift all the data to right first

		for(int p = size-1; p >= idx; --p)
			arr[p+1] = arr[p];

		arr[idx] = value;
		++size;

		// Common mistake to iterate from begin to end
		// the whole array right array will be arr[idx]
		//for (int p = idx; p < size; ++p)
	}
	int pop(int idx){
		int popped_element= arr[idx] ;
		for (int i=idx ;i<size;i++) {
			arr[i]=arr[i+1 ] ;

		}
		size -- ;
		return popped_element ;
	}



	void Right_rotation(){
		int last_element = arr[size-1] ;

		for (int i=size-1 ;i>=0 ;i--){
			arr[i] =arr[i-1] ;
		}
		arr[0] =last_element ;
	}
	void Right_rotation_with_steps (int steps) {
		steps = steps%size ;
		for (int i= 0;i<steps;i++)
		   Right_rotation() ;

	}
	void Left_rotation(){
		int first_element = arr[0] ;

		for (int i=0 ;i<size ;i++){
			arr[i] =arr[i+1] ;
		}
		arr[size-1] =first_element ;
	}
};

int main() {

	int n = 5;
	Vector v(n);
	for (int i = 0; i < n; ++i)
		v.set(i, i);

	

	return 0;
}
