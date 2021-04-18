from key_generator.key_generator import generate

OUTPUT_PATH = "./double_test_100.txt"
STRING_COUNT = 100


output_file = open(OUTPUT_PATH, "w")

for i in range(STRING_COUNT):
	integer_before_dot = generate(
		num_of_atom = 1,
		min_atom_len = 1,
		max_atom_len = 6,
		type_of_value = "int",
		seed = i
	).get_key()

	integer_after_dot = generate(
		num_of_atom = 1,
		min_atom_len = 1,
		max_atom_len = 6,
		type_of_value = "int",
		seed = i
	).get_key()

	integer_before_dot = integer_before_dot.lstrip("0")
	integer_after_dot = integer_after_dot.rstrip("0")
	integer_before_dot = integer_before_dot.lstrip("0") if integer_before_dot != "" else "0"
	integer_after_dot = integer_after_dot.rstrip("0") if integer_after_dot != "" else "0"
	output_file.write(integer_before_dot + "." + integer_after_dot + "\n")

output_file.close()
