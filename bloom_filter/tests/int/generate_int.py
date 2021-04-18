from key_generator.key_generator import generate

OUTPUT_PATH = "./int_test_100k.txt"
STRING_COUNT = 100000


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
