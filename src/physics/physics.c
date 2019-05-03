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

// note that this isn't the best method out there to do collisions; with this method, the player won't be able to slide off the wall.
// A better, more discrete method would be to calculate by how much the player can advance, calculate and update the velocity it still has and redo the calculation. This only has a small performance cost, but greatly improves the user experience
// This method would also allow us to manipulate the position of the player at the same time, and to ~teleport~ it.
// For this, we need functions to tell us how much the player can go in one direction, in regards of a single line, which we will execute for every line and take the minimum
// Bouncing is a simple thing, a dot product between the normalized vector of the movement and the normal of the line that has been hit should be enough

bool can_move(const Vec2D* old_pos, const Vec2D* new_pos, const Line2D* line) {
    Vec2D old_v = Vec2D_new(old_pos->x - line->pos.x , old_pos->y - line->pos.y);
    double a = dot2D(&old_v, &line->vec);

    if (0 >= a || a >= line->length) return true;

    // distances to the line
    double d1 = get_distance_of(old_pos, line);
    double d2 = get_distance_of(new_pos, line);

    // distances to the ends of the line
    double d3 = get_distance_to_ends(old_pos, line);
    double d4 = get_distance_to_ends(new_pos, line);

    return (d1 > 0) == (d2 > 0) // on the same side of the line
        && (lc_maths_abs(d1) < lc_maths_abs(d2) || lc_maths_abs(d2) > PLAYER_RADIUS) // if we are going out or if we are far enough
        && (lc_maths_abs(d3) < lc_maths_abs(d4) || lc_maths_abs(d4) > PLAYER_RADIUS); // if we are going off or if we are far enough from the ends
}
