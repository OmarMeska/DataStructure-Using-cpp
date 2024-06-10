#include<iostream>
#include <vector>
#include<cassert>
using namespace std;

int hash_num(int value, int n_ = 65407) {
	long long n = n_;
	return (value % n + n) % n;
}

unsigned int hash_num2(int value, unsigned int n = 65407) {
	return (unsigned int)value % n;
}

int hash_string(string str, int n) {
	long long nn = n;
	long long sum = 0;
	for (int i = 0; i < (int) str.size(); ++i)
		sum = (sum * 26 + str[i] - 'a') % nn;
	return sum % nn;
}

int main() {

	return 0;
}
