#include <bits/stdc++.h>
#include "bloom_filter.hpp"
using namespace std;


int main(){
	cout << boolalpha;

	// cout << endl << "BIT VECTOR TESTING" << endl;
	// bit_vector<20> b;
	// b.set(2, 1);
	// b.set(19, 1);
	// cout << "Array is: " << b << endl;
	// cout << "Array value at 2: " << b.test(2) << ", Array value at 4: " << b.test(4) << endl;
	// cout << "Array value at 2: " << b[2] << ", Array value at 4: " << b[4] << endl;
	// cout << "Array size is: " << b.size() << endl;
	// cout << "Array count of set bits is: " << b.count() << endl;
	// cout << "Is any bit set in the array? " << b.any() << endl;
	// cout << "Is array empty? " << b.none() << endl;
	// cout << "Are all bits set in the array? " << b.all() << endl;
	// bit_vector<20> c(b);
	// cout << "New array c (copy of b): " << c << endl;
	// c.flip();
	// cout << "Array b after flipping c: " << b << endl;
	// cout << "Array c after flipping c: " << c << endl;
	// b.reset();
	// cout << "Array b after resetting b: " << b << endl;
	// cout << "Array c after resetting b: " << c << endl;



	// cout << endl << "BLOOM FILTER TESTING" << endl;
	// bloom_filter<string> bf(2, 20, 4);
	// bf.insert("om@gmail.com");
	// bf.insert("saksham@gmail.com");
	// bf.insert("sahith@gmail.com");
	// bloom_filter<string> bf2(bf);
	// cout << "Bloom Filter bf: " <<  bf << endl;
	// cout << "Bloom Filter bf2: " << bf2 << endl;
	// cout << "Does element 1 exist? " << bf.check("sahith@gmail.com") << endl;
	// cout << "Does element 2 exist? " << bf.check("mo@gmail.com") << endl;


	cout << endl << "DATE TESTING" << endl;
	bloom_filter<Date> bf_date(4, 50, 4);
	cout << "False Positive Probability = " << bf_date.get_false_positive_rate() * 100 << "%" << endl;
	cout << "Number of Hash functions used = " << bf_date.get_num_hash_fn() << endl;
	cout << "Bit array size = " << bf_date.get_bit_array_size() << endl;
	cout << "Expected number of elements to insert = " << bf_date.get_expected_num_elements() << endl;
	
	
	Date date1(5, Jan, 2021, 9, 8, 20);
	Date date2(5, Feb, 2021, 19, 7, 23);
	Date date3(8, Mar, 2020, 5, 4, 22);
	Date date4(8, Apr, 2022, 7, 34, 45);
	cout << "Date 1: " << date1 << ", Timestamp: " << date1.timestamp() << endl;
	cout << "Date 2: " << date2 << ", Timestamp: " << date2.timestamp() << endl;
	cout << "Date 3: " << date3 << ", Timestamp: " << date3.timestamp() << endl;
	cout << "Date 4: " << date4 << ", Timestamp: " << date4.timestamp() << endl;

	bf_date.insert(date1);
	// bf_date.insert(date2);
	bf_date.insert(date3);
	bf_date.insert(date4);
	cout << "Checking if Date 1 exists? " << bf_date.check(date1) << endl;
	cout << "Checking if Date 2 exists? " << bf_date.check(date2) << endl;
	cout << "Checking if Date 3 exists? " << bf_date.check(date3) << endl;
	cout << "Checking if Date 4 exists? " << bf_date.check(date4) << endl;
}