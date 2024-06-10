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
    void free(){
        while (!isEmpty()) pop();
    }
};

#include <iostream>
#include <cassert>
using namespace std;

class Queue {
	int size { };
    Stack st1 ;
    Stack st2 ;
	int *array { };

public:
	Queue(int size) :
			size(size),st1(size),st2(size) {
		array = new int[size];
	}

	~Queue() {
		delete[] array;
	}
   int dequeu(){
    return st1.pop() ;
   }

   void enqueu(int value) {
     while(!st1.isEmpty()){
        st2.push(st1.pop());
     }
     st2.push(value);
     while(!st2.isEmpty())st1.push(st2.pop()) ;
     
   }

	int next(int pos) {
		++pos;
		if (pos == size)
			pos = 0;
		return pos;
		//return (pos + 1) % size;	//  Or shorter way
	}
    
};

int main() {


	return 0;
}
