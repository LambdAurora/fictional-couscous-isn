/*
 * Copyright © 2019 LambdAurora <aurora42lambda@gmail.com>, Shad Amethyst <shad.amethyst@gmail.com>
 *
 * This file is part of fictional_couscous_isn.
 *
 * Licensed under the MIT license. For more information,
 * see the LICENSE file.
 */

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

/*!
 * Structure représentant un monde.
 */
struct World {
    uint64_t age;
    // Position du joueur.
    Position player_position;
    // Angle de vision du joueur.
    double player_angle;
    // Point d'apparition.
    Position spawn_position;
    Layer* layers;
    size_t n_layers;
    // Salles.
    Room** rooms;
    size_t n_rooms;
};
typedef struct World World;

/*!
 * Initialise un monde avec un point d'apparition.
 *
 * @param world Instance du monde.
 * @param spawn_pos Point d'apparition.
 */
void World_init(World* world, Position spawn_pos);

/*!
 * Mets à jour le monde.
 *
 * @param world Instance du monde.
 */
void World_update(World* world);

/*!
 * Déplace le joueur dans une direction.
 *
 * @param world Instance du monde.
 * @param new_player_position Nouvelle position du joueur représentant son déplacement.
 */
void World_move(World *world, const Vec2D* new_player_position);

#endif //FICTIONAL_COUSCOUS_ISN_WORLD_H
