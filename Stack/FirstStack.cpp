#include <iostream>
#include <cassert>
using namespace std;

class Stack {
private:
	int size { };
	int top { };
	int* array { };
public:
	Stack(int size) :
			size(size), top(-1) {
		array = new int[size];
	}

	~Stack() {
		delete[] array;
	}

	void push(int x) {
		assert(!isFull());
		array[++top] = x;
	}

	int pop() {
		assert(!isEmpty());
		return array[top--];
	}

	int peek() {
		assert(!isEmpty());
		return array[top];
	}

	int isFull() {
		return top == size - 1;
	}

	int isEmpty() {
		return top == -1;
	}

	void display() {
		for (int i = top; i >= 0; i--)
			cout << array[i] << " ";
		cout << "\n";
	}

	void insert_at_bottom(int x ){
		if (this->isEmpty()){this->push(x);return;}
		int y = this->pop() ;
		this->insert_at_bottom(x) ;
		this->push(y) ;
	}

	void reverse(){
		if (isEmpty())return ;
		int cur = pop();
		reverse();
		insert_at_bottom(cur) ;
	}
};



int main() {


	Stack stk(5);
	stk.push(10);
	stk.push(20);
	stk.push(30);

	stk.display();	// 30 20 10
	cout << stk.peek() << "\n";	// 30
   stk.insert_at_bottom(15);
   
	stk.display();	// 30 20 10
	cout << stk.peek() << "\n";	// 30
   stk.insert_at_bottom(19);
   
	stk.display();	// 30 20 10
   
 
    stk.reverse();
cout << "reverse\n" ;
	stk.display();
   
	while (!stk.isEmpty()) {
		cout <<"stk.peek "<< stk.peek() << " ";
		stk.pop();
	} // 30 20 10

	return 0;
}
