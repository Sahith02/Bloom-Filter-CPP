# Generic Bloom Filter

## How to Run
### Linux
#### Constructor 1
Needs FPR, Expected Number of Elements.
```bash
# To run string test cases
make run_string_1 TEST_FILE=500 FPR=0.1 EXPECTED_INSERT=500

# To run int test cases
make run_int_1 TEST_FILE=500 FPR=0.1 EXPECTED_INSERT=500

# To run double test cases
make run_double_1 TEST_FILE=500 FPR=0.1 EXPECTED_INSERT=500
```

#### Constructor 2
Needs Number of Hash functions, Bit Array Size, Expected Number of Elements.
```bash
# To run string test cases
make run_string_2 TEST_FILE=500 HASH_COUNT=5 BIT_COUNT=5000 EXPECTED_INSERT=500

# To run int test cases
make run_int_2 TEST_FILE=500 HASH_COUNT=5 BIT_COUNT=5000 EXPECTED_INSERT=500

# To run double test cases
make run_double_2 TEST_FILE=500 HASH_COUNT=5 BIT_COUNT=5000 EXPECTED_INSERT=500
```

### Windows
#### Constructor 1
```bash
# To run string test cases
g++ test_string_1.cpp bloom_filter.hpp
a.exe 500 0.1 500

# To run int test cases
g++ test_int_1.cpp bloom_filter.hpp
a.exe 500 0.1 500

# To run double test cases
g++ test_double_1.cpp bloom_filter.hpp
a.exe 500 0.1 500
```

#### Constructor 2
```bash
# To run string test cases
g++ test_string_2.cpp bloom_filter.hpp
a.exe 500 5 5000 500

# To run int test cases
g++ test_string_2.cpp bloom_filter.hpp
a.exe 500 5 5000 500

# To run double test cases
g++ test_string_2.cpp bloom_filter.hpp
a.exe 500 5 5000 500
```