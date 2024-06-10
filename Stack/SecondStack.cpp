#include <iostream>
#include <cassert>
using namespace std;

class Stack {
private:
	int size { };
	int added_elements { };
	int* array { };
public:
	Stack(int size) :
			size(size), added_elements(0) {
		array = new int[size];
	}

	~Stack() {
		delete[] array;
	}

	bool push(int x) {
        if (isFull()) return false ;
        if (isEmpty()) {array[0]=x;added_elements++;return true ;}
	    for (int i= added_elements ;i>=0 ;i--) array[i] =array[i-1];
      array[0]=x ;
      added_elements++;
    }

	int pop() {
           if (isEmpty()) return -1 ;
         int x = array[0] ;
        for (int i=0 ;i<added_elements-1 ;i++) array[i]= array[i+1];
	        added_elements--;
            return x ;
    }

	int peek() {
		assert(!isEmpty());
          return  array[0] ;
  	}

	int isFull() {
		return added_elements == size ;
	}

	int isEmpty() {
		return added_elements == 0;
	}

	void display() {
		for (int i = 0; i<added_elements; i++)
			cout << array[i] << " ";
		cout << "\n";
	}
};

int main() {


	Stack stk(3);
	stk.push(10);
	stk.push(20);
	stk.push(30);
cout << "we are here ";
	if (!stk.isFull())
		stk.push(50);
	else
		cout << "Full Stack\n";
	stk.display();	// 30 20 10
	cout << stk.peek() << "\n";	// 30

	while (!stk.isEmpty()) {
		cout << stk.peek() << " ";
		stk.pop();
	} // 30 20 10

	return 0;
}
