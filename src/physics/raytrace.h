#ifndef FICTIONAL_COUSCOUS_RAYTRACE_H
#define FICTIONAL_COUSCOUS_RAYTRACE_H

#include "../world/world.h"
#include "../maths/vec2d.h"
#include "../maths/double.h"
#include "../maths/geometry.h"
#include <stdbool.h>

#define MAX_BOUNCES 32

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
};
typedef struct Hit Hit;

struct RayIntersection {
    Hit hits[MAX_BOUNCES];
    size_t n_hits;
    bool success;
};
typedef struct RayIntersection RayIntersection;

MaybePosition2D intersect2D(const Line2D* a, const Line2D* b);

RayIntersection cast_ray(const World* world, const Line2D* ray, size_t level);

#endif //FICTIONAL_COUSCOUS_RAYTRACE_H
