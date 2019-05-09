#include "world.h"
#include "../physics/raytrace.h"

void World_init(World* world, Position spawn_pos) {
    world->spawn_position = spawn_pos;
    world->player_position = spawn_pos;
    world->player_angle = 0.0;
    world->n_rooms = 0;
}

void World_update(World* world) {
    world->age++;

    // Check if the player is out-of-bound:
    //
}

void World_move(World* world, const Vec2D* new_ppos) {
  // Mouvement à effectuer.
  Line2D movement = Line2D_new(&(world->player_position), new_ppos);

  size_t bounces = 0;
  while (bounces < MAX_BOUNCES) {
    size_t hit;
    MaybePosition2D result = cast_ray(world, &movement, 0, &hit);

    // On ne touche aucun mur, on peut bouger.
    if (!result.success) {
      world->player_position = *new_ppos;
      return;
    }

    // On touche un mur, c'est l'heure des calculs!
    Line2D wall = world->layers[0].walls.lines[hit]; // Le mur touché.

    if (wall.type != TELEPORT_LINE) {
      //world->player_position = result.pos;
      return;
    }

    // On a affaire à un mur téléporteur.

    bounces++;
  }
}
