#include "game.h"

void step(Matrix_t *m)
{
    Matrix_t *mCopy;
    mCopy = createMatrix(m->height, m->width);

    copyMatrix(m, mCopy);

    for (int i = 1; i <= m->height; i++)
        for (int j = 1; j <= m->width; j++)
        {
            if (countNeighbor(m, i, j) == 3)
                mCopy->matrix[i][j] = 1;

            if (countNeighbor(m, i, j) < 2 || countNeighbor(m, i, j) > 3)
                mCopy->matrix[i][j] = 0;
        }
    

    copyMatrix(mCopy, m);

    cleanBorder(m);

    freeMatrix(mCopy);
}

int countNeighbor(Matrix_t *m, int i, int j)
{
    int count = 0;
    for (int ir = i - 1; ir <= i + 1; ir++)
        for (int jr = j - 1; jr <= j + 1; jr++)
            if (i != ir || j != jr)
                count += m->matrix[ir][jr];

    return count;
}