/*
 * Copyright © 2019 LambdAurora <aurora42lambda@gmail.com>, Shad Amethyst <shad.amethyst@gmail.com>
 *
 * This file is part of fictional_couscous_isn.
 *
 * Licensed under the MIT license. For more information,
 * see the LICENSE file.
 */

#ifndef FICTIONAL_COUSCOUS_RAYTRACING_H
#define FICTIONAL_COUSCOUS_RAYTRACING_H

#include "../game.h"
#include "easysdl.h"
#include "../maths/line.h"
#include "../maths/vec2d.h"
#include "../maths/double.h"
#include "../physics/raytrace.h"
#include "color.h"
#include "texture.h"
#include "room.h"
#include <stdlib.h>

#define DISTANCE_THRESHOLD 0.01 // trust me, that'll make things better!

#define HEIGHT_ADJUST 0.21

/*!
 * Fait le rendu du monde en perspective à la première personne.
 * @param game Instance de Game, contenant les options du jeu
 * @param world Instance de World, d'où sera lu les murs, la position du joueur et les salles
 * @param layer (unused) Index du niveau dans World
 * @param fov Field of vision, valeur en radians du secteur d'angle du champ de vision
 * @param length Distance maximale visible
 * @param bg Couleur du fond
 * @param mist_length Valeur représentant l'intensité du brouillard; des valeurs plus grandes indiquent un brouillard moins intense
 */
void draw(
        const Game* game,
        const World* world,
        size_t layer, double fov, double length,
        const Color* bg, double mist_length
);


/*!
 * Calcule la hauteur qu'un mur devrait avoir
 * @param distance La distance par rapport à la caméra du mur
 * @param angle L'angle entre le milieu du champ de vision et l'intersection avec le mur
 * @param height Hauteur de la fenêtre
 * @parma width Largeur de la fenêtre
 * @return Hauteur du mur
 */
double calc_height(double distance, double angle, int height, int width);

/*!
 * Retourne si la texture est complexe (checkerboard ou image) ou non
 * @return `true` si oui, `false` si non
 */
bool is_complex_texture(void* tex);

#endif //FICTIONAL_COUSCOUS_RAYTRACING_H
