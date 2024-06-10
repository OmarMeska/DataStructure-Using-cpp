#include<bits/stdc++.h>
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

    int Size(){
        return top + 1; 
    }

	void display() {
		for (int i = top; i >= 0; i--)
			cout << array[i] << " ";
		cout << "\n";
	}
};

class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        Stack st(asteroids.size());
        for (int i=0;i<asteroids.size();i++){

            if (st.isEmpty()or asteroids[i]>0 or (asteroids[i]<0 and st.peek()<0))st.push(asteroids[i]) ;
            else if (abs(asteroids[i])<0 and st.peek()>0 and abs(asteroids[i]) == st.peek() )st.pop();
            else if (asteroids[i] <0 and st.peek()>0){
                   
                   bool flag2 =false ;
                   while (!st.isEmpty() and abs(asteroids[i])>st.peek() and  st.peek()>0){
                    st.pop();flag2=true ;
                   }
                   if ((st.isEmpty() or st.peek()<0) )st.push(asteroids[i]) ;
                 
               }
               

            }
        vector<int>res ;
        while (!st.isEmpty())res.push_back(st.pop()) ;
        reverse(res.begin(),res.end()) ;
        return res ;
            }

    
};


int main() {

    Solution sl ;
    vector<int> ast ={-2,-2,1,-2} ;
    ast = sl.asteroidCollision(ast) ;
    for (auto i :ast) cout << i<< ' ' ;

	return 0;
}
