#include<bits/stdc++.h>
using namespace std;

typedef char type ;
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

	void display() {
		for (int i = top; i >= 0; i--)
			cout << array[i] << " ";
		cout << "\n";
	}
};

 string removeDuplicates(string s) {
        Stack st(s.size());
        for (int i = s.size()-1; i>=0; i--){
            if (st.isEmpty() or s[i]!=st.peek()) st.push(s[i]);
            else if (st.peek()==s[i]) st.pop();
        }
        string res {} ;
        while (!st.isEmpty()) res+=st.pop() ;
        return res ;
    }

char get_match(char s) {
    if (s ==')') return '(' ;
    if (s=='}') return '{' ;
     return '[';
}
bool isValid(string str){
   Stack st (str.size()) ;

   for (int i=0 ;i< str.size() ;i++) {
    if (str[i]=='(' or str[i]=='{' or str[i]=='[') st.push(str[i]);
    else if (st.isEmpty() or st.pop()!=get_match(str[i])) return false ;
   }
   return st.isEmpty() ;
}


string reverse_subwords(string str) {
    
    str+=' ' ;
    Stack st(str.size()) ;
 string res {};
    for (int i=0 ;i<str.length();i++){
        if (str[i]==' '){
            while(!st.isEmpty())
           res+=st.pop();
            
            res+=' ';
        }else st.push(str[i]);
    }
    return res ;
}

int reverse_num(int num) {
  string str = to_string(num) ;
  Stack st(str.size()) ;
   while (num){
    int x = num%10 ;
      st.push(x );
      num/=10;
   }
 int res{} ;
  int mul =1 ;
   while(!st.isEmpty()){
    int x = st.pop();
     x*=mul;
     res += x ;
     mul*=10;
   } 
   return res ;

}

int main() {

  string res = removeDuplicates("abbaca") ;
  cout << res << endl ;

	// Stack stk(3);
	// stk.push(10);
	// stk.push(20);
	// stk.push(30);

	// if (!stk.isFull())
	// 	stk.push(50);
	// else
	// 	cout << "Full Stack\n";
	// stk.display();	// 30 20 10
	// cout << stk.peek() << "\n";	// 30

	// while (!stk.isEmpty()) {
	// 	cout << stk.peek() << " ";
	// 	stk.pop();
	// } // 30 20 10

	return 0;
}
