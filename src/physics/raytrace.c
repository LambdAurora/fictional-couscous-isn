#include "raytrace.h"

#include <stdio.h>

MaybePosition2D intersect2D(Line2D a, Line2D b) {
  MaybePosition2D res;
  if (approx_eq(dot2D(a.vec, b.vec), 1) || approx_eq(dot2D(a.vec, b.vec), -1)) {
    res.pos.x = 0;
    res.pos.y = 0;
    res.success = false;
    return res;
  } else {
    // TODO: explain & make prettier & redo the maths
    double wx = b.pos.x - a.pos.x;
    double wy = b.pos.y - a.pos.y;

    double s = -(b.vec.y * wx - b.vec.x * wy) / (b.vec.x * a.vec.y - b.vec.y * a.vec.x);
    double t = -(a.vec.x * wy - a.vec.y * wx) / (a.vec.x * b.vec.y - a.vec.y * b.vec.x);

    res.pos.x = a.pos.x + a.vec.x * s;
    res.pos.y = a.pos.y + a.vec.y * s;

    printf("%lf %lf\n", s, t);

    res.success = approx_lt(s, a.length) && approx_gt(s, 0) && approx_lt(t, b.length) && approx_gt(t, 0);
    return res;
  }
}
