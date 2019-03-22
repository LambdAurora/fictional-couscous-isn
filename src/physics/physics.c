#include "physics.h"

double get_distance_of(const Vec2D* pos, const Line2D* line) {
    Vec2D v = Vec2D_new(pos->x - line->pos.x, pos->y - line->pos.y);
    // Vecteur normal de la droite.
    Vec2D n = Vec2D_new(- line->vec.y, line->vec.x);
    // La distance entre la position et la ligne.
    return dot2D(&v, &n);
}

bool collide(const Vec2D* pos, const Line2D* line) {
    return lc_maths_abs(get_distance_of(pos, line)) < 0.01;
}

bool can_move(const Vec2D* old_pos, const Vec2D* new_pos, const Line2D* line) {
    Vec2D old_v = Vec2D_new(old_pos->x - line->pos.x , old_pos->y - line->pos.y);
    double a = dot2D(&old_v, &line->vec);
    return (get_distance_of(old_pos, line) > 0) == (get_distance_of(new_pos, line) > 0) || 0 >= a || a >= line->length;
}
