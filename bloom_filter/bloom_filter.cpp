#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <sstream>
#include <fstream>
#include <chrono>
using namespace std;
#define WORD 32
#define PRIME 32494189635056477
typedef unsigned long long int ullong_t;


/*
[Class Methods]
Class bit_vector:
	default constructor: initialises empty array of 0s of given size;
	copy constructor: Makes a deep copy of a previous bit_vector of same size;
	set(bit_pos, bit_val): sets bit to bit_val at position bit_pos
	reset(): resets all bits to 0
	flip(): flips all bits
	test(i): returns value at index i
	operator[i]: returns value at index i
	size(): returns length of bit vector
	count(): returns number of 1s in the vector
	any(): checks if atleast 1 bit is set to 1
	none(): checks if none of the bits are set to 1
	all(): checks if all of the bits are set to 1
	friend ostream operator<<: displays bit vector
*/



template<ullong_t bit_size>
class bit_vector;

template<ullong_t bit_size>
ostream& operator<<(ostream &output, bit_vector<bit_size> b);

template<typename T>
class bloom_filter;

template<typename T>
ostream& operator<<(ostream& output, bloom_filter<T> bf);

template<ullong_t bit_size = 0>
class bit_vector{
	private:
	ullong_t _bit_size;			// Total number of bits in the array
	ullong_t _array_size;		// Number of 32 bit WORDS in the array [ONLY FOR INTERNAL USE]
	uint32_t* _bit_array;		// The actual array of 32 bit words

	// Internal helper functions
	ullong_t array_index(ullong_t bit_pos){
		return bit_pos / WORD;
	}

	ullong_t array_offset(ullong_t bit_pos){
		return bit_pos % WORD;
	}

	public:
	// Default constructor of len bit_size
	bit_vector() : _bit_size(bit_size) {
		_array_size = _bit_size / WORD + 1;
		_bit_array = new uint32_t[_array_size];
		for(int i = 0; i < _array_size; ++i){
			_bit_array[i] = 0;
		}
	}

	bit_vector(ullong_t _bit_size) : _bit_size(_bit_size) {
		_array_size = _bit_size / WORD + 1;
		_bit_array = new uint32_t[_array_size];
		for(int i = 0; i < _array_size; ++i){
			_bit_array[i] = 0;
		}
	}

	// Copy constructor of same len bit_size
	bit_vector(bit_vector<bit_size>& b){
		this -> _bit_size = b._bit_size;
		this -> _array_size = b._array_size;
		this -> _bit_array = new uint32_t[this -> _array_size];
		for(int i = 0; i < this -> _bit_size; ++i){
			this -> set(i, b.test(i));
		}
	}

	~bit_vector(){
		delete[] _bit_array;
	}

	// Bit operation functions
	bool set(ullong_t bit_pos, bool bit_val){
		if(bit_pos >= _bit_size){
			return false;
		}

		ullong_t bit_index = array_index(bit_pos);
		ullong_t bit_offset = array_offset(bit_pos);
		if(bit_val){
			_bit_array[bit_index] |= (1 << (WORD - bit_offset - 1));
		}
		else{
			_bit_array[bit_index] &= ~(1 << (WORD - bit_offset - 1));
		}
		return true;
	}

	void reset(){
		for(ullong_t i = 0; i < this -> _bit_size; ++i){
			this -> set(i, 0);
		}
	}

	void flip(){
		for(ullong_t i = 0; i < this -> _bit_size; ++i){
			if(this -> test(i) == true){
				this -> set(i, false);
			}
			else{
				this -> set(i, true);
			}
		}
	}

	// Bit access functions
	bool test(ullong_t bit_pos){
		if(bit_pos >= _bit_size){
			return false;
		}
		ullong_t bit_index = array_index(bit_pos);
		ullong_t bit_offset = array_offset(bit_pos);
		return _bit_array[bit_index] & (1 << (WORD - bit_offset - 1));
	}

	bool operator[] (ullong_t bit_pos){
		return this -> test(bit_pos);
	}

	ullong_t size(){
		return this -> _bit_size;
	}

	ullong_t count(){
		ullong_t _count = 0;
		for(ullong_t i = 0; i < this -> _bit_size; ++i){
			if(this -> test(i) == true){
				++_count;
			}
		}
		return _count;
	}

