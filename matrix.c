#include "matrix.h"

Matrix_t *createMatrix(int height, int width)
{
    Matrix_t *m;
    m = (Matrix_t *)malloc(sizeof(Matrix_t));

    m->height = height;
    m->width = width;

    m->matrix = (int **)calloc(m->height + 2, sizeof(int **));
    for (int i = 0; i < m->height + 2; i++)
    {
        m->matrix[i] = (int *)calloc(m->width + 2, sizeof(int *));
        for (int j = 0; j < m->width; j++)
            m->matrix[i][j] = 0;
    }

    return m;
}

void freeMatrix(Matrix_t *m)
{
    for (int i = 0; i < m->height + 2; i++)
    {
        for (int j = 0; j < m->width + 2; j++)
            m->matrix[i][j] = 0;

        free(m->matrix[i]);
        m->matrix[i] = NULL;
    }

    free(m->matrix);
    m->matrix = NULL;
    m = NULL;
    free(m);
}

void copyMatrix(Matrix_t *orig, Matrix_t *dest)
{
    for (int i = 0; i < dest->height + 2; i++)
        for (int j = 0; j < dest->width + 2; j++)
            dest->matrix[i][j] = orig->matrix[i][j];
}

void cleanBorder(Matrix_t *m)
{
    for (int i = 1; i < m->height + 1; i++)
    {
        m->matrix[i][0] = 0;
        m->matrix[i][m->width + 1] = 0;
    }

    for (int j = 0; j < m->width + 2; j++)
    {
        m->matrix[0][j] = 0;
        m->matrix[m->height + 1][j] = 0;
    }
}

void randMatrix(Matrix_t *m)
{
    for (int i = 0; i < m->height; i++)
        for (int j = 0; j < m->width; j++)
            m->matrix[i][j] = rand() & 0x01;
}