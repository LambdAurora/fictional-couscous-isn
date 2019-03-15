#ifndef FICTIONAL_COUSCOUS_ISN_WORLD_H
#define FICTIONAL_COUSCOUS_ISN_WORLD_H

#include "../base.h"
#include "../maths/geometry.h"

typedef Vec2D Position;

struct Level {
    Position spawn_position;
    Lines walls;
};
typedef struct Level Level;

struct World {
    uint64_t age;
    Position player_position;
    double player_angle;
    Level level;
};
typedef struct World World;

void World_use_level(World *world, const Level *level);

void World_update(World *world);

#endif //FICTIONAL_COUSCOUS_ISN_WORLD_H