	bool any(){
		for(ullong_t i = 0; i < this -> _bit_size; ++i){
			if(this -> test(i) == true){
				return true;
			}
		}
		return false;
	}

	bool none(){
		if(this -> any() == false){
			return true;
		}
		else{
			return false;
		}
	}

	bool all(){
		for(ullong_t i = 0; i < this -> _bit_size; ++i){
			if(this -> test(i) == false){
				return false;
			}
		}
		return true;
	}

	friend ostream& operator<<<bit_size>(ostream &output, bit_vector<bit_size> b);
};

template<ullong_t bit_size>
ostream& operator<<(ostream &output, bit_vector<bit_size> b){
	uint32_t compare = (1 << (WORD - 1));
	// printing all but last element of bit array
	ullong_t i = 0;
	for(i = 0; i < b._array_size - 1; ++i){
		uint32_t temp = b._bit_array[i];
		for(int j = 0; j < WORD; ++j){
			output << ((temp & compare) ? 1 : 0) << " ";
			temp = temp << 1;
		}
	}
	// printing last element of the bit array
	uint32_t temp = b._bit_array[i];
	ullong_t max_offset = b._bit_size % WORD;
	for(int j = 0; j < max_offset; ++j){
		output << ((temp & compare) ? 1 : 0) << " ";
		temp = temp << 1;
	}
	return output;
}

// int main(){
// 	cout << boolalpha;
// 	bit_vector<20> b;
// 	b.set(2, 1);
// 	b.set(3, 1);
// 	cout << "Array is: " << b << endl;
// 	cout << "Array value at 2: " << b.test(2) << ", Array value at 4: " << b.test(4) << endl;
// 	cout << "Array value at 2: " << b[2] << ", Array value at 4: " << b[4] << endl;
// 	cout << "Array size is: " << b.size() << endl;
// 	cout << "Array count of set bits is: " << b.count() << endl;
// 	cout << "Is any bit set in the array? " << b.any() << endl;
// 	cout << "Is array empty? " << b.none() << endl;
// 	cout << "Are all bits set in the array? " << b.all() << endl;
// 	bit_vector<20> c(b);
// 	cout << "New array c (copy of b): " << c << endl;
// 	c.flip();
// 	cout << "Array b after flipping c: " << b << endl;
// 	cout << "Array c after flipping c: " << c << endl;
// 	b.reset();
// 	cout << "Array b after resetting b: " << b << endl;
// 	cout << "Array c after resetting b: " << c << endl;
// }



/*
[Class Methods]
Class bloom_filter:
	private:
	int P: false positivity rate;
	int k: # of hash functions (seed);
	int m: size of bit array required;
	int n: expected # of elements to insert;

	methods:
	constructor 1: simple init method from parameters P and n;
	constructor 2: another init method from k, m, n;
	copy constructor: Makes a deep copy of a previous bloom_filter of same size; [REMINDER: HAVE TO MAKE]
	insert(): insert hashed value k number of times after each hash function with seed;
	check(): checks and returns true/false;
	probability_false_positive(): returns false probability percentage calculated from the # of inserted elements;
*/

// Hasher class
class hasher{
	public:
		static ullong_t hash(string value, int seed){
			ullong_t hashed_value = 1;
			long long int temp = 1;
			for(int i = 0; i < value.size(); ++i){
				temp = (temp * 53) % PRIME;
				hashed_value = (hashed_value + (temp * (int)value[i] + 47 * seed)) % PRIME;
			}
			return hashed_value;
		}
		static ullong_t hash(int value, int seed){
			ullong_t hashed_value = 1;
			hashed_value = (53 * value + 47 * seed) % PRIME;
			return hashed_value;
		}
		static ullong_t hash(ullong_t value, int seed){
			ullong_t hashed_value = 1;
			hashed_value = (53 * value + 47 * seed) % PRIME;
			return hashed_value;
		}
		static ullong_t hash(long double value, int seed){
			ostringstream strs;
			strs << value;
			string str = strs.str();
			return hash(str, seed);
		}
};


template<typename T>
class bloom_filter{
	private:
		long double _false_positive_rate;
		int _num_hash_fn;
		ullong_t _bit_array_size;
		ullong_t _expected_num_elements;
		bit_vector<>* _bit_vector;
		inline void update_fpr(int num_hash_fn, ullong_t bit_array_size, ullong_t expected_num_elements){
			_false_positive_rate = pow(( 1.0 - (pow( (1.0-(1.0/bit_array_size)) , (num_hash_fn*expected_num_elements) ) )), (num_hash_fn));
		}

