#include "world.h"

// TODO: fix
void World_init(World* world, Position spawn_pos) {
    world->spawn_position = spawn_pos;
    world->player_position = spawn_pos;
    world->player_angle = 0.0;
}

void World_update(World* world) {
    world->age++;

    // Check if the player is out-of-bound:
    //
}
