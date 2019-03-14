#ifndef FICTIONAL_COUSCOUS_RAYTRACE_H
#define FICTIONAL_COUSCOUS_RAYTRACE_H

#include "../world/world.h"
#include "../maths/vec2d.h"
#include "../maths/double.h"
#include "../maths/geometry.h"
#include <stdbool.h>

struct MaybePosition2D {
  Vec2D pos;
  bool success;
};
typedef struct MaybePosition2D MaybePosition2D;

struct RayIntersection {
  size_t index;
  MaybePosition2D pos;
};
typedef struct RayIntersection RayIntersection;

MaybePosition2D intersect2D(Line2D a, Line2D b);
RayIntersection cast_ray(Lines lines, Line2D ray);

#endif //FICTIONAL_COUSCOUS_RAYTRACE_H