	public:
		bloom_filter(long double false_positive_rate, ullong_t expected_num_elements)
		: _false_positive_rate(false_positive_rate), _expected_num_elements(expected_num_elements){
			_bit_array_size= -1*((_expected_num_elements*log(_false_positive_rate))/pow(log(2),2));
			_num_hash_fn=(_bit_array_size/_expected_num_elements)*log(2);
			_bit_vector = new bit_vector<>(_bit_array_size);
			// Calculate _num_hash_fn and _bit_array_size
			// initialize bit_vector of size _bit_array_size
		}

		bloom_filter(int num_hash_fn, ullong_t bit_array_size, ullong_t expected_num_elements)
		: _num_hash_fn(num_hash_fn), _bit_array_size(bit_array_size), _expected_num_elements(expected_num_elements){
			// Calculate _false_positive_rate
			// initialize bit_vector of size _bit_array_size
			update_fpr(_num_hash_fn, _bit_array_size, _expected_num_elements);
			_bit_vector = new bit_vector<>(_bit_array_size);
		}

		bool insert(T value){
			// Loop through i from 0 till _num_hash_fn
				// seed is i
				// call hash_fn(value, i)
				// This hashed value, gets modded with _bit_array_size
				// set the bit to 1 at that modded value
			for(int i = 0; i < _num_hash_fn; ++i){
				int seed = i + 1;
				ullong_t hashed_value = hasher::hash(value, seed);
				ullong_t insert_at_index = hashed_value % _bit_array_size;
				bool is_inserted = _bit_vector -> set(insert_at_index, 1);

				if(!is_inserted){
					return false;
				}
			}
			return true;
		}

		bool check(int value){
			// Loop through i from 0 till _num_hash_fn
				// seed is i
				// call hash_fn(value, i)
				// This hashed value, gets modded with _bit_array_size
				// If the bit is not set -> return false
			for(int i = 0; i < _num_hash_fn; ++i){
				int seed = i + 1;
				ullong_t hashed_value = hasher::hash(value, seed);
				ullong_t check_at_index = hashed_value % _bit_array_size;
				bool check_index = _bit_vector -> test(check_at_index);

				if(!check_index){
					return false;
				}
			}
			return true;
		}

		double probability_false_positive(){
			return _false_positive_rate;
		}

		friend ostream& operator<<<T>(ostream& output, bloom_filter<T> bf);
};

template<typename T>
ostream& operator<<(ostream& output, bloom_filter<T> bf){
	output << *(bf._bit_vector);
	return output;
}



int main(){
	/*
	using chrono::high_resolution_clock;
	using chrono::duration_cast;
	using chrono::duration;
	auto t1 = high_resolution_clock::now();
	// Inner code for timing starts

	string TEST_FILE = "./tests/string/string_test_100.txt";
	ifstream file(TEST_FILE);
	if(file.is_open()) {
		string line;
		while (getline(file, line)) {
			cout << line << endl;
		}
		file.close();
	}

	auto t2 = high_resolution_clock::now();

	// Inner code for timing ends
	duration<double, milli> ms_double = t2 - t1;
	cout << ms_double.count() << "ms\n";
	*/

	bloom_filter<int> bf(2, 30, 2);
	bloom_filter<string> bf2(0.1, 30);
	cout << bf2.probability_false_positive() << endl;
	string test_1 = "sahith02@gmailjasknadn asndnalsdnamsdnakld cmadnaldndfkalsdnmadamsansdk cdcamdncadnsalmsda dsdkakslmdf ffnaklsd.com";
	string test_2 = "sahithk02@gmail.com";
	bf2.insert(test_1);
	cout << bf2 << endl;
	bf2.insert(test_2);
	cout << bf2 << endl;

	bf.insert(123);
	cout << bf << endl;

	// cout << hasher::hash("abc", 2) << endl;
	// ullong_t temp = 18736583454784733;
	// cout << hasher::hash(temp, 2) << endl;

	// long double temp2 = 12467.4784;
	// cout << hasher::hash(temp2, 1) << endl;
}