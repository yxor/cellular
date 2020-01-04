#include <SDL2/SDL.h>
#ifndef AUTOMATA
#define AUTOMATA

#define PREDATOR 1
#define PREY 2

#define PREDATOR_COLOR 0, 0, 255, 255
#define PREY_COLOR 255, 0, 0, 255


struct automata {
    int* map;
    int* cmap;
    int height;
    int width;
};

typedef struct automata Automata;

Automata* automata_init(int width, int height);
void automata_destroy(Automata* a);
void automata_render(Automata* a, SDL_Renderer *renderer);
void automata_progress(Automata* a);
int automata_get_coords(Automata* a, int x, int y);

#endif