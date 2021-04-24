#include <bits/stdc++.h>
#include "bloom_filter.hpp"
using namespace std;


int main(){
	bloom_filter<string> bf(2, 20, 4);
	
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