#include "world.h"

void World_use_level(World *world, const Level *level) {
    world->level = *level;
    world->player_position = world->level.spawn_position;
    world->player_angle = 0.0;
}

void World_update(World *world) {
    world->age++;

    // Check if the player is out-of-bound:
    //
}
