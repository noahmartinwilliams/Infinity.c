#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

typedef long int inf_length;
typedef uint8_t byte;


byte *stream=NULL;
inf_length num_bytes=0;

uint8_t* increment_bits()
{
	bool full=true;
	inf_length c;
	for (c=0; c<num_bytes; c++) {
		if (stream[c]==UCHAR_MAX) {
			stream[c]=0;
			continue;
		} else {
			stream[c]++;
			full=false;
			break;
		}
	}

	if (full) {
		num_bytes++;
		stream=realloc(stream, num_bytes*sizeof(byte));
		stream[num_bytes-1]=1;
		for (c=0; c<num_bytes-1; c++) {
			stream[c]=0;
		}
	}

	return stream;
}

int main(int argc, char *argv[])
{
	/*planned getopt options: 
		-b bits
		-d decimal
		-o octal
		-h hexadecimal
		-x hexadicimal
		-r raw
		-a use alphabet as digits in a base 26 system.
		-D define your own "numbers". You'll provide a text string that has each character act as its own "digit" in a 
		base whatever number system
		-l limit the amount of output (for weenies who can't handle an infinite amount of information and/or don't have an infinite
		amount of memory).
		*/

	num_bytes++;
	stream=realloc(stream, num_bytes*sizeof(byte));
	stream[num_bytes-1]=0;
	while (1) {
		increment_bits();
		inf_length x;
		for (x=num_bytes-1; x>=0; x--) {
			printf("%c", stream[x]);
		}
	}
	return 0;
}
