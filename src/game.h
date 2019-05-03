#ifndef FICTIONAL_COUSCOUS_ISN_GAME_H
#define FICTIONAL_COUSCOUS_ISN_GAME_H

#include "world/world.h"

struct Game 
{
    int width;
    int height;
    bool top_mode;
    int zoom;
};
typedef struct Game Game;

void init_game(Game* game, int width, int height);

void render_top_mode(Game* g, World* world);

#endif //FICTIONAL_COUSCOUS_ISN_GAME_H
