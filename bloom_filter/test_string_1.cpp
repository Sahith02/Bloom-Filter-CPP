#include <iostream>
// #include <stdlib.h>
// #include <cmath>
// #include <sstream>
#include <fstream>
#include <chrono>
#include "bloom_filter.hpp"
using namespace std;


int main(int argc, char** argv){
	
	using chrono::high_resolution_clock;
	using chrono::duration_cast;
	using chrono::duration;
	cout << boolalpha;
	
	bloom_filter<string> bf(
								atof(argv[2]),
								atoll(argv[3])
							);

	cout << endl << "===== BLOOM FILTER PROPERTIES =====" << endl;

	cout << "False Positive Probability = " << bf.get_false_positive_rate() * 100 << endl;
	cout << "Number of Hash functions used = " << bf.get_num_hash_fn() << endl;
	cout << "Bit array size = " << bf.get_bit_array_size() << endl;
	cout << "Expected number of elements to insert = " << bf.get_expected_num_elements() << endl;

	cout << endl << "===== STRING TEST CASES STARTING =====" << endl;
	auto t1 = high_resolution_clock::now();
	// Inner code for timing starts

	string TEST_FILE = "./tests/string/string_test_" + (string)argv[1] + ".txt";
	string CHECK_FILE = "./tests/check_string_exists.txt";

	ifstream test_file(TEST_FILE);
	if(test_file.is_open()){
		string line;
		while (getline(test_file, line)){
			// cout << line << "\n";
			if(!line.empty() && *line.rbegin() == '\r'){
				line.erase(line.length() - 1, 1);
			}
			bf.insert(line);
		}
		test_file.close();
	}

	auto t2 = high_resolution_clock::now();

	// Inner code for timing ends
	duration<double, milli> ms_double = t2 - t1;
	cout << "Time taken to insert all elements: " << ms_double.count() << "ms\n";

	ifstream check_file(CHECK_FILE);
	if(check_file.is_open()){
		string line;
		while (getline(check_file, line)){
			// cout << line << "\n";
			if(!line.empty() && *line.rbegin() == '\r'){
				line.erase(line.length() - 1, 1);
			}
			cout << "Is Present? - " << line << " : " << bf.check(line) << endl;
		}
		check_file.close();
	}

	// cout << bf << endl;
	// string test_strings[] = {
	// 							"9623_8E08f@A34-.F190",	// present
	// 							"eeA@0ffBF.3727C",		// present
	// 							"abcd"					// no
	// 						};
	// int test_count = sizeof(test_strings) / sizeof(string);

	// cout << boolalpha;
	// for(int i = 0; i < test_count; ++i){
	// 	cout << "Is " << test_strings[i] << " present: " << bf.check(test_strings[i]) << endl;
	// }
}