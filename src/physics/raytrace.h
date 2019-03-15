#ifndef FICTIONAL_COUSCOUS_RAYTRACE_H
#define FICTIONAL_COUSCOUS_RAYTRACE_H

#include "../world/world.h"
#include "../maths/vec2d.h"
#include "../maths/double.h"
#include "../maths/geometry.h"
#include <stdbool.h>

#define MAX_BOUNCES 10

struct MaybePosition2D {
  Vec2D pos;
  bool success;
};
typedef struct MaybePosition2D MaybePosition2D;

struct Hit {
  Line2D* line;
  double dist;
};
typedef struct Hit Hit;

struct RayIntersection {
  size_t index;
  Hit hits[MAX_BOUNCES];
  bool success;
};
typedef struct RayIntersection RayIntersection;

MaybePosition2D intersect2D(const Line2D *a, const Line2D *b);
RayIntersection cast_ray(const Lines *lines, const Line2D *ray);

#endif //FICTIONAL_COUSCOUS_RAYTRACE_H
