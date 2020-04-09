/********************************************************
 * Kernels to be optimized for the CS:APP Performance Lab
 ********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

/* 
 * Please fill in the following team struct 
 */
team_t team = {
    "FC Barcelona",              /* Team name */

    "Meni Ashurov",     /* First member full name */
    "menash9288@gmail.com",  /* First member email address */

    "Eitan Kerzhner",   /* Second member full name (leave blank if none) */
    "eizzker@gmail.com"      /* Second member email addr (leave blank if none) */
};

/***************
 * ROTATE KERNEL
 ****************/

/******************************************************
 * Your different versions of the rotate kernel go here
 ******************************************************/

/* 
 * naive_rotate - The naive baseline version of rotate 
 */
char naive_rotate_descr[] = "naive_rotate: Naive baseline implementation";
void naive_rotate(int dim, pixel *src, pixel *dst) 
{
    int i, j;

    for (i = 0; i < dim; i++)
	for (j = 0; j < dim; j++)
	    dst[RIDX(dim-1-j, i, dim)] = src[RIDX(i, j, dim)];
}

/* 
 * rotate - Your current working version of rotate
 * IMPORTANT: This is the version you will be graded on
 */
char rotate_descr[] = "rotate: Current working version";
void meni_naive_rotate(int dim, pixel *src, pixel *dst) 
{
    int i, j;

    for (j = 0; j < dim; j++)
	for (i = 0; i < dim; i++)
	    dst[RIDX(dim-1-j, i, dim)] = src[RIDX(i, j, dim)];
}
void rotate(int dim, pixel *src, pixel *dst) 
{
    meni_naive_rotate(dim, src, dst);
}

/*********************************************************************
 * register_rotate_functions - Register all of your different versions
 *     of the rotate kernel with the driver by calling the
 *     add_rotate_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_rotate_functions() 
{
    add_rotate_function(&naive_rotate, naive_rotate_descr);   
    add_rotate_function(&rotate, rotate_descr);   
    /* ... Register additional test functions here */
}


/***************
 * SMOOTH KERNEL
 **************/

/***************************************************************
 * Various typedefs and helper functions for the smooth function
 * You may modify these any way you like.
 **************************************************************/

/* A struct used to compute averaged pixel value */
typedef struct {
    int red;
    int green;
    int blue;
    int num;
} pixel_sum;

/* Compute min and max of two integers, respectively */
static int min(int a, int b) { return (a < b ? a : b); }
static int max(int a, int b) { return (a > b ? a : b); }

/* 
 * initialize_pixel_sum - Initializes all fields of sum to 0 
 */
static void initialize_pixel_sum(pixel_sum *sum) 
{
    sum->red = sum->green = sum->blue = 0;
    sum->num = 0;
    return;
}

/* 
 * accumulate_sum - Accumulates field values of p in corresponding 
 * fields of sum 
 */
static void accumulate_sum(pixel_sum *sum, pixel p) 
{
    sum->red += (int) p.red;
    sum->green += (int) p.green;
    sum->blue += (int) p.blue;
    sum->num++;
    return;
}

/* 
 * assign_sum_to_pixel - Computes averaged pixel value in current_pixel 
 */
static void assign_sum_to_pixel(pixel *current_pixel, pixel_sum sum) 
{
    current_pixel->red = (unsigned short) (sum.red/sum.num);
    current_pixel->green = (unsigned short) (sum.green/sum.num);
    current_pixel->blue = (unsigned short) (sum.blue/sum.num);
    return;
}

/* 
 * avg - Returns averaged pixel value at (i,j) 
 */
static pixel avg(int dim, int i, int j, pixel *src) 
{
    int ii, jj;
    pixel_sum sum;
    pixel current_pixel;

    //initialize_pixel_sum(&sum);
    sum.red = sum.green = sum.blue = 0;
    sum.num = 0;
    for(ii = max(i-1, 0); ii <= min(i+1, dim-1); ii++) 
	for(jj = max(j-1, 0); jj <= min(j+1, dim-1); jj++) 
	    accumulate_sum(&sum, src[RIDX(ii, jj, dim)]);

    assign_sum_to_pixel(&current_pixel, sum);
    return current_pixel;
}

/******************************************************
 * Your different versions of the smooth kernel go here
 ******************************************************/

/*
 * naive_smooth - The naive baseline version of smooth 
 */
char naive_smooth_descr[] = "naive_smooth: Naive baseline implementation";
void naive_smooth(int dim, pixel *src, pixel *dst) 
{
    int i, j;

    for (i = 0; i < dim; i++)
	for (j = 0; j < dim; j++)
	    dst[RIDX(i, j, dim)] = avg(dim, i, j, src);
}

