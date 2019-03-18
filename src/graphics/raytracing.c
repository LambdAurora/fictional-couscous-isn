#include "raytracing.h"
#include <inttypes.h>

// TODO: replace `lines` with `world`
void sweep(
        int width, int height,
        const World* world,
        size_t layer,double fov, double length,
        const Color* bg, double mist_length
) {
    int x;
    double last_dist = 0;
    for (x = 0; x < width; x++) {
        double angle = ((double) x - (double) width / 2) / (double) width * 2 * fov;

        Line2D ray;
        ray.length = length;
        ray.pos = world->player_position;
        ray.vec.x = cos(angle + world->player_angle);
        ray.vec.y = sin(angle + world->player_angle);

        RayIntersection cast = cast_ray(world, &ray, layer);
        if (cast.success) {
            size_t n_hit;
            for (n_hit = cast.n_hits - 1; n_hit != -1; n_hit--) {
                Hit hit = cast.hits[n_hit];
                Line2D* line = hit.line;
                int h = (int) ((double) height * calc_height(hit.dist, angle));
                double mist = 1 - 1 / (1 + hit.dist * hit.dist / mist_length);

                switch (line->type) {
                    case NORMAL_LINE:
                        EZ_trace_rectangle_plein((uint32_t) x, (uint32_t) (height / 2 - h), 0, (uint32_t) h * 2, line->color.red, line->color.green, line->color.blue, mix(255, 0, mist));
                        break;
                    case BOUNCE_LINE:
                        EZ_trace_rectangle_plein((uint32_t) x, (uint32_t) (height / 2 - h), 0, (uint32_t) h * 2, line->color.red, line->color.green, line->color.blue, mix(32, 0, mist));
                        break;
                    case TRANSPARENT_LINE:
                        EZ_trace_rectangle_plein((uint32_t) x, (uint32_t) (height / 2 - h), 0, (uint32_t) h * 2, line->color.red, line->color.green, line->color.blue, mix(*(uint8_t*)line->data, 0, mist));
                }
            }
        }
    }
}

double calc_height(double distance, double angle) {
    return .5 / distance / cos(angle);
}
