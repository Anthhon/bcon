#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>

#define MAX_SUBSTRING_SIZE (8)

// See more about how to these convertions work at:
// https://www.rapidtables.com/convert/number/

void fatal(char *message){
	(void)fprintf(stdout, "%s", message);
	exit(EXIT_FAILURE);
}

void display_usage()
{
    puts("Usage: program_name <number> [options]");
    puts("Options:");
    puts("-v\tVerbose mode");
}

void convert_to_octal(uint32_t number)
{
	if (number < 2) {
		(void)fprintf(stdout, "%i", number);
		return;
	}
	uint32_t remainder = number % 8;

	convert_to_octal(number >> 3);
	(void)fprintf(stdout, "%i", remainder);
}

void convert_to_hexadecimal(uint32_t number)
{
	if (number < 2) {
		(void)fprintf(stdout, "%i", number);
		return;
	}
	uint32_t remainder = number % 16;

	if (remainder > 9) remainder += 55; // Convert 10..15 to A..E
	else remainder += '0'; // Cast integer to character to avoid complexity

	convert_to_hexadecimal(number >> 4);
	(void)fprintf(stdout, "%c", remainder);
}

void convert_to_binary(uint32_t number)
{
	if (number < 2){
		(void)fprintf(stdout, "%i", number);
		return;
	}
	uint32_t remainder = number % 2;

	convert_to_binary(number >> 1);
	(void)fprintf(stdout, "%i", remainder);
}

int main(int argc, char **argv)
{
	if (argc == 1){
		display_usage();
		return 0;
	}

	bool verbose = false;
	bool need_help = false;
	char *endptr = NULL;

	errno = 0; // Reset errno before call
	uint32_t number = strtol(argv[1], &endptr, 10);

	// Error-check value conversion
	if (argv[1] == endptr)
		fatal("[!!] Invalid input (no digits found, 0 returned)\n");
	if (errno == ERANGE && number == LONG_MIN)
		fatal("[!!] Invalid input (underflow occurred)\n");
	if (errno == ERANGE && number == LONG_MAX)
		fatal("[!!] Invalid input (overflow occurred)\n");
	if (errno == EINVAL)  /* not in all c99 implementations - gcc OK */
		fatal("[!!] Invalid input (base contains unsupported value)\n");
	if (errno != 0 && number == 0)
		fatal("[!!] Invalid input (unspecified error occurred)\n");

	// Parse command-line arguments
	int option = 0;
	while ((option = getopt(argc, argv, ":v")) != -1){
		switch (option){
			case 'v':
				verbose = true;
				break;
			default:
				need_help = true;
				break;
		}
	}

	// Display help message if requested
	if (need_help){
		display_usage();
		return 0;
	}

	if (verbose)
		(void)fprintf(stdout, "BINARY\t HEXADECIMAL\t OCTAL\n");

	convert_to_binary(number);
	printf("\t");
	printf("0x");
	convert_to_hexadecimal(number);
	printf("\t");
	convert_to_octal(number);
	printf("\n");

	return 0;
}
