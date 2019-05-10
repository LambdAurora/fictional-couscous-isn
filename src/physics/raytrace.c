#include "raytrace.h"

#include <stdio.h>

MaybePosition2D intersect2D(const Line2D* a, const Line2D* b) {
    MaybePosition2D res;
    if (approx_eq(dot2D(&(a->vec), &(b->vec)), 1) || approx_eq(dot2D(&(a->vec), &(b->vec)), -1)) {
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

        // printf("%lf %lf\n", s, t);

        res.success = approx_lt(s, a->length) && approx_gt(s, 0) && approx_lt(t, b->length) && approx_gt(t, 0);
        return res;
    }
}

MaybePosition2D cast_ray(const World* world, const Line2D* ray, size_t layer, size_t* hit) {
  MaybePosition2D hit_pos;
  size_t n;
  *hit = 0;
  hit_pos.success = false;
  const Lines* lines = &world->layers[layer].walls;
  for (n = 0; n < lines->length; n++) {
      MaybePosition2D intersection = intersect2D(&(lines->lines[n]), ray);
      if (intersection.success) {
          if (!hit_pos.success || dist2D(&(ray->pos), &(intersection.pos)) < dist2D(&(ray->pos), &(hit_pos.pos))) {
              *hit = n;
              hit_pos.success = true;
              hit_pos.pos.x = intersection.pos.x;
              hit_pos.pos.y = intersection.pos.y;
          }
      }
  }
  return hit_pos;
}

RayIntersection send_ray(const World* world, const Line2D* ray, size_t layer) {
    RayIntersection result;
    result.n_hits = 0;
    int bounces = 0;
    int p;
    bool loop = true;
    double dist = 0;
    Line2D ray2 = *ray;

    size_t current_layer = layer;

    for (p = 0; p < MAX_BOUNCES; p++) {
        result.hits[p].line = NULL;
        result.hits[p].exists = NULL;
    }
    while (loop && bounces < MAX_BOUNCES) {
        size_t hit;
        MaybePosition2D hit_pos = cast_ray(world, &ray2, current_layer, &hit);
        const Lines* lines = &world->layers[current_layer].walls;
        if (hit_pos.success) {
            dist += dist2D(&(ray2.pos), &(hit_pos.pos));
            result.n_hits++;
            result.success = true;
            result.hits[bounces].pos = hit_pos.pos;
            result.hits[bounces].line = &(lines->lines[hit]);
            result.hits[bounces].dist = dist;
            Vec2D normal = Vec2D_normal(&result.hits[bounces].line->vec);
            result.hits[bounces].side = dot2D(&normal, &ray2.vec) > 0;
            switch (lines->lines[hit].type) {
                case NORMAL_LINE:
                    loop = false;
                    break;
                case BOUNCE_LINE:
                    ray2.pos.x = hit_pos.pos.x;
                    ray2.pos.y = hit_pos.pos.y;
                    {
                        Vec2D normal = Vec2D_normal(&lines->lines[hit].vec);
                        Vec2D bounce;
                        double d = dot2D(&normal, &ray2.vec);
                        bounce.x = ray2.vec.x - 2 * d * normal.x;
                        bounce.y = ray2.vec.y - 2 * d * normal.y;
                        ray2.vec = bounce;
                    }
                    ray2.pos.x += 2 * EPSILON * ray2.vec.x;
                    ray2.pos.y += 2 * EPSILON * ray2.vec.y;
                    break;
                case TELEPORT_LINE:
                    // rotation and layer changing isn't supported yet, this will have to be done
                    {
                        TeleportTarget* loc = (TeleportTarget*)lines->lines[hit].data;
                        // double n_rot_x = ;
                        ray2.pos.x = hit_pos.pos.x - lines->lines[hit].pos.x + loc->line->pos.x;
                        ray2.pos.y = hit_pos.pos.y - lines->lines[hit].pos.y + loc->line->pos.y;
                    }
                    ray2.pos.x += ray2.vec.x * EPSILON * 2;
                    ray2.pos.y += ray2.vec.y * EPSILON * 2;
                    break;
                case TRANSPARENT_LINE:
                case GHOST_LINE:
                    ray2.pos.x = hit_pos.pos.x + ray2.vec.x * EPSILON * 2;
                    ray2.pos.y = hit_pos.pos.y + ray2.vec.y * EPSILON * 2;
                    break;

            }
        } else {
            loop = false;
        }
        bounces++;
    }
    return result;
}

TeleportTarget TeleportTarget_new(Line2D* line, size_t layer) {
    TeleportTarget res;
    res.line = line;
    res.layer = layer;
    return res;
}
