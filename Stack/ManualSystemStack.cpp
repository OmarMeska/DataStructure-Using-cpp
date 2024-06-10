#include <iostream>
#include <cassert>
using namespace std;
struct StackElement{
    int n;
    int result{-1} ;
    StackElement(int n=1 , int result=-1) :
    n(n),result(result) {
    }
};

class Stack {
private:
	int size { };
	int top { };
	StackElement* array { };
public:
	Stack(int size) :
			size(size), top(-1) {
		array = new StackElement[size];
	}

	~Stack() {
		delete[] array;
	}

	void push(StackElement x) {
		assert(!isFull());
		array[++top] = x;
	}

	StackElement pop() {
		assert(!isEmpty());
		return array[top--];
	}

	StackElement peek() {
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
			cout << array[i].n << " ";
		cout << "\n";
	}

	void insert_at_bottom(StackElement x ){
		if (this->isEmpty()){this->push(x);return;}
		StackElement y = this->pop() ;
		this->insert_at_bottom(x) ;
		this->push(y) ;
	}

	void reverse(){
		if (isEmpty())return ;
		StackElement cur = pop();
		reverse();
		insert_at_bottom(cur) ;
	}
};

int factorial_stack(int n) {
	if (n <= 1)
		return 1;

	Stack st(n);
	st.push(StackElement(n));
	StackElement cur(1);

	while(!st.isEmpty()){
        cur = st.peek() ;
        if (cur.result ==-1) {
             if (cur.n==1){
                 cur.result =1 ;
                  st.pop() ;
                  st.push(cur) ;
             } // base case
             else {
                st.push(StackElement(cur.n -1 )) ;
             }
        }else if (cur.result != -1){
             cur = st.pop();
             if (!st.isEmpty()) {
                auto parent = st.pop() ;
                parent.result = cur.result*parent.n ;
                st.push(parent) ;
             }
        }
    }
    return cur.result ;
}
int main() {

   cout <<  factorial_stack(5) ;
	return 0;
}
