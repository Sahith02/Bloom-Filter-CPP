from key_generator.key_generator import generate

OUTPUT_PATH = "./string_test_100k.txt"
STRING_COUNT = 100000


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
