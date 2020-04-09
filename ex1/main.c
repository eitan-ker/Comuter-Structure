#include <stdlib.h>
#include <stdio.h>
#include "bytes.h"

int main()
{
	byte_t* bytes = create_bytes("Course_123.csv");
	print_bytes(bytes, stdout);
	set_stud(bytes, 5, 3, 2);
	print_bytes(bytes, stdout);
	float average = average_stud(bytes, 5);
	printf("%.1f\n", average);
	average = average_ans(bytes, 3);
	printf("%.1f\n", average);
	free(bytes);
}
