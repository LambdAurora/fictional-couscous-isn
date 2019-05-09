#include "draw.h"

// TODO: replace `lines` with `world`
void draw(
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

        RayIntersection cast = send_ray(world, &ray, layer);
        if (cast.success) {
            size_t n_hit;
            for (n_hit = cast.n_hits - 1; n_hit != -1; n_hit--) {
                Hit hit = cast.hits[n_hit];
                Line2D* line = hit.line;
                int h = (int) ((double) height * calc_height(hit.dist, angle));
                double mist = 1 - 1 / (1 + hit.dist * hit.dist / mist_length);

                switch (line->type) {
                    case BOUNCE_LINE:
                        (*line->texture)(x, h, height, line, &hit, (1 - mist) * 0.25);
                        break;
                    case TRANSPARENT_LINE:
                        {
                            double* transparency_ptr = (double*)line->data;
                            double transparency = transparency_ptr == NULL ? 0.5 : *transparency_ptr;
                            (*line->texture)(x, h, height, line, &hit, (1 - mist) * (1 - transparency));
                        }
                        break;
                    default:
                        (*line->texture)(x, h, height, line, &hit, 1 - mist);
                        break;
                }
            }
        }
    }
}

double calc_height(double distance, double angle) {
    return .5 / distance / cos(angle);
}
