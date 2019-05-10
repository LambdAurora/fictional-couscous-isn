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

    if (wall.type == GHOST_LINE) { // c'est un mur "fantôme": on fait comme si il n'était pas là
      world->player_position = result.pos;
      world->player_position.x += EPSILON * 4 * movement.vec.x;
      world->player_position.y += EPSILON * 4 * movement.vec.y;
    }
    else if (wall.type != TELEPORT_LINE) {
      //world->player_position = result.pos;
      return;
    } else { // On a affaire à un mur téléporteur.
      TeleportTarget* loc = (TeleportTarget*)wall.data;
      world->player_position.x = result.pos.x - wall.pos.x + loc->line->pos.x;
      world->player_position.y = result.pos.y - wall.pos.y + loc->line->pos.y;
      world->player_position.x += EPSILON * 4 * movement.vec.x;
      world->player_position.y += EPSILON * 4 * movement.vec.y;
    }

    double distance = dist2D(&result.pos, &movement.pos);
    movement.length -= distance;
    movement.pos = world->player_position;


    bounces++;
  }
}
