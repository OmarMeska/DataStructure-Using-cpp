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

	void insert(string str, int idx = 0) {
		if (idx == (int) str.size())
			isLeaf = 1;
		else {
			int cur = str[idx] - 'a';
			if (child[cur] == 0)
				child[cur] = new trie();
			child[cur]->insert(str, idx + 1);
		}
	}

	void insert_iterative(string str ){
       int idx = 0;
		int int_based = str[idx]-'a' ;
		trie * cur = this ;
		while (true){
		if (idx == str.size()) {cur->isLeaf = 1 ;break;}
             
			//  cout << "str[idx] "<< str[idx] << '\n' ;
		if (cur->child[int_based] ==0) 
		    cur->child [int_based ] = new trie() ;
		
		cur = cur->child [int_based] ;
		 int_based = str[++idx]-'a' ;
	 }
	}
 
     string  first_word_prefix(const string &str){
		trie* cur = this;
		for (int idx = 0; idx < (int) str.size(); ++idx) {
			int ch = str[idx] - 'a';
			
			if (!cur->child[ch])
				return str;	
				
			if (cur->child[ch]->isLeaf) return str.substr(0,idx+1) ;
			cur = cur->child[ch];
		}
		return str;
	}

    bool word_exist_iterative(string str) {
    int idx =0 ;
     trie * cur = this;
	 while (cur->child[str[idx]-'a']){
		cur = cur->child [str[idx++]-'a'] ;
	 }
	 return ( cur->isLeaf) and (idx == str.size());
	}
    
	bool word_exist(string str, int idx = 0) {
		if (idx == (int) str.size())
			return isLeaf;	// there is a string marked here

		int cur = str[idx] - 'a';
		if (!child[cur])
			return false;	// such path don't exist

		return child[cur]->word_exist(str, idx + 1);
	}

	bool prefix_exist(string str, int idx = 0) {
		if (idx == (int) str.size())
			return true;	// all subword covered

		int cur = str[idx] - 'a';
		if (!child[cur])
			return false;	// such path don't exist

		return child[cur]->prefix_exist(str, idx + 1);
	}

    void list_substrs(const string & str ,vector<string>&queries){
		trie* cur = this;
		for (int i=0 ;i<str.size() ;i++){
			string sub_str = str.substr(i,str.size()) ;
			cur.insert(sub_str) ;
		}
		vector<strin> new_vec ;
		for (int i=0 ;i<queries.size() ;i++){
			if (cur->prefix_exist(queries[i])) new_vec.push_back(queries[i]) ;
		}
for (auto i:new_vec) cout << i << ' ' ;
cout << endl ;
	}


};

int main() {
	trie root;

	// root.insert("abcd");
	// root.insert("xyz");
	// root.insert("abf");
	// root.insert("xn");
	// root.insert("ab");
	// root.insert("bcd");

	// cout << root.word_exist("xyz") << "\n";
	// cout << root.word_exist("xy") << "\n";
	// cout << root.prefix_exist("xy") << "\n";

	root.insert_iterative("abcd");
	root.insert_iterative("xyz");
	root.insert_iterative("abf");
	root.insert_iterative("xn");
	root.insert_iterative("xnabc");
	root.insert_iterative("ab");
	root.insert_iterative("bcd");
   
   cout << root.first_word_prefix("abcdefg")<< endl ;
   cout << root.first_word_prefix("a")<< endl ;
   cout << root.first_word_prefix("xy")<< endl ;
   cout << root.first_word_prefix("xnabc")<< endl ;
   cout << root.first_word_prefix("ab")<< endl ;
   cout << root.first_word_prefix("a")<< endl ;
	return 0;
}
