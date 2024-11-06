/* This program prints out a list of source files included in an executable
   made with DEPUI.  The library must be compiled with MX_DEBUG_MODULES for
	any modules to be found.

	The syntax is:
 	   demodule ex0.exe
*/

#include <stdlib.h>
#include <stdio.h>

static const char *marker = "MxModule";

int main(int argc, char *argv[])
{
	 FILE *stream;

	 int done = 0;
	 int count = 0;

	 const int len = strlen(marker);

	 /* Make sure we have an argument */
	 if (argc < 2) {
		  fprintf(stderr,
					 "Print out a list of DEPUI source files included in an executable made with "
					 "DEPUI. The library must be compiled with MX_DEBUG_MODULES for any module to" "to be found. \n" "\n"
					 "The syntax is: \n" "    demodule ex0.exe\n");
		  exit(1);
	 }

	 /* Open the input file */
#ifdef __DOS__
	 stream = fopen(argv[1], "rb");
#else
	 stream = fopen(argv[1], "r");
#endif
	 if (!stream) {
		  fprintf(stderr, "Could not open file\n");
		  exit(2);
	 }

	 while ((!done) && (!feof(stream))) {

		  /* Read a character in */
		  int c = getc(stream);

		  /* Does it match the marker */
		  if (c == marker[count])
				++count;
		  else
				count = 0;

		  /* Are we finished the marker */
		  if (count >= len) {

				/* Print the string out */
				c = getc(stream);
				while (c) {
					 putc(c, stdout);
					 c = getc(stream);
				}
				/* Seperate the module names on different lines */
				putc('\n', stdout);
		  }
	 }
	 fclose(stream);
	 return 0;
}
