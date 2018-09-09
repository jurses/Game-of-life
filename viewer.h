#ifndef VIEWER_H
#define VIEWER_H

#include <SDL2/SDL.h>

#include "matrix.h"

typedef struct GComponents{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
} GComponents_t;

GComponents_t *createGComponents(int width, int height, int scale);
void freeGComponents(GComponents_t *g);

void copyPixels2Matrix(Uint32 *p, Matrix_t *m);
void copyMatrix2Pixels(Matrix_t *m, Uint32 *p);
void printMatrix(Matrix_t *m);

#endif // VIEWER_H