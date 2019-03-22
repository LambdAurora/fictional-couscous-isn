#ifndef FICTIONAL_COUSCOUS_PHYSICS_H
#define FICTIONAL_COUSCOUS_PHYSICS_H

#include "../maths/geometry.h"

#define PLAYER_RADIUS 0.1

double get_distance_of(const Vec2D* pos, const Line2D* line);
double get_distance_to_ends(const Vec2D* pos, const Line2D* line);

bool collide(const Vec2D* pos, const Line2D* line);

bool can_move(const Vec2D* old_pos, const Vec2D* new_pos, const Line2D* line);

#endif //FICTIONAL_COUSCOUS_PHYSICS_H
