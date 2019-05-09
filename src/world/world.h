#ifndef FICTIONAL_COUSCOUS_ISN_WORLD_H
#define FICTIONAL_COUSCOUS_ISN_WORLD_H

#include "../base.h"
#include "../maths/line.h"

#define N_LEVELS 1

typedef Vec2D Position;

struct Layer {
    Lines walls;
};
typedef struct Layer Layer;

struct World {
    uint64_t age;
    Position player_position;
    double player_angle;
    Position spawn_position;
    Layer* layers;
    size_t n_layers;
};
typedef struct World World;

void World_init(World* world, Position spawn_pos);

void World_update(World* world);

void World_move(World *world, const Vec2D* new_player_position);

#endif //FICTIONAL_COUSCOUS_ISN_WORLD_H
