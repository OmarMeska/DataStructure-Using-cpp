#include <iostream>
#include <cassert>
using namespace std;

class Stack {
private:
	int size { };
	int top1 { };
    int top2 { };
	int* array { };
public:
	Stack(int size) :
			size(size), top1(-1),top2(size){
		array = new int[size];
	}

	~Stack() {
		delete[] array;
	}

	void push(int id ,int x) {
		assert(!isFull());
		if (id==1)array[++top1] = x;
        else array[--top2]=x ;
	}

	int pop(int id) {
		assert(!isEmpty(id));
	 if (id==1)	return array[top1--];
	  else return array[top2++];
    }

	int peek(int id) {
		assert(!isEmpty(id));
		if (id==1)return array[top1];
	     else return array[top2];
    }

	bool isFull() {
		return top1+1 >= top2;
	}

	bool isEmpty(int id) {
 if (id==1)		return (top1 == -1) ;
	else return (top2 ==size) ;
    }
    
	void display() {
		for (int i = top1; i >= 0; i--)
			cout << array[i] << " ";
		for (int i=top2;i<size;i++) cout << array[i] << ' ';
        cout << "\n";
	}
};



int main() {


	Stack stk(10);
	stk.push(1,10);
	stk.push(1,20);
	stk.push(1,30);
	stk.push(1,90);
 cout << "i am here \n" ;
	stk.push(2,60);
	stk.push(2,70);
	stk.push(2,50);
	if (!stk.isFull())
		stk.push(2,500);
	else
		cout << "Full Stack\n";
	stk.display();	// 30 20 10
	cout << stk.peek(1) << "\n";	// 30
	cout << stk.peek(2) << "\n";	// 30

	while (!stk.isEmpty(1)) {
		cout<<"peek1 : " << stk.peek(1) << " ";
		stk.pop(1);
	}
    cout << endl;
    while(!stk.isEmpty(2)){
        cout << "peek2 : " << stk.peek(2) << " "; 
        stk.pop(2);
    }

	return 0;
}
