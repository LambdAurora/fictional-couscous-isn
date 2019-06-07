/*
 * Copyright © 2019 LambdAurora <aurora42lambda@gmail.com>, Shad Amethyst <shad.amethyst@gmail.com>
 *
 * This file is part of fictional_couscous_isn.
 *
 * Licensed under the MIT license. For more information,
 * see the LICENSE file.
 */

#include "physics.h"
#include "raytrace.h"

double get_distance_of(const Vec2D* pos, const Line2D* line) {
    Vec2D v = Vec2D_new(pos->x - line->pos.x, pos->y - line->pos.y);
    // Vecteur normal de la droite.
    Vec2D n = Vec2D_new(- line->vec.y, line->vec.x);
    // La distance entre la position et la ligne.
    return dot2D(&v, &n);
}

double get_distance_to_ends(const Vec2D* pos, const Line2D* line) {
    Vec2D v1 = Vec2D_new(pos->x - line->pos.x, pos->y - line->pos.y);
    Vec2D v2 = Vec2D_new(
        pos->x - line->pos.x - line->vec.x * line->length,
        pos->y - line->pos.y - line->vec.y / line->length
    );
    double d1 = length2D(&v1);
    double d2 = length2D(&v2);
    if (d1 < d2) return d1;
    else return d2;
}

bool collide(const Vec2D* pos, const Line2D* line) {
    return lc_maths_abs(get_distance_of(pos, line)) < PLAYER_RADIUS;
}
