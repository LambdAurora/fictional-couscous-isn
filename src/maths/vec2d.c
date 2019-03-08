#include "vec2d.h"

double dot2D(Vec2D a, Vec2D b) {
  return a.x * b.x + a.y * b.y;
}

Vec2D norm(Vec2D in) {
  if (approx_eq(in.x, 0) && approx_eq(in.y, 0)) {
    // ERROR ERROR
    fprintf(stderr, "Tried to normalize a null vector!\n");
  }
  double l = sqrt(in.x * in.x + in.y * in.y);
  Vec2D res;
  res.x = in.x / l;
  res.y = in.y / l;
}
