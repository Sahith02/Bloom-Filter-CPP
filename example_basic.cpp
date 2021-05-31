#include<iostream>
#include "bloom_filter.hpp"
using namespace std;

int main(){
	bloom_filter<string> bf(2, 20, 4);		// parameters -> (num of hash functions, bit array size, expected num of elements)

	// Inserting elements into the bloom filter
	bf.insert("sahith@gmail.com");
	bf.insert("om@gmail.com");
	bf.insert("saksham@gmail.com");

	// Querying whether the elements exist in the bloom filter
	cout << "Does element 1 exist? " << bf.check("sahith@gmail.com") << endl;
	cout << "Does element 2 exist? " << bf.check("mo@gmail.com") << endl;
}