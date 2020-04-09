#include <stdio.h>
#include <stdlib.h>
#define SIZE 16
void transpose(int *src, int *dst, int dim)
{
   int i, j;
   for (i = 0; i < dim; i++)
      for (j = 0; j < dim; j++)
         dst[j * dim + i] = src[i * dim + j];
}

void block_transpose(int *src, int *dst, int dim, int block_size)
{
   int i, j;
   int k, l;
   for(i = 0; i < dim; i += block_size)
      for(j = 0; j < dim; j += block_size)
 	    for(k = i; k < i + block_size; ++k)
       	  for(l = j; l < j + block_size; ++l)
 		      dst[l * dim + k] = src[k * dim + l];
}

void rotate(int *src, int *dst, int dim) 
{ // Rotate array - transpose and exchange rows
   int i, j;
   for (i = 0; i < dim; i++)
      for (j = 0; j < dim; j++)
         dst[(dim - 1 - j) * dim + i] = src[i * dim + j];
}

void block_rotate(int *src, int *dst, int dim, int block_size)
{
   int i, j;
   int k, l;
   for(i = 0; i < dim; i += block_size)
      for(j = 0; j < dim; j += block_size)
 	    for(k = i; k < i + block_size; ++k)
       	  for(l = j; l < j + block_size; ++l)
 		      dst[(dim - 1 - l) * dim + k] = src[k * dim + l];
}

void print_array(int *arr, int dim)
{
	int i, j;
	for (i = 0 ; i < dim ; ++i) {
		for (j = 0 ; j < dim ; ++j)
			printf ("%5d", arr[i * dim + j]);
		printf("\n");
	}
	printf("\n");
}
int main()
{
	int* A = (int*) malloc(sizeof(int) * SIZE * SIZE);
	int* B = (int*) malloc(sizeof(int) * SIZE * SIZE);
	int i, j;	
	for (i = 0 ; i < SIZE * SIZE ; ++i) A[i] = i; // Initialize array
	print_array(A, SIZE);
	transpose(A, B, SIZE); // Transpose array
	print_array(B, SIZE);
	block_transpose(A, B, SIZE, SIZE/4); // Block Transpose array
	print_array(B, SIZE);
	rotate(A, B, SIZE); // Rotate array
	print_array(B, SIZE);
	block_rotate(A, B, SIZE, SIZE/4);
	print_array(B, SIZE);
}
