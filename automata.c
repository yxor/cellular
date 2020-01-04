#include "automata.h"
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

Automata* automata_init(int width, int height)
{
    srand(time(NULL));
    Automata* a = (Automata*) malloc(sizeof(Automata));
    assert(a != NULL);

    a->width = width;
    a->height = height;

    a->map = (int*) malloc(height * width * sizeof(int));
    assert(a->map != NULL);

    a->cmap = (int*) malloc(height * width * sizeof(int));
    assert(a->map != NULL);

    for(int i = 0; i < height * width; i++)
    {
        a->map[i] = rand() % 3;
    }

    return a;
}


void automata_destroy(Automata* a)
{
    assert(a != NULL);

    free(a->map);
    free(a);
}


void automata_render(Automata* a, SDL_Renderer* renderer)
{
    int creature;
    for(int x = 0; x < a->width; x++)
    {
        for(int y = 0; y < a->height; y++)
        {
            creature = a->map[x + y * a->height];
            switch(creature)
            {
                case PREDATOR:
                    SDL_SetRenderDrawColor(renderer, PREDATOR_COLOR);
                    break;
                case PREY:
                    SDL_SetRenderDrawColor(renderer, PREY_COLOR);
                    break;
                default:
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            }
            

            SDL_RenderDrawPoint(renderer, x, y);
        }
    }
}

void automata_progress(Automata* a)
{
    int creature;
    bool did_i_eat;
    memcpy(a->cmap, a->map, a->height * a->width * sizeof(int));
    for(int x = 1; x < a->width - 1; x++)
    {
        for(int y = 1; y < a->height - 1; y++)
        {
            creature = automata_get_coords(a, x, y);
            switch(creature)
            {
                case PREDATOR:
                    did_i_eat = false;
                    if (automata_get_coords(a, x-1, y) == PREY)
                    {
                        a->map[x - 1 + y * a->height] = PREDATOR;
                        did_i_eat = true;
                    }
                    if (automata_get_coords(a, x+1, y) == PREY)
                    {
                        a->map[x + 1 + y * a->height] = PREDATOR;
                        did_i_eat = true;
                    }
                    if (automata_get_coords(a, x, y-1) == PREY)
                    {
                        a->map[x  + (y-1) * a->height] = PREDATOR;
                        did_i_eat = true;
                    }
                    if (automata_get_coords(a, x, y+1) == PREY)
                    {
                        a->map[x - 1 + (y+1) * a->height] = PREDATOR;
                        did_i_eat = true;
                    }
                    if(!did_i_eat)
                        a->map[x + y * a->height] = 0;
                    break;
                case PREY:
                    if (automata_get_coords(a, x-1, y) == 0)
                        a->map[x - 1 + y * a->height] = PREY;
                    if (automata_get_coords(a, x+1, y) == 0)
                        a->map[x + 1 + y * a->height] = PREY;
                    if (automata_get_coords(a, x, y-1) == 0)
                        a->map[x  + (y-1) * a->height] = PREY;
                    if (automata_get_coords(a, x, y+1) == 0)
                        a->map[x - 1 + (y+1) * a->height] = PREY;
                    
                    break;
            }
            

        }
    }
}

int automata_get_coords(Automata* a, int x, int y)
{
    return a->cmap[x + y * a->height];
}