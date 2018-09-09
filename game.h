#ifndef GAME_H
#define GAME_H

#include "matrix.h"
#include "viewer.h"

// Do next iteration matrix
void step(Matrix_t *);

// Counts living cell around
int countNeighbor(Matrix_t *, int, int);

#endif // GAME_H
