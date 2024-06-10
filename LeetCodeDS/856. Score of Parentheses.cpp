#include<bits/stdc++.h>
using namespace std;

// typedef char type ;

struct type  {
  int data ;
  int  index;
 

};
class Stack {
private:
	int size { };
	int top { };
	type* array { };
public:
	Stack(int size) :
			size(size), top(-1) {
		array = new type[size];
	}

	~Stack() {
		delete[] array;
	}

	void push(type x) {
		assert(!isFull());
		array[++top] = x;
	}

	type pop() {
		assert(!isEmpty());
		return array[top--];
	}

	type   peek() {
		assert(!isEmpty());
		return array[top];
	}

	int isFull() {
		return top == size - 1;
	}

	int isEmpty() {
		return top == -1;
	}

	// void display() {
	// 	for (int i = top; i >= 0; i--)
	// 		cout << array[i] << " ";
	// 	cout << "\n";
	// }
};

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
    Stack st (temperatures.size()) ;
   map <int,int>res ;
    for (int i=0;i<temperatures.size();i++){
        if (st.isEmpty() or temperatures[i]<=st.peek().data) st.push({temperatures[i],i}) ;
        else if (temperatures[i]>st.peek().data) {
          while(!st.isEmpty() and  temperatures[i]>st.peek().data){
         
            temperatures[st.peek().index] = i-st.pop().index ;
            
          }
          st.push({temperatures[i],i}) ;
          
        }
    }
    while(!st.isEmpty()) temperatures[st.pop().index]=0;
 return temperatures;
    }
};
int main() {

	Solution sl;
    vector<int>vec={73,74,75,71,69,72,76,73};
     vec = sl.dailyTemperatures(vec) ;
     for(auto i :vec) cout << i << " "; 

	return 0;
}
