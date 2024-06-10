#include<iostream>
#include<vector>
#include<cmath>
#include<cassert>
#include<sstream>
using namespace std;

int hash_string(string str, int n_ = 65407) {
	int base = 2 * 26 + 10;	// lower, upper and 10 digits
	long long n = n_;
	long long sum = 0;

	for (int i = 0; i < (int) str.size(); ++i) {
		// lowers from [0-25], upper [26-51] and digits [52-61]
		int value = 0;
		if (islower(str[i]))
			value = str[i] - 'a';
		else if (isupper(str[i]))
			value = 26 + str[i] - 'A';
		else if (isdigit(str[i]))
			value = 26 + 26 + str[i] - '0';
		else
			assert(false);
		sum = sum * base + value;	// base 26 number
		sum %= n;	// reduce to minimize overflows
	}
	return sum % n;
}

struct PhoneEntry {
	const static int INTERNAL_LIMIT = 2147483647;
	string name;			// key
	string phone_number;	// data

	int hash() {
		return hash_string(name, INTERNAL_LIMIT);
	}

	PhoneEntry(string name, string phone_number) :
			name(name), phone_number(phone_number) {
	}

	void print() {
		cout << "(" << name << ", " << phone_number << ")  ";
	}
};

class PhoneHashTable {
private:
	int table_size { };
	double limit_load_factor { };
	int total_elements { };
	vector<vector<PhoneEntry>> table;

public:
	PhoneHashTable(int table_size = 10, double limit_load_factor = 0.75) :
		table_size(table_size), limit_load_factor(limit_load_factor) {
		table.resize(table_size);
	}

	bool get(PhoneEntry &phone) {
		int idx = phone.hash() % table_size;

		for (int i = 0; i < (int) table[idx].size(); ++i) {
			if (table[idx][i].name == phone.name) {
				phone = table[idx][i];
				return true;
			}
		}
		return false;
	}

	void put(PhoneEntry phone) {
		int idx = phone.hash() % table_size;

		for (int i = 0; i < (int) table[idx].size(); ++i) {
			if (table[idx][i].name == phone.name) {
				table[idx][i] = phone; // exist => update
				return;
			}
		}
		++total_elements;
		rehashing();
		table[idx].push_back(phone);
	}

	bool remove(PhoneEntry phone) {
		int idx = phone.hash() % table_size;
		for (int i = 0; i < (int) table[idx].size(); ++i) {
			if (table[idx][i].name == phone.name) {
				// Swap with last and remove last in O(1)
				swap(table[idx][i], table[idx].back());
				table[idx].pop_back();
				--total_elements;
				rehashing();
				return true;
			}
		}
		return false;
	}

	void rehashing() {
		double cur_load_factor = (double) total_elements / table_size;
		cout<<cur_load_factor<<"\n";
		if (cur_load_factor < limit_load_factor)
			return;

		PhoneHashTable new_table(2 * table_size, limit_load_factor);

		for (int hash = 0; hash < table_size; ++hash) {
			if (table[hash].size() == 0)
				continue;

			for (int i = 0; i < (int) table[hash].size(); ++i)
				new_table.put(table[hash][i]);
		}
		// Copy & delete
		table_size *= 2;
		table = new_table.table;

		print_all();
	}

	void print_all() {
		cout<<"**********************\n";
		for (int hash = 0; hash < table_size; ++hash) {
			if (table[hash].size() == 0)
				continue;

			cout << "Hash " << hash << ": ";
			for (int i = 0; i < (int) table[hash].size(); ++i)
				table[hash][i].print();
			cout << "\n" << flush;
		}
	}
};

string to_str(int val) {
	ostringstream oss;
	oss << val;
	return oss.str();
}
int main() {

	PhoneHashTable table;
	for (int i = 0; i < 100; ++i) {
		table.put(PhoneEntry(to_str(i), to_str(i * 10)));
	}

	return 0;
}
