#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <unistd.h>
#include <getopt.h>

typedef long int inf_length;
typedef uint8_t byte;


bool raw_print=true;
byte *stream=NULL;
inf_length num_bytes=0;
bool use_pseudo_random=false;

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

void print(char c)
{
	if (raw_print)
		printf("%c", c);
	else {
		printf("%d", (c & 0x80)>>7);
		printf("%d", (c & 0x40)>>6);
		printf("%d", (c & 0x20)>>5);
		printf("%d", (c & 0x10)>>4);
		printf("%d", (c & 0x08)>>3);
		printf("%d", (c & 0x04)>>2);
		printf("%d", (c & 0x02)>>1);
		printf("%d", (c & 0x01)>>0);
	}
}

int main(int argc, char *argv[])
{
	/*planned getopt options: 
		-p print digits of pi (possibly converted into one of the following formats
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
		-m use up infinite memory.
		*/

	struct option long_options[]={
		{ "pseudo-random", no_argument, 0, 'r' },
		{ "infinite-memory", no_argument, 0, 'm' }
	};
	int option_index=0;
	while (1) {
		int c=getopt_long(argc, argv, "rm", long_options, &option_index);
		if (c==-1)
			break;
		switch (c) {
		case 'r':
			use_pseudo_random=true;
			break;
		case 'm':
			use_pseudo_random=false;
			break;
		}
	}

	if (!use_pseudo_random) {
		num_bytes++;
		stream=realloc(stream, num_bytes*sizeof(byte));
		stream[num_bytes-1]=0;
		while (1) {
			increment_bits();
			inf_length x;
			for (x=num_bytes-1; x>=0; x--) {
				print(stream[x]);
			}
		}
	} else {
		while (1) 
			printf("%c", (char) random()); /* Pffft. What kind of weenies don't have infinite memory? :/ */
			
	}
	return 0;
}
