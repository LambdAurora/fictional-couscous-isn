#ifndef FICTIONAL_COUSCOUS_ISN_GAME_H
#define FICTIONAL_COUSCOUS_ISN_GAME_H

#include "world/world.h"

struct Game
{
    int width;
    int height;
    bool top_mode;
    bool draw_floor;
    int zoom;
    bool mouse_captured;
};
typedef struct Game Game;

void init_game(Game* game, int width, int height);

void render_top_mode(Game* g, World* world);

void capture_mouse(Game* game);

void free_mouse(Game* game);

#endif //FICTIONAL_COUSCOUS_ISN_GAME_H
