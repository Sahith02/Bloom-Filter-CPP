from key_generator.key_generator import generate

all_sizes_required = [(100, '100'), (500, '500'), (1000, '1K'), (5000, '5K'), (10000, '10K'), (50000, '50K'), (100000, '100K'), (500000, '500K')]

for file_size in all_sizes_required:
	OUTPUT_PATH = "./int_test_" + file_size[1] + ".txt"
	STRING_COUNT = file_size[0]

	output_file = open(OUTPUT_PATH, "w")

	for i in range(STRING_COUNT):
		integer = generate(
			num_of_atom = 1,
			min_atom_len = 3,
			max_atom_len = 9,
			type_of_value = "int",
			seed = i
		).get_key()

		integer = integer.lstrip("0")
		if(integer == ""):
			output_file.write("0" + "\n")
		else:
			output_file.write(integer + "\n")

	output_file.close()
	print("Done with " + OUTPUT_PATH)
