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
            int last_ground_height = 0;
#ifdef DRAW_ROOMS
            Room* current_room = find_current_room(world);
#endif // DRAW_ROOMS
            for (n_hit = cast.n_hits - 1; n_hit != -1; n_hit--) {
                Hit hit = cast.hits[n_hit];
                Line2D* line = hit.line;
                if (hit.dist < DISTANCE_THRESHOLD) {
                    #ifdef DRAW_ROOMS
                        if (line->type != NORMAL_LINE) {
                            if (hit.side) {
                                if (line->room_left != NULL) {
                                    current_room = line->room_left;
                                }
                            } else {
                                if (line->room_right != NULL) {
                                    current_room = line->room_right;
                                }
                            }
                            if (current_room != NULL) {
                                EZ_trace_rectangle_plein(x, height / 2 + last_ground_height, 0, height - last_ground_height, current_room->color.red, current_room->color.green, current_room->color.blue, 255);
                            }
                        }
                    #endif // DRAW_ROOMS
                    last_ground_height = height;
                    continue;
                }
                int h = (int) ((double) height * calc_height(hit.dist, angle));
                double mist = 1 - 1 / (1 + hit.dist * hit.dist / mist_length);

                #ifdef DRAW_ROOMS
                    if (line->type != NORMAL_LINE) {
                        if (hit.side) {
                            if (line->room_left != NULL) {
                                current_room = line->room_left;
                            }
                        } else {
                            if (line->room_right != NULL) {
                                current_room = line->room_right;
                            }
                        }
                        if (current_room != NULL) {
                            EZ_trace_rectangle_plein(x, height / 2 + last_ground_height, 0, h - last_ground_height, current_room->color.red, current_room->color.green, current_room->color.blue, 255);
                        }
                    }
                #endif // DRAW_ROOMS

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
                last_ground_height = h;
            }

            #ifdef DRAW_ROOMS
                if (current_room != NULL) {
                    current_room = find_current_room(world);
                    EZ_trace_rectangle_plein(x, height / 2 + last_ground_height, 0, height - last_ground_height, current_room->color.red, current_room->color.green, current_room->color.blue, 255);
                }
            #endif // DRAW_ROOMS
        }
    }
}

double calc_height(double distance, double angle) {
    return .5 / distance / cos(angle);
}
