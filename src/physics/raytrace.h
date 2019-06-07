/*
 * Copyright © 2019 LambdAurora <aurora42lambda@gmail.com>, Shad Amethyst <shad.amethyst@gmail.com>
 *
 * This file is part of fictional_couscous_isn.
 *
 * Licensed under the MIT license. For more information,
 * see the LICENSE file.
 */

#ifndef FICTIONAL_COUSCOUS_RAYTRACE_H
#define FICTIONAL_COUSCOUS_RAYTRACE_H

#include "../world/world.h"
#include "../maths/vec2d.h"
#include "../maths/double.h"
#include "../maths/line.h"
#include <stdbool.h>

#define MAX_BOUNCES 16

struct MaybePosition2D {
    Vec2D pos;
    bool success;
};
typedef struct MaybePosition2D MaybePosition2D;

struct Hit {
    Vec2D pos;
    Line2D* line;
    double dist;
    bool exists;
    bool side;
};
typedef struct Hit Hit;

struct RayIntersection {
    Hit hits[MAX_BOUNCES];
    size_t n_hits;
    bool success;
};
typedef struct RayIntersection RayIntersection;

struct TeleportTarget {
    Line2D* line;
    size_t layer;
};
typedef struct TeleportTarget TeleportTarget;

MaybePosition2D intersect2D(const Line2D* a, const Line2D* b);

MaybePosition2D cast_ray(const World* world, const Line2D* ray, size_t layer, size_t* hit);

RayIntersection send_ray(const World* world, const Line2D* ray, size_t level);

TeleportTarget TeleportTarget_new(Line2D* line, size_t layer);

#endif //FICTIONAL_COUSCOUS_RAYTRACE_H
