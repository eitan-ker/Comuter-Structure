#include <stdio.h>
extern int kefel(int);
int main ()
{
	int k, x;
	printf ("Enter k and x: ");
	scanf ("%d %d", &k, &x);
	printf("\nUsing k * x:\n");
	printf ("%d * %d = %d\n", k, x, k * x);
	printf("\nUsing kefel(%d):\n", x);
	printf ("%d * %d = %d\n", k, x, kefel(x));
	return 0;
}