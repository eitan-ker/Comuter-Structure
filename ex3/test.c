#include <stdio.h>
long switch1(long*,long*,long);
extern long switch2(long*,long*,long);
int main ()
{
	long x, y, z, result;
	long x1, y1, z1, result1;
	printf ("Enter x, y and z: ");
	scanf ("%ld %ld %ld", &x, &y, &z);
        x1=x; y1=y; z1=z; result1=result;

	printf("Calling: result = switch1(x, y, z)\n");
	result = switch1(&x, &y, z);
	printf("result = %ld, x = %ld, y = %ld, z = %ld\n", result, x, y, z);
	x=x1; y=y1; z=z1; result=result1;

	printf("Calling: result = switch2(x, y, z)\n");
	result = switch2(&x, &y, z);
	printf("result = %ld, x = %ld, y = %ld, z = %ld\n", result, x, y, z);
	return 0;
}
