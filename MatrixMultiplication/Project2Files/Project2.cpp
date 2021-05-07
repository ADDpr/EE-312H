// SuperStrings <Project2.cpp>
// EE 312 Project 1 submission by
// Anthony Do
// add3254
// Slip days used: <0>
// Spring 2021
// Copy-paste contents of this file at the top of every .c or .h file that you write or modify.

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "MatrixMultiply.h"

//Precondition: Takes two matricies that can be multiplied, A, and B, with A's R+C, and B's cols
//Postcondition: Returns the product in matrix C
void multiplyMatrices(
        double a[],
        const uint32_t a_rows, 
        const uint32_t a_cols, /*a_cols = b_rows */
        double b[],
        const uint32_t b_cols,
        double c[]) {
    uint32_t i, j, k, aI, bI, cI; //aI, bI, and cI are array indexes
    i = 0;
    
    while(i < a_rows){
        j = 0;
        while(j < b_cols){
            k = 0;
            cI = (i*b_cols)+j;
            c[cI] = 0;
            while(k < a_cols){ 
                aI = (i*a_cols)+k;
                bI = (k*b_cols)+j;
                c[cI]  += (a[aI])*(b[bI]);
                k++;
            }
            j++;
        }
        i++;
    }
    // https://en.wikipedia.org/wiki/Row-_and_column-major_order
}

//Precondition: Takes two matricies that can be multiplied, A, and B, with A's R+C, and B's cols
//Postcondition: Returns the product in dynamic matrix C
double** multiplyMatricesPtr(
        double** a,
        const uint32_t a_rows,
        const uint32_t a_cols,
        double** b,
        const uint32_t b_cols) {
    uint32_t i, j, k; 
    double **c;

    c = (double **)malloc(sizeof(double *) * a_rows);
    for (uint32_t i = 0; i < a_rows; i++) {
        *(c + i) = (double *)malloc(sizeof(double) * b_cols);
    }

    i = 0;
    while(i < a_rows){
        j = 0;
        while(j < b_cols){
            c[i][j] = 0;
            k = 0;
            while(k < a_cols){ 
                c[i][j] += (a[i][k])*(b[k][j]);
                k++;
            }
            j++;
        }
        i++;
    }
    return c;
}

// https://en.wikipedia.org/wiki/Transpose
//Precondition: Takes a pointer to a pointer of the input matrix and the number of rows and cols. of the matrix
//Postcondition: Returns the transpose of the input in dynamic matrix C
double** transposeMatrix(
         double** a,
         const uint32_t a_rows,
         const uint32_t a_cols) {
    double** b;
    uint32_t i, j;

    b = (double **)malloc(sizeof(double *) * a_cols);
    for (uint32_t i = 0; i < a_cols; i++) {
        *(b + i) = (double *)calloc(a_rows, sizeof(double));
    }
    
    i = 0;
    while(i < a_cols){
        j = 0;
        while(j < a_rows){
            b[i][j] = a[j][i];
            j++;
        }
        i++;
    }

    return b;
}
