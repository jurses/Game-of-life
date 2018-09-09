#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct Matrix{
    int height;
    int width;
    int **matrix;
} Matrix_t;

void copyMatrix(Matrix_t *, Matrix_t*);
Matrix_t *createMatrix(int, int);
void freeMatrix(Matrix_t *);

// set to 0 or dead living cells in the border
void cleanBorder(Matrix_t *);

// useful to set randomly 1 or alive some cells in the matrix
void randMatrix(Matrix_t *);

#endif // MATRIX_H
