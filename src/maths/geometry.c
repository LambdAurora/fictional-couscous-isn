#include "geometry.h"

Line2D Line2D_new(Vec2D from, Vec2D to) {
  Line2D res;
  if (Vec2D_eq(from, to)) { // that's a point, but heh
    res.pos.x = from.x;
    res.pos.y = from.y;
    res.vec.x = 1;
    res.vec.y = 0;
    res.length = 0;
  } else {
    Vec2D diff = Vec2D_sub(to, from);
    Vec2D norm = norm2D(diff);
    res.pos.x = from.x;
    res.pos.y = from.y;
    res.vec.x = norm.x;
    res.vec.y = norm.y;
    res.length = length2D(diff);
  }
  res.type = NORMAL_LINE;
  res.data = NULL;
  return res;
}
