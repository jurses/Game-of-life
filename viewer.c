#include "viewer.h"

GComponents_t *createGComponents(int width, int height, int scale)
{
    GComponents_t *g = (GComponents_t *)malloc(sizeof(GComponents_t));
    g->window = SDL_CreateWindow("Game of live", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        scale * width, scale * height, 0);
    g->renderer = SDL_CreateRenderer(g->window, -1, 0);
    g->texture = SDL_CreateTexture(g->renderer, SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STATIC, width, height);

    return g;    
}

void freeGComponents(GComponents_t *g)
{
    SDL_DestroyWindow(g->window);
    SDL_DestroyRenderer(g->renderer);
    SDL_DestroyTexture(g->texture);
}

void copyMatrix2Pixels(Matrix_t *m, Uint32 *p)
{
    for (int i = 1; i <= m->height; i++)
        for (int j = 1; j <= m->width; j++)
        {
            *p = m->matrix[i][j] ? 0 : -1;
            p++;
        }
}

void copyPixels2Matrix(Uint32 *p, Matrix_t *m)
{
    for (int i = 1; i <= m->height; i++)
        for (int j = 1; j <= m->width; j++)
        {
            if (*p == -1)
                m->matrix[i][j] = 0;
            else if (*p == 0)
                m->matrix[i][j] = 1;

            p++;
        }
}

void printMatrix(Matrix_t *m)
{
    for (int i = 0; i < m->height + 2; i++)
    {
        for (int j = 0; j < m->width + 2; j++)
            printf("%c ", m->matrix[i][j] ? '*' : '`');
        printf("\n");
    }
}