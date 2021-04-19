from key_generator.key_generator import generate

all_sizes_required = [(100, '100'), (500, '500'), (1000, '1k'), (5000, '5k'), (10000, '10k'), (25000, '25k'), (50000, '50k'), (100000, '100k')]

for file_size in all_sizes_required:
	OUTPUT_PATH = "./string_test_" + file_size[1] + ".txt"
	STRING_COUNT = file_size[0]

	output_file = open(OUTPUT_PATH, "w")

	for i in range(STRING_COUNT):
		string = ""

		recipient = generate(
			num_of_atom = 1,
			type_of_value = "hex",
			capital = "mix",
			extras = ["-", "_"],
			seed = i
		).get_key()

		domain = generate(
			num_of_atom = 2,
			separator = ".",
			min_atom_len = 3,
			max_atom_len = 5,
			type_of_value = "hex",
			capital = "mix",
			extras = ["-"],
			seed = i
		).get_key()

		string = recipient + "@" + domain
		output_file.write(string + "\n")

	output_file.close()
	print("Done with " + OUTPUT_PATH)
