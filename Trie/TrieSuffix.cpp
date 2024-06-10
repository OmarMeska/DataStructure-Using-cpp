#include<iostream>
#include<cstring>	// memset
using namespace std;

class trie {
private:
	static const int MAX_CHAR = 26;
	trie* child[MAX_CHAR];
	bool isLeaf { };

public:
	trie() {
		// set an array to 0s. Here pointers to null
		memset(child, 0, sizeof(child));
	}

   void insert(string str  ){
       trie * cur = this ;
      for (int idx = str.size()-1 ;idx >=0 ;idx --) {
            int ch = str[idx]-'a' ;
            if (!cur->child[ch])
              cur->child[ch] = new trie() ;

              cur = cur->child[ch] ;
      }
      cur->isLeaf = 1 ;
   }

   bool suffix_exist(string str) {
 
    int idx =0 ;
     trie * cur = this;
	 while (cur->child[str[idx]-'a']){
		cur = cur->child [str[idx++]-'a'] ;
	 }
	 return  (idx == str.size());
	
   }

	
};

int main() {
	trie root;


	root.insert("abcd");
	root.insert("xyz");
	root.insert("abf");
	root.insert("xn");
	root.insert("xnabc");
	root.insert("ab");
	root.insert("bcd");
   
   cout << root.suffix_exist("dcba")<< endl ;
   cout << root.suffix_exist("a")<< endl ;
   cout << root.suffix_exist("d")<< endl ;
   cout << root.suffix_exist("dc")<< endl ;
   cout << root.suffix_exist("xy")<< endl ;
   cout << root.suffix_exist("zy")<< endl ;
	return 0;
}
