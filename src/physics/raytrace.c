#include "raytrace.h"

#include <stdio.h>

MaybePosition2D intersect2D(const Line2D *a, const Line2D *b) {
  MaybePosition2D res;
  if (approx_eq(dot2D(a->vec, b->vec), 1) || approx_eq(dot2D(a->vec, b->vec), -1)) {
    res.pos.x = 0;
    res.pos.y = 0;
    res.success = false;
    return res;
  } else {
    // TODO: explain & make prettier & redo the maths
    double wx = b->pos.x - a->pos.x;
    double wy = b->pos.y - a->pos.y;

    double s = -(b->vec.y * wx - b->vec.x * wy) / (b->vec.x * a->vec.y - b->vec.y * a->vec.x);
    double t = -(a->vec.x * wy - a->vec.y * wx) / (a->vec.x * b->vec.y - a->vec.y * b->vec.x);

    res.pos.x = a->pos.x + a->vec.x * s;
    res.pos.y = a->pos.y + a->vec.y * s;

    // printf("%lf~%lf %lf~%lf\n", s, a->length, t, b->length);

    res.success = s < a->length && s > 0 && t < b->length && t > 0;

    return res;
  }
}

RayIntersection cast_ray(const Lines *lines, const Line2D *ray) {
  RayIntersection res;
  size_t n;
  for (n = 0; n < MAX_BOUNCES; n++) res.hits[n].line = NULL;
  int o = 0;
  double dist = 0;
  Line2D ray2 = *ray;
  while (o >= 0 && o < MAX_BOUNCES) {
    size_t hit = 0;
    MaybePosition2D res_pos;
    res_pos.success = false;
    for (n = 0; n < lines->length; n++) {
      MaybePosition2D i = intersect2D(&lines->lines[n], &ray2);
      if (i.success) {
        if (!res_pos.success || dist2D(ray2.pos, i.pos) < dist2D(ray2.pos, res_pos.pos)) {
          hit = n;
          res_pos.success = true;
          res_pos.pos.x = i.pos.x;
          res_pos.pos.y = i.pos.y;
        }
      }
    }
    if (res_pos.success) {
      res.success = true;
      // printf("Howdy!\n");
      dist += dist2D(ray2.pos, res_pos.pos);
      ray2.length -= dist2D(ray2.pos, res_pos.pos);
      res.hits[o].line = &lines->lines[hit];
      res.hits[o].dist = dist;
      o++;
      switch (lines->lines[hit].type) {
        case NORMAL_LINE:
          o = -1; // destructive hit
          break;
        case BOUNCE_LINE:
          ray2.pos.x = res_pos.pos.x;
          ray2.pos.y = res_pos.pos.y;
          Vec2D normal = Vec2D_normal(&lines->lines[hit].vec);
          if (dot2D(normal, ray2.vec) < 0) normal = Vec2D_mult(normal, -1);
          double d = 2*dot2D(ray2.vec, normal);
          Vec2D n_angle = Vec2D_new(ray2.vec.x - d*normal.x, ray2.vec.y - d*normal.y);
          ray2.pos.x -= EPSILON * 2 * normal.x;
          ray2.pos.y -= EPSILON * 2 * normal.y;
          ray2.vec = n_angle;
          break;
      }
    } else o = -1;
  }
  return res;
}
