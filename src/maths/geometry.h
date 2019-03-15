#ifndef FICTIONAL_COUSCOUS_GEOMETRY_H
#define FICTIONAL_COUSCOUS_GEOMETRY_H

#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>
#include "double.h"
#include "vec2d.h"
#include "../graphics/color.h"

enum LINE_TYPE {
  NORMAL_LINE,
  BOUNCE_LINE
};
typedef enum LINE_TYPE LINE_TYPE;

struct Line2D {
  Vec2D pos;
  Vec2D vec; // should be normalized
  double length;
  uint8_t type;
  Color color;
  void* data;
};
typedef struct Line2D Line2D;

struct Lines {
  Line2D* lines;
  size_t length;
};
typedef struct Lines Lines;

Line2D Line2D_new(Vec2D from, Vec2D to);

#endif// FICTIONAL_COUSCOUS_GEOMETRY_H
