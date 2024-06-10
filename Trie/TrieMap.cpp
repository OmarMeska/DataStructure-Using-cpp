#include <iostream>
#include <cstring> // memset
#include <bits/stdc++.h>
using namespace std;

class trie
{
private:
	map<int, trie *> child;
	bool isLeaf{};

public:
	trie()
	{
		// set an array to 0s. Here pointers to nu
	}

	void insert(string str, int idx = 0)
	{
		if (idx == (int)str.size())
			isLeaf = 1;
		else
		{
			int cur = str[idx] - 'a';
			if (!child[cur])
				child[cur] = new trie();
			child[cur]->insert(str, idx + 1);
		}
	}

	void insert_iterative(string str)
	{
		int idx = 0;
		int int_based = str[idx] - 'a';
		trie *cur = this;
		while (true)
		{
			if (idx == str.size())
			{
				cur->isLeaf = 1;
				break;
			}

			//  cout << "str[idx] "<< str[idx] << '\n' ;
			if (cur->child[int_based] == 0)
				cur->child[int_based] = new trie();

			cur = cur->child[int_based];
			int_based = str[++idx] - 'a';
		}
	}

	string first_word_prefix(const string &str)
	{
		trie *cur = this;
		for (int idx = 0; idx < (int)str.size(); ++idx)
		{
			int ch = str[idx] - 'a';

			if (!cur->child[ch])
				return str;

			if (cur->child[ch]->isLeaf)
				return str.substr(0, idx + 1);
			cur = cur->child[ch];
		}
		return str;
	}

	bool word_exist_iterative(string str)
	{
		int idx = 0;
		trie *cur = this;
		while (cur->child[str[idx] - 'a'])
		{
			cur = cur->child[str[idx++] - 'a'];
		}
		return (cur->isLeaf) and (idx == str.size());
	}

	bool word_exist(string str, int idx = 0)
	{
		if (idx == (int)str.size())
			return isLeaf; // there is a string marked here

		int cur = str[idx] - 'a';
		if (!child[cur])
			return false; // such path don't exist

		return child[cur]->word_exist(str, idx + 1);
	}

	bool prefix_exist(string str, int idx = 0)
	{
		if (idx == (int)str.size())
			return true; // all subword covered

		int cur = str[idx] - 'a';
		if (!child[cur])
			return false; // such path don't exist

		return child[cur]->prefix_exist(str, idx + 1);
	}

	void get_all_strings(vector<string> &res, string str = "")
	{
		if (isLeaf)
			res.push_back(str);
		for (int i = 0; i < 26; i++)
		{
			if (child[i])
			{
				str += char(i + 'a');
				child[i]->get_all_strings(res, str);
				str.pop_back();
			}
		}
	}

	void auto_complete(const string &str, vector<string> &res, string sub_word = "", int first = -1)
	{
		auto cur = this;

		if (first == -1)
		{
			for (int i = 0; i < str.size(); i++)
				cur = cur->child[i], sub_word += str[i];
		}

		if (cur->isLeaf)
		{
			cout << " sub word " << sub_word << endl;
			res.push_back(sub_word);
		}
		for (int i = 0; i < 26; i++)
		{
			if (cur->child[i])
			{
				sub_word += char(i + 'a');
				cur->child[i]->auto_complete(str, res, sub_word, 0);
				sub_word.pop_back();
			}
		}
	}

	bool word_exist_with_1_change(string original, string str = "", int num_changes = 0, int idx = 0)
	{
		 cout << "str "<< str <<  " changes " << num_changes << endl;
		if (str.size() == original.size() and num_changes==0) return false ;
	if ((int)str.size() == (int)original.size() and num_changes == 1){
		cout << "returnd true " << str<< endl;	return true;}

		bool flag1 = false, flag2 = false;
		for (auto i : child)
		{
			if (char(i.first + 'a') == original[idx] )
			{
				// cout << "i.first " << char(i.first+'a') << endl ;
				flag1 = i.second->word_exist_with_1_change(original, str + original[idx], num_changes, idx + 1);
			}
			else
			{
				//  cout << "second " << char(i.first+'a') << endl ;
				if (num_changes == 0)
					flag2 = i.second->word_exist_with_1_change(original, str + original[idx], num_changes + 1, idx + 1);
			}
			if (flag1 or flag2) return true ;
		}
		return flag1 or flag2;

	}

	bool word_exist_with_1_changeV2(string str) {
		// Brute force all possible 1-char change and search for it
		// O(L * 26 * L)
		for (int i = 0; i < (int) str.size(); ++i) {
			char cpy = str[i];
			for (char ch = 'a'; ch <= 'z'; ch++) {
				if (ch == cpy)	// Must do a change
					continue;
				str[i] = ch;
				if (word_exist(str))
					return true;
			}
			str[i] = cpy;	// copy back
		}
		return false;
	}
  
  void list_substrs(const string & str ,vector<string>&queries){
		trie* cur = this;
		for (int i=0 ;i<str.size() ;i++){
			string sub_str = str.substr(i,str.size()) ;
			cur->insert_iterative(sub_str) ;
		}
		vector<string> new_vec ;
		for (int i=0 ;i<queries.size() ;i++){
			if (cur->prefix_exist(queries[i])) new_vec.push_back(queries[i]) ;
		}
for (auto i:new_vec) cout << i << ' ' ;
cout << endl ;
	}

  void any_name_iterative(string original) {
	trie* cur =this; 
	string  str ;
	bool flag = false ;
	int idx =  0 ;
 vector<string>cur_strs;
	for (int i=0 ;i<original.size();i++){
	
      if (cur->child[original[i]-'a']){
		if (!flag) idx = i ;
		flag  =1 ;
		str += original[i] ;
		cur = cur->child[original[i]-'a'] ;
		if (cur->isLeaf) cur_strs.push_back(str) ;

	  }
	  else {
      str="";
	  cur = this ;
		if (flag)i=idx;
		flag = false ;

	  }
	}
	for (auto i : cur_strs)cout << i<< ' ' ;
	 cout << endl ;
  }

 void list_substrs_v2(const string & str ,vector<string > &queries){
	trie* cur = this;
	for (auto i :queries) cur->insert_iterative(i) ;
   cur-> any_name_iterative(str) ;

 }

};

int main()
{
	trie root;
	string s = "heyabcdtwxyw";
	vector<string>queries  ={ "xy" ,"ab" ,"t" ,"yz"} ;
	root.list_substrs_v2(s,queries) ;

	return 0;
}
