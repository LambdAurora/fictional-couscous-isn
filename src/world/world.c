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

#define FIX_POSITION(pos, movement) \
    pos.x += movement.vec.x * 3 * EPSILON; \
    pos.y += movement.vec.y * 3 * EPSILON;


void World_move(World* world, const Vec2D* new_ppos) {
  // Mouvement à effectuer.
  Line2D movement = Line2D_new(&(world->player_position), new_ppos);

  size_t bounces = 0;
  while (bounces < MAX_BOUNCES) {
    size_t hit;
    MaybePosition2D result = cast_ray(world, &movement, 0, &hit);

    // On ne touche aucun mur, on peut bouger.
    if (!result.success) {
      world->player_position.x = movement.pos.x + movement.length * movement.vec.x;
      world->player_position.y = movement.pos.y + movement.length * movement.vec.y;
      return;
    }

    // On touche un mur, c'est l'heure des calculs!
    Line2D wall = world->layers[0].walls.lines[hit]; // Le mur touché.

    if (wall.type == GHOST_LINE) {
        world->player_position = result.pos;
        FIX_POSITION(world->player_position, movement)
    } else if (wall.type == TELEPORT_LINE) {
        // On a affaire à un mur téléporteur.
        // Récupérons la position de téléportation du mur.
        TeleportTarget* loc = (TeleportTarget*) wall.data;
        // Coordonnée X dans le repère du mur.
        double rot_dot_ldir = dot2D(&(wall.vec), &(movement.vec));
        Vec2D l_norm = Vec2D_normal(&(wall.vec));
        double rot_dot_lnorm = dot2D(&l_norm, &(movement.vec));

        Vec2D t_norm = Vec2D_normal(&loc->line->vec);

        // Coordonnées du vecteur du mouvement dans le repère du monde à la sortie du portail.
        double n_rot_x = t_norm.x * rot_dot_lnorm + loc->line->vec.x * rot_dot_ldir;
        double n_rot_y = t_norm.y * rot_dot_lnorm + loc->line->vec.y * rot_dot_ldir;

        // Distance du point d'entrée par rapport au point d'origine du mur.
        double entry_dist = dist2D(&result.pos, &(wall.pos));

        // Mise à jour de la position du joueur.
        world->player_position.x = loc->line->pos.x + entry_dist * loc->line->vec.x;
        world->player_position.y = loc->line->pos.y + entry_dist * loc->line->vec.y;

        movement.vec.x = n_rot_x;
        movement.vec.y = n_rot_y;

        // On a u*u'=||u||*||u'||*cos(u,u') or les vecteurs u et u' sont normalisés alors: u*u'=cos(u,u')
        // Alors: cos(u,u')=u*u'
        // D'où: |u,u'|=cos^-1(u*u')
        double angle = acos(dot2D(&(wall.vec), &(loc->line->vec)));
        // Le vecteur du portail d'arrivé tourné à partir de l'angle.
        Vec2D rotated = Vec2D_rotate(&(loc->line->vec), angle);
        // On vérifie que le vecteur tourné soit égal au vecteur du portail d'entrée pour déterminer l'orientation de l'angle.
        if (Vec2D_eq(&wall.vec, &rotated))
            world->player_angle -= angle;
        else
            world->player_angle += angle;

        // On évite de bloquer le joueur.
        FIX_POSITION(world->player_position, movement)
    } else {
        // C'est aucun des deux: on arrête.
        // world->player_position = result.pos;
        return;
    }

    // On met à jour le mouvement.
    double distance = dist2D(&(result.pos), &(movement.pos));
    movement.length -= distance;
    movement.pos = world->player_position;

    bounces++;
  }
}
