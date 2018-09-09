#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "matrix.h"
#include "viewer.h"

int guiGameOfLife(int rows, int columns, int scale);
int cliGameOfLife(int rows, int columns);

// GUI MAIN PROGRAM
int main(int argc, char *argv[])
{
    int rows = 50, columns = 50, scale = 30;
    int guiMode = 1;

    if (argc != 5 && argc != 1)
    {
        fprintf(stderr, "Bad number of arguments: total = %d.\n", argc);
        printf("%s [-c|-i] <rows <columns> <scalle>.\n", argv[0]);
        return 1;
    }

    if (argc == 5)
    {
        switch (argv[1][1])
        {
            case 'i':
                sscanf(argv[2], "%d", &rows);
                sscanf(argv[3], "%d", &columns);
                sscanf(argv[4], "%d", &scale);
                guiMode = 1;
            break;

            case 'c':
                sscanf(argv[2], "%d", &rows);
                sscanf(argv[3], "%d", &columns);
                guiMode = 0;
            break;
        }
    }

    if (guiMode)
        return guiGameOfLife(rows, columns, scale);
    else
        return cliGameOfLife(rows, columns);
}

int cliGameOfLife(int rows, int columns)
{
    Matrix_t *m = createMatrix(rows, columns);

    randMatrix(m);
    cleanBorder(m);

    while ('q' != getchar())
    {
        printMatrix(m);
        step(m);
    }

    return 0;
}

int guiGameOfLife(int rows, int columns, int scale)
{
    int quit = 0;
    int mouseX, mouseY;
    SDL_Event event;
    Matrix_t *m;
    char *cliMatrix;
    
    SDL_Init(SDL_INIT_VIDEO);
    int gameRunning = 0;
    int leftMouseButtonDown = 0;


    cliMatrix = (char *)calloc((rows + 2) * (columns + 2), sizeof(char));

    m = createMatrix(rows, columns);
    cleanBorder(m);

    Uint32 *pixels = (Uint32 *)calloc(rows * columns, sizeof(Uint32));
    GComponents_t *g = createGComponents(columns, rows, scale);

    copyMatrix2Pixels(m, pixels);

    while (!quit)
    {
        SDL_UpdateTexture(g->texture, NULL, (void *)pixels, columns * sizeof(Uint32));
        SDL_WaitEventTimeout(&event, 10);
        const Uint8 *state;
        switch (event.type)
        {
            case SDL_QUIT:
                quit = 1;
            break;
            case SDL_KEYDOWN:
                state = SDL_GetKeyboardState(NULL);
                if (state[SDL_SCANCODE_P] && gameRunning)
                    gameRunning = 0;
                else if (state[SDL_SCANCODE_P] && !gameRunning)
                    gameRunning = 1;
            break;
            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT)
                    leftMouseButtonDown = 0;
            break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    leftMouseButtonDown = 1;
                    gameRunning = 0;
                }
            break;
            case SDL_MOUSEMOTION:
                if (leftMouseButtonDown)
                {
                    mouseX = event.motion.x / scale;
                    mouseY = event.motion.y / scale;
                    pixels[mouseY * columns + mouseX] = 0;
                }
            break;
        }
        if (gameRunning)
        {
            copyPixels2Matrix(pixels, m);
            step(m);
            copyMatrix2Pixels(m, pixels);
        }
        SDL_RenderClear(g->renderer);
        SDL_RenderCopy(g->renderer, g->texture, NULL, NULL);
        SDL_RenderPresent(g->renderer);
    }

    free(pixels);
    free(cliMatrix);

    return 0;
}