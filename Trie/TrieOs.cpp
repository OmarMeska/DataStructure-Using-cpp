#include<iostream>
#include<cstring>	// memset
#include <bits/stdc++.h>
using namespace std;

class trie {
private:
	map<string,trie*>child;
	bool isLeaf { };

public:
	trie() {
	}

void insert(const vector<string> &path) {
		trie* cur = this;

		for (int idx = 0; idx < (int) path.size(); ++idx) {
			if (!cur->child.count(path[idx]))
				cur->child[path[idx]] = new trie();
			cur = cur->child[path[idx]];
		}
		cur->isLeaf = true;
	}

	bool subpath_exist(const vector<string> &path) {
		trie* cur = this;

		for (int idx = 0; idx < (int) path.size(); ++idx) {
			if (!cur->child.count(path[idx]))
				return false;	// such path don't exist
			cur = cur->child[path[idx]];
		}
		return true;
	}
};

int main() {
	trie root;
      vector<string > path ;
      path = {"home" , "software" , "eclipse"} ;
      root.insert(path) ;
      path = {"home" , "software" , "eclipse" ,"bin"} ;
	  root.insert(path) ;
      path = {"home" , "installed" , "gnu"} ;
      root.insert(path) ;
	  path = {"user","omar","tmp"} ;
	  root.insert(path) ;
	  
	  path = {"user","omar","tmp"} ;
	   cout << root.subpath_exist(path) << endl;

	  path = {"user","omar"} ;
	     cout << root.subpath_exist(path) << endl;

	  path = {"user" , "om"} ;
	     cout << root.subpath_exist(path) << endl;
	  
	  path = {"user","omar","meska"} ;
	     cout << root.subpath_exist(path) << endl;

	  
	  
	  return 0;
}
