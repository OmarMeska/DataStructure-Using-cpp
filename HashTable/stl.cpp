#include<iostream>
#include<unordered_map>
#include<unordered_set>
using namespace std;

void test_unordered_set() {
	unordered_set<int> s1 {20, 10, 20, 5, 30};

	s1.insert(7);
	s1.insert(0);

	for (auto v : s1)
		cout << v << " ";
	cout << "\n";	// 0 7 20 10 5 30 : removed duplicates

	if(s1.count(20))
		cout<<"20 exists\n";

	// unordered_multiset: same but allows duplicates
}

void print(const unordered_map<string, int> &mp) {
	for (const pair<string, int> &item : mp)
		cout << item.first << "-" << item.second << " | ";
	cout << "\n";
}

void test_unordered_map() {
	unordered_map<string, int> mp;

	mp["mostafa"] = 10;
	mp["mostafa"] = 20;
	mp["ali"] = 10;
	mp["bzzzzzzzzz"] = 18;
	mp["ali"]++;
	// bzzzzzzzzz-18 | mostafa-20 | ali-11 |
	// NOT ordered. String is hashed

	print(mp);
}


int main() {
	test_unordered_map();


	cout<<hash<string>{}("mostafa")<<"\n";	// 599476741851583482
	cout<<hash<int>{}(15)<<"\n";			// 15
	cout<<hash<double>{}(  1.0/7.0  )<<"\n";	// 17712118859827550249
	cout<<hash<double>{}(1+1.0/7.0-1)<<"\n";	// 11642402381101587664


	return 0;
}
