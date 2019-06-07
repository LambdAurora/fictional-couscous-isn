/*
 * Copyright © 2019 LambdAurora <aurora42lambda@gmail.com>, Shad Amethyst <shad.amethyst@gmail.com>
 *
 * This file is part of fictional_couscous_isn.
 *
 * Licensed under the MIT license. For more information,
 * see the LICENSE file.
 */

#ifndef FICTIONAL_COUSCOUS_ROOM_H
#define FICTIONAL_COUSCOUS_ROOM_H

#include "color.h"
#include "../base.h"

/*!
 * Représente une salle.
 */
struct Room {
  // Couleur de la salle.
  Color color;
  // Position de la salle.
  double x;
  double y;
  // Taille de la salle.
  double width;
  double height;
};
typedef struct Room Room;

/*!
 * Créer une nouvelle salle.
 *
 * @param x Coordonnée X de la salle.
 * @param y Coordonnée Y de la salle.
 * @param width Longueur de la salle.
 * @param height Largeur de la salle.
 */
Room Room_new(double x, double y, double width, double height);

/*!
 * Trouve la salle actuelle où le joueur est.
 *
 * @param world Instance du monde.
 */
Room* find_current_room(const struct World* world);

#endif // FICTIONAL_COUSCOUS_ROOM_H