/*
 * smooth - Your current working version of smooth. 
 * IMPORTANT: This is the version you will be graded on
 */
char smooth_descr[] = "smooth: Current working version";
void eitan_smooth(int dim, pixel *src, pixel *dst) 
{
   int i, j;
    int accum_red, accum_green, accum_blue;

    // upper left corner
    accum_red = (int) src[RIDX(0, 0, dim)].red + (int) src[RIDX(0, 1, dim)].red
                + (int) src[RIDX(1, 0, dim)].red + (int) src[RIDX(1, 1, dim)].red;
    accum_green = (int) src[RIDX(0, 0, dim)].green + (int) src[RIDX(0, 1, dim)].green
                  + (int) src[RIDX(1, 0, dim)].green + (int) src[RIDX(1, 1, dim)].green;
    accum_blue = (int) src[RIDX(0, 0, dim)].blue + (int) src[RIDX(0, 1, dim)].blue
                 + (int) src[RIDX(1, 0, dim)].blue + (int) src[RIDX(1, 1, dim)].blue;
    dst[RIDX(0, 0, dim)].red = (unsigned short)(accum_red / 4);
    dst[RIDX(0, 0, dim)].green = (unsigned short)(accum_green / 4);
    dst[RIDX(0, 0, dim)].blue = (unsigned short)(accum_blue / 4);

    // initial down left corner
    accum_red = (int) src[RIDX(dim - 1, dim - 1, dim)].red + (int) src[RIDX(dim - 1, dim - 2, dim)].red
                + (int) src[RIDX(dim - 2, dim - 1, dim)].red + (int) src[RIDX(dim-2, dim-2, dim)].red;
    accum_green = (int) src[RIDX(dim - 1, dim - 1, dim)].green + (int) src[RIDX(dim - 1, dim - 2, dim)].green
                  + (int) src[RIDX(dim - 2, dim - 1, dim)].green + (int) src[RIDX(dim-2, dim-2, dim)].green;
    accum_blue = (int) src[RIDX(dim - 1, dim - 1, dim)].blue + (int) src[RIDX(dim - 1, dim - 2, dim)].blue
                 + (int) src[RIDX(dim - 2, dim - 1, dim)].blue + (int) src[RIDX(dim-2, dim-2, dim)].blue;
    dst[RIDX(dim - 1, dim - 1, dim)].red = (unsigned short)(accum_red / 4);
    dst[RIDX(dim - 1, dim - 1, dim)].green = (unsigned short)(accum_green / 4);
    dst[RIDX(dim - 1, dim - 1, dim)].blue = (unsigned short)(accum_blue / 4);

    // initial upper right corner
    accum_red = (int) src[RIDX(0, dim - 1, dim)].red + (int) src[RIDX(0, dim - 2, dim)].red
                + (int) src[RIDX(1, dim - 1, dim)].red + (int) src[RIDX(1, dim-2, dim)].red;
    accum_green = (int) src[RIDX(0, dim - 1, dim)].green + (int) src[RIDX(0, dim - 2, dim)].green
                  + (int) src[RIDX(1, dim - 1, dim)].green + (int) src[RIDX(1, dim-2, dim)].green;
    accum_blue = (int) src[RIDX(0, dim - 1, dim)].blue + (int) src[RIDX(0, dim - 2, dim)].blue
                 + (int) src[RIDX(1, dim - 1, dim)].blue + (int) src[RIDX(1, dim-2, dim)].blue;
    dst[RIDX(0, dim - 1, dim)].red = (unsigned short)(accum_red / 4);
    dst[RIDX(0, dim - 1, dim)].green = (unsigned short)(accum_green / 4);
    dst[RIDX(0, dim - 1, dim)].blue = (unsigned short)(accum_blue / 4);

    // initial down left corner
    accum_red = (int) src[RIDX(dim - 1, 0, dim)].red + (int) src[RIDX(dim - 1, 1, dim)].red
                + (int) src[RIDX(dim - 2, 0, dim)].red + (int) src[RIDX(dim - 2, 1, dim)].red;
    accum_green = (int) src[RIDX(dim - 1, 0, dim)].green + (int) src[RIDX(dim - 1, 1, dim)].green
                  + (int) src[RIDX(dim - 2, 0, dim)].green + (int) src[RIDX(dim - 2, 1, dim)].green;
    accum_blue = (int) src[RIDX(dim - 1, 0, dim)].blue + (int) src[RIDX(dim - 1, 1, dim)].blue
                 + (int) src[RIDX(dim - 2, 0, dim)].blue + (int) src[RIDX(dim - 2, 1, dim)].blue;
    dst[RIDX(dim - 1, 0, dim)].red = (unsigned short)(accum_red / 4);
    dst[RIDX(dim - 1, 0, dim)].green = (unsigned short)(accum_green / 4);
    dst[RIDX(dim - 1, 0, dim)].blue = (unsigned short)(accum_blue / 4);

    //initial upper row
    for(j = 1; j < dim-1; j++) {
        accum_red = (int) src[RIDX(0, j-1, dim)].red + (int) src[RIDX(0, j, dim)].red
                    + (int) src[RIDX(0, j + 1, dim)].red + (int) src[RIDX(1, j-1, dim)].red
                    + (int) src[RIDX(1, j, dim)].red + (int) src[RIDX(1, j+1, dim)].red;
        accum_green = (int) src[RIDX(0, j-1, dim)].green + (int) src[RIDX(0, j, dim)].green
                      + (int) src[RIDX(0, j + 1, dim)].green + (int) src[RIDX(1, j-1, dim)].green
                      + (int) src[RIDX(1, j, dim)].green + (int) src[RIDX(1, j+1, dim)].green;
        accum_blue = (int) src[RIDX(0, j-1, dim)].blue + (int) src[RIDX(0, j, dim)].blue
                     + (int) src[RIDX(0, j + 1, dim)].blue + (int) src[RIDX(1, j-1, dim)].blue
                     + (int) src[RIDX(1, j, dim)].blue + (int) src[RIDX(1, j+1, dim)].blue;
        dst[RIDX(0, j, dim)].red = (unsigned short)(accum_red / 6);
        dst[RIDX(0, j, dim)].green = (unsigned short)(accum_green / 6);
        dst[RIDX(0, j, dim)].blue = (unsigned short)(accum_blue / 6);
    }

    // initial lower row
    for(j = 1; j < dim-1; j++) {
        accum_red = (int) src[RIDX(dim-1, j-1, dim)].red + (int) src[RIDX(dim-1, j, dim)].red
                    + (int) src[RIDX(dim-1, j + 1, dim)].red + (int) src[RIDX(dim-2, j-1, dim)].red
                    + (int) src[RIDX(dim-2, j, dim)].red + (int) src[RIDX(dim-2, j+1, dim)].red;
        accum_green = (int) src[RIDX(dim-1, j-1, dim)].green + (int) src[RIDX(dim-1, j, dim)].green
                      + (int) src[RIDX(dim-1, j + 1, dim)].green + (int) src[RIDX(dim-2, j-1, dim)].green
                      + (int) src[RIDX(dim-2, j, dim)].green + (int) src[RIDX(dim-2, j+1, dim)].green;
        accum_blue = (int) src[RIDX(dim-1, j-1, dim)].blue + (int) src[RIDX(dim-1, j, dim)].blue
                     + (int) src[RIDX(dim-1, j + 1, dim)].blue + (int) src[RIDX(dim-2, j-1, dim)].blue
                     + (int) src[RIDX(dim-2, j, dim)].blue + (int) src[RIDX(dim-2, j+1, dim)].blue;
        dst[RIDX(dim-1, j, dim)].red = (unsigned short)(accum_red / 6);
        dst[RIDX(dim-1, j, dim)].green = (unsigned short)(accum_green / 6);
        dst[RIDX(dim-1, j, dim)].blue = (unsigned short)(accum_blue / 6);
    }

    //initial left col
    for (i = 1; i < dim-1; i++) {
        accum_red = (int) src[RIDX(i-1, 0, dim)].red + (int) src[RIDX(i, 0, dim)].red
                    + (int) src[RIDX(i+1, 0, dim)].red + (int) src[RIDX(i-1, 1, dim)].red
                    + (int) src[RIDX(i, 1, dim)].red + (int) src[RIDX(i+1, 1, dim)].red;
        accum_green = (int) src[RIDX(i-1, 0, dim)].green + (int) src[RIDX(i, 0, dim)].green
                      + (int) src[RIDX(i+1, 0, dim)].green + (int) src[RIDX(i-1, 1, dim)].green
                      + (int) src[RIDX(i, 1, dim)].green + (int) src[RIDX(i+1, 1, dim)].green;
        accum_blue = (int) src[RIDX(i-1, 0, dim)].blue + (int) src[RIDX(i, 0, dim)].blue
                     + (int) src[RIDX(i+1, 0, dim)].blue + (int) src[RIDX(i-1, 1, dim)].blue
                     + (int) src[RIDX(i, 1, dim)].blue + (int) src[RIDX(i+1, 1, dim)].blue;
        dst[RIDX(i, 0, dim)].red = (unsigned short)(accum_red / 6);
        dst[RIDX(i, 0, dim)].green = (unsigned short)(accum_green / 6);
        dst[RIDX(i, 0, dim)].blue = (unsigned short)(accum_blue / 6);
    }

    // initial right col
    for (i = 1; i < dim-1; i++) {
        accum_red = (int) src[RIDX(i-1, dim-1, dim)].red + (int) src[RIDX(i, dim-1, dim)].red
                    + (int) src[RIDX(i+1, dim-1, dim)].red + (int) src[RIDX(i-1, dim-2, dim)].red
                    + (int) src[RIDX(i, dim-2, dim)].red + (int) src[RIDX(i+1, dim-2, dim)].red;
        accum_green = (int) src[RIDX(i-1, dim-1, dim)].green + (int) src[RIDX(i, dim-1, dim)].green
                      + (int) src[RIDX(i+1, dim-1, dim)].green + (int) src[RIDX(i-1, dim-2, dim)].green
                      + (int) src[RIDX(i, dim-2, dim)].green + (int) src[RIDX(i+1, dim-2, dim)].green;
        accum_blue = (int) src[RIDX(i-1, dim-1, dim)].blue + (int) src[RIDX(i, dim-1, dim)].blue
                     + (int) src[RIDX(i+1, dim-1, dim)].blue + (int) src[RIDX(i-1, dim-2, dim)].blue
                     + (int) src[RIDX(i, dim-2, dim)].blue + (int) src[RIDX(i+1, dim-2, dim)].blue;
        dst[RIDX(i, dim-1, dim)].red = (unsigned short)(accum_red / 6);
        dst[RIDX(i, dim-1, dim)].green = (unsigned short)(accum_green / 6);
        dst[RIDX(i, dim-1, dim)].blue = (unsigned short)(accum_blue / 6);
    }

    // initial all the rest
    for(i = 1; i < dim-1; i++) {
        for (j = 1; j < dim-1; j++) {
            accum_red = (int) src[RIDX(i-1, j-1, dim)].red + (int) src[RIDX(i-1, j, dim)].red
                        + (int) src[RIDX(i-1, j + 1, dim)].red + (int) src[RIDX(i, j-1, dim)].red
                        + (int) src[RIDX(i, j, dim)].red + (int) src[RIDX(i, j + 1, dim)].red
                        + (int) src[RIDX(i+1, j-1, dim)].red + (int) src[RIDX(i+1, j, dim)].red
                        + (int) src[RIDX(i+1, j + 1, dim)].red;
            accum_green = (int) src[RIDX(i-1, j-1, dim)].green + (int) src[RIDX(i-1, j, dim)].green
                          + (int) src[RIDX(i-1, j + 1, dim)].green + (int) src[RIDX(i, j-1, dim)].green
                          + (int) src[RIDX(i, j, dim)].green + (int) src[RIDX(i, j + 1, dim)].green
                          + (int) src[RIDX(i+1, j-1, dim)].green + (int) src[RIDX(i+1, j, dim)].green
                          + (int) src[RIDX(i+1, j + 1, dim)].green;
            accum_blue = (int) src[RIDX(i-1, j-1, dim)].blue + (int) src[RIDX(i-1, j, dim)].blue
                         + (int) src[RIDX(i-1, j + 1, dim)].blue + (int) src[RIDX(i, j-1, dim)].blue
                         + (int) src[RIDX(i, j, dim)].blue + (int) src[RIDX(i, j + 1, dim)].blue
                         + (int) src[RIDX(i+1, j-1, dim)].blue + (int) src[RIDX(i+1, j, dim)].blue
                         + (int) src[RIDX(i+1, j + 1, dim)].blue;
            dst[RIDX(i, j, dim)].red = (unsigned short)(accum_red / 9);
            dst[RIDX(i, j, dim)].green = (unsigned short)(accum_green / 9);
            dst[RIDX(i, j, dim)].blue = (unsigned short)(accum_blue / 9);
        }
    }
}
void smooth(int dim, pixel *src, pixel *dst) 
{
    eitan_smooth(dim, src, dst);
}


/********************************************************************* 
 * register_smooth_functions - Register all of your different versions
 *     of the smooth kernel with the driver by calling the
 *     add_smooth_function() for each test function.  When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_smooth_functions() {
    add_smooth_function(&smooth, smooth_descr);
    add_smooth_function(&naive_smooth, naive_smooth_descr);
    /* ... Register additional test functions here */
}

