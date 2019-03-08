#ifndef FICTIONAL_COUSCOUS_RAYTRACE_H
#define FICTIONAL_COUSCOUS_RAYTRACE_H

#include "../world/world.h"
#include "../maths/vec2d.h"
#include "../maths/double.h"
#include <stdbool.h>

struct MaybePosition2D {
  Vec2D pos;
  bool success;
};
typedef struct MaybePosition2D MaybePosition2D;

struct Line2D {
  Vec2D pos;
  Vec2D vec; // should be normalized
  double length;
};
typedef struct Line2D Line2D;

struct Lines {
  Line2D* lines;
  size_t length;
};
typedef struct Lines Lines;

struct RayIntersection {
  size_t index;
  MaybePosition2D pos;
};
typedef struct RayIntersection RayIntersection;

MaybePosition2D intersect2D(Line2D a, Line2D b);
RayIntersection cast_ray(Lines lines, Line2D ray);

#endif //FICTIONAL_COUSCOUS_RAYTRACE_H
