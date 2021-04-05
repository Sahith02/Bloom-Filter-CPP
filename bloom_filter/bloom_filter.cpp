#include <iostream>
#include <stdlib.h>
using namespace std;
#define WORD 32

template<int bit_size>
class bit_vector;

template<int bit_size>
ostream& operator<<(ostream &output, bit_vector<bit_size> b);

template<int bit_size>
class bit_vector{
	private:
	int _bit_size;
	int _array_size;
	uint32_t* _bit_array;

	public:
	bit_vector() : _bit_size(bit_size) {
		_array_size = _bit_size / WORD + 1;
		_bit_array = new uint32_t[_array_size];
		for(int i = 0; i < _array_size; ++i){
			_bit_array[i] = 0;
		}
	}

	int array_index(int bit_pos){
		return bit_pos / WORD;
	}

	int array_offset(int bit_pos){
		return bit_pos % WORD;
	}

	// Bit operation functions
	bool set(int bit_pos, bool bit_val){
		if(bit_pos >= _bit_size){
			return false;
		}

		int bit_index = array_index(bit_pos);
		int bit_offset = array_offset(bit_pos);
		if(bit_val){
			_bit_array[bit_index] |= (1 << (WORD - bit_offset - 1));
		}
		else{
			_bit_array[bit_index] &= ~(1 << (WORD - bit_offset - 1));
		}
		return true;
	}

	void reset(){
		for(int i = 0; i < this -> _bit_size; ++i){
			this -> set(i, 0);
		}
	}

	void flip(){
		for(int i = 0; i < this -> _bit_size; ++i){
			if(this -> test(i) == true){
				this -> set(i, false);
			}
			else{
				this -> set(i, true);
			}
		}
	}

	// Bit access functions
	bool test(int bit_pos){
		if(bit_pos >= _bit_size){
			return false;
		}
		int bit_index = array_index(bit_pos);
		int bit_offset = array_offset(bit_pos);
		return _bit_array[bit_index] & (1 << (WORD - bit_offset - 1));
	}

	bool operator[] (int bit_pos){
		return this -> test(bit_pos);
	}

	int size(){
		return this -> _bit_size;
	}

	int count(){
		int _count = 0;
		for(int i = 0; i < this -> _bit_size; ++i){
			if(this -> test(i) == true){
				// cout << i << " ";
				++_count;
			}
		}
		return _count;
	}

	bool any(){
		for(int i = 0; i < this -> _bit_size; ++i){
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
		for(int i = 0; i < this -> _bit_size; ++i){
			if(this -> test(i) == false){
				return false;
			}
		}
		return true;
	}

	friend ostream& operator<<<bit_size>(ostream &output, bit_vector<bit_size> b);
};

template<int bit_size>
ostream& operator<<(ostream &output, bit_vector<bit_size> b){
	uint32_t compare = (1 << 31);
	// printing all but last element of bit array
	int i = 0;
	for(i = 0; i < b._array_size - 1; ++i){
		uint32_t temp = b._bit_array[i];
		for(int j = 0; j < 32; ++j){
			output << ((temp & compare) ? 1 : 0) << " ";
			temp = temp << 1;
		}
		output << endl;
	}
	// printing last element of the bit array
	uint32_t temp = b._bit_array[i];
	int max_offset = b._bit_size % WORD;
	for(int j = 0; j < max_offset; ++j){
		output << ((temp & compare) ? 1 : 0) << " ";
		temp = temp << 1;
	}
	return output;
}

int main(){
	cout << boolalpha;
	bit_vector<30> b;
	b.set(2, 1);
	b.set(3, 1);
	cout << "Array is: " << b << endl;
	cout << "Array value at 2: " << b.test(2) << ", Array value at 4: " << b.test(4) << endl;
	cout << "Array value at 2: " << b[2] << ", Array value at 4: " << b[4] << endl;
	cout << "Array size is: " << b.size() << endl;
	cout << "Array count of set bits is: " << b.count() << endl;
	cout << "Is any bit set in the array? " << b.any() << endl;
	cout << "Is array empty? " << b.none() << endl;
	cout << "Are all bits set in the array? " << b.all() << endl;
	b.flip();
	cout << "Array after flipping: " << b << endl;
	b.reset();
	cout << "Array after resetting: " << b << endl;
}