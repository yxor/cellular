#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define SDL_MAIN_HANDLED
#include "automata.h"
#include <SDL2/SDL.h>

static const int width = 400;
static const int height = 400;


int main(int argc, char **argv)
{
    // initiating SDL stuff
    SDL_Event event;
    SDL_SetMainReady();
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Predator and prey", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    // setting automata stuff
    Automata* a = automata_init(width, height);
    
    bool running = true;
    while(running)
    {
        // Process events
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                running = false;
            }
        }

        // rendering automata
        automata_render(a, renderer);
        automata_progress(a);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}