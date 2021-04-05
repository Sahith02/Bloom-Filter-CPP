#include<iostream>
#include<stdlib.h>
using namespace std;
#define PRIME 1500450271

class Node{
	public:
	int _data;
	Node* _next;
	Node* _prev;
	Node() : _data(0), _next(NULL), _prev(NULL) {}
	Node(int data) : _data(data), _next(NULL), _prev(NULL) {}
};

long long int hash_function(long long int value){
	return value % PRIME;
}

class my_set{
	private:
	Node** _buckets;
	int _bucket_count;
	int _size;

	public:
	my_set() : _bucket_count(1), _size(0){
		_buckets = new Node*[_bucket_count];
		_buckets[0] = NULL;
	}
	~my_set(){
		delete[] _buckets;
	}
	bool rehash(Node** buckets, int data, int bucket_count){
		int hashed_data = hash_function(data);
		// cout << hashed_data << " ";
		int bucket_index = hashed_data % bucket_count;
		// cout << bucket_index << " ";
		if(buckets[bucket_index] == NULL){
			// cout << " here4 ";
			buckets[bucket_index] = new Node(data);
		}
		else{
			Node* temp = buckets[bucket_index];
			// bucket list elements are same (except last)
			while(temp -> _next != NULL){
				// cout << "here1";
				if(temp -> _data == data){
					return false;
				}
				temp = temp -> _next;
			}
			// last element in bucket list is same
			if(temp -> _data == data){
				return false;
			}
			temp -> _next = new Node(data);
			temp -> _next -> _prev = temp;
		}
		return true;
	}
	void insert(int data){
		if(_bucket_count == _size){
			int new_bucket_count = 2 * _bucket_count;
			Node** temp_buckets = new Node*[new_bucket_count];
			for(int i = 0; i < new_bucket_count; ++i){
				temp_buckets[i] = NULL;
			}
			for(int i = 0; i < _bucket_count; ++i){
				if(_buckets[i] != NULL){
					Node* temp = _buckets[i];
					while(temp != NULL){
						// this -> show();
						// cout << "here2";
						bool rehashed = rehash(temp_buckets, temp -> _data, new_bucket_count);
						// if(!rehashed){
						// 	return;
						// }
						// this -> show();
						temp = temp -> _next;
					}
				}
			}
			delete[] _buckets;
			_buckets = temp_buckets;
			_bucket_count = new_bucket_count;
		}
		bool rehashed = rehash(_buckets, data, _bucket_count);
		if(!rehashed){
			return;
		}
		++(this -> _size);
	}
	void show(){
		cout << "bucket_count = " << _bucket_count << endl;
		cout << "size = " << _size << endl;
		for(int i = 0; i < _bucket_count; ++i){
			cout << "[" << i << "] ";
			if(_buckets[i] != NULL){
				Node* temp = _buckets[i];
				while(temp != NULL){
					// cout << "here3";
					cout << temp -> _data << " ";
					temp = temp -> _next;
				}
			}
			else{
				cout << "NULL";
			}
			cout << endl;
		}
	}

	class iterator{
		private:
		Node** _it_ptr;

		public:
		iterator(Node** it_ptr) : _it_ptr(it_ptr) {}
		
		int operator*(){
			return (*_it_ptr) -> _data;
		}

		iterator operator++(){
			if((*_it_ptr) -> _next == NULL){
				do{
					++_it_ptr;
				}while((*_it_ptr) == NULL);
				return _it_ptr;
			}
			*_it_ptr = (*_it_ptr) -> _next;
			return *this;
		}

		// iterator operator++(int){
		// 	iterator temp(*this);
		// 	++(*this);
		// 	return temp;
		// }
	};

	iterator begin(){
		for(int i = 0; i < _bucket_count; ++i){
			if(_buckets[i] != NULL){
				return iterator(&_buckets[i]);
			}
		}
	}
};

int main(){
	my_set set;
	set.insert(13);
	set.insert(8);
	set.insert(4);
	set.insert(3);
	set.insert(4);
	set.insert(0);
	set.insert(1);
	set.insert(4);
	// set.insert(10);
	set.insert(11);
	// set.insert(41);
	// set.insert(2);
	// set.insert(15);
	set.show();
	auto it = set.begin();
	cout << *(it) << endl;
	cout << *(++it) << endl;
	cout << *(++it) << endl;
	// cout << *(it++) << endl;
	// cout << *(it++) << endl;
	// cout << *(it++) << endl;
	// cout << *(it++) << endl;
	// cout << *(it++) << endl;
	// cout << *(it++) << endl;
	// cout << *(it++) << endl;

}