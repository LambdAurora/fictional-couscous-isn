#ifndef FICTIONAL_COUSCOUS_RAYTRACING_H
#define FICTIONAL_COUSCOUS_RAYTRACING_H

#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>
#include "easysdl.h"
#include "../maths/geometry.h"
#include "../maths/vec2d.h"
#include "../maths/double.h"
#include "../physics/raytrace.h"
#include "color.h"

void sweep(
  int width, int height,
  Lines *lines,
  const Vec2D *camera_pos,
  double rotation, double fov, double length,
  const Color *bg, double mist_length
);

#define DRAW_OUTLINE

#endif //FICTIONAL_COUSCOUS_RAYTRACING_H
