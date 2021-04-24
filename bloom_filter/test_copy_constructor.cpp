#include <bits/stdc++.h>
#include "bloom_filter.hpp"
using namespace std;


int main(){
	bloom_filter<string> bf(2, 20, 4);

	// bit_vector<10> b1;
	// b1.set(2, 1);
	// bit_vector<10> b2(b1);
	// cout << b1 << endl << b2 << endl;

	bf.insert("omomom");
	bf.insert("saksham");
	bf.insert("sahith");

	bloom_filter<string> bf2(bf);
	
	cout << bf << endl;
	cout << bf2 << endl;
	cout << boolalpha;
	cout << bf.check("sahith") << endl;
	cout << bf.check("omomo") << endl;
}