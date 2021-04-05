#include <iostream>
#include <stdlib.h>
using namespace std;
#define WORD 32

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

	bool test(int bit_pos){
		int bit_index = array_index(bit_pos);
		int bit_offset = array_offset(bit_pos);

		return _bit_array[bit_index] & (1 << (WORD - bit_offset - 1));
	}

	void show(){
		uint32_t compare = (1 << 31);
		// printing all but last element of bit array
		int i = 0;
		for(i = 0; i < _array_size - 1; ++i){
			uint32_t temp = _bit_array[i];
			for(int j = 0; j < 32; ++j){
				cout << ((temp & compare) ? 1 : 0) << " ";
				temp = temp << 1;
			}
			cout << endl;
		}
		// printing last element of the bit array
		uint32_t temp = _bit_array[i];
		int max_offset = _bit_size % WORD;
		for(int j = 0; j < max_offset; ++j){
			cout << ((temp & compare) ? 1 : 0) << " ";
			temp = temp << 1;
		}
		cout << endl;
	}
};

int main(){
	cout << boolalpha;
	bit_vector<30> b;
	b.set(2, 1);
	b.set(3, 1);
	cout << b.test(2) << b.test(3) << endl;
	b.show();
	cout << "Bloom filters coming up!" << endl;
}