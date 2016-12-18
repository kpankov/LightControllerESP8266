/*
 * @author Konstantin Pankov (ksp-labs.com)
 */

#include <stdio.h>

#define MAX_LEN 200

int main(int argc, char **argv){
	FILE *input_file, *output_file;
	char buffer[MAX_LEN];
	char c;

	if (argc != 4) {
		printf("Usage: txtToCppConverter [input_file] [output_file] [var_name]\n");
		return 0;
	}

	input_file = fopen(argv[1], "r");
	output_file = fopen(argv[2], "w");

	fprintf(output_file, "const char %s[] = {", argv[3]);

	do {
		c = getc (input_file);
		if (c != EOF) {
			fprintf(output_file, "0x%02x, ", c);
    	} else {
    		fprintf(output_file, "0x00");
    	}
    } while (c != EOF);

	fprintf(output_file, "};");

	fclose(input_file);
	fclose(output_file);

	return 0;
}