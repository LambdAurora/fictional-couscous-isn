#include "draw.h"

// TODO: replace `lines` with `world`
void draw(
        const Game* game,
        const World* world,
        size_t layer,double fov, double length,
        const Color* bg, double mist_length
) {
    int x;
    double last_dist = 0;
    for (x = 0; x < game->width; x++) {
        double angle = ((double) x - (double) game->width / 2) / (double) game->width * 2 * fov;

        Line2D ray;
        ray.length = length;
        ray.pos = world->player_position;
        ray.vec.x = cos(angle + world->player_angle);
        ray.vec.y = sin(angle + world->player_angle);

        RayIntersection cast = send_ray(world, &ray, layer);
        if (cast.success) {
            size_t n_hit;
            int last_ground_height = 0;

            Room* current_room = find_current_room(world);

            for (n_hit = cast.n_hits - 1; n_hit != -1; n_hit--) {
                Hit hit = cast.hits[n_hit];
                Line2D* line = hit.line;
                if (hit.dist < DISTANCE_THRESHOLD) {

                    if (game->draw_floor) {

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
                                EZ_trace_rectangle_plein(x, game->height / 2 + last_ground_height, 0, game->height - last_ground_height, current_room->color.red, current_room->color.green, current_room->color.blue, 255);
                            }
                        }

                    }

                    last_ground_height = game->height;
                    continue;
                }
                int h = (int) (calc_height(hit.dist, angle, game->height, game->width));
                double mist = 1 - 1 / (1 + hit.dist * hit.dist / mist_length);

                if (game->draw_floor) {
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
                            EZ_trace_rectangle_plein(x, game->height / 2 + last_ground_height, 0, h - last_ground_height, current_room->color.red, current_room->color.green, current_room->color.blue, 255);
                        }
                    }
                }

                switch (line->type) {
                    case BOUNCE_LINE:
                        if (!game->draw_complex_textures && is_complex_texture(line->texture)) {
                            texture_flat(x, h, game->height, line, &hit, (1 - mist) * 0.25);
                        } else {
                            (*line->texture)(x, h, game->height, line, &hit, (1 - mist) * 0.25);
                        }
                        break;
                    case GHOST_LINE:
                    case TRANSPARENT_LINE:
                        {
                            double* transparency_ptr = (double*)line->data;
                            double transparency = transparency_ptr == NULL ? 0.5 : *transparency_ptr;
                            if (!game->draw_complex_textures && is_complex_texture(line->texture)) {
                                texture_flat(x, h, game->height, line, &hit, (1 - mist) * (1 - transparency));
                            } else {
                                (*line->texture)(x, h, game->height, line, &hit, (1 - mist) * (1 - transparency));
                            }
                        }
                        break;
                    default:
                        if (!game->draw_complex_textures && is_complex_texture(line->texture)) {
                            texture_flat(x, h, game->height, line, &hit, 1 - mist);
                        } else {
                            (*line->texture)(x, h, game->height, line, &hit, 1 - mist);
                        }
                        break;
                }
                last_ground_height = h;
            }

            if (game->draw_floor) {
                current_room = find_current_room(world);
                if (current_room != NULL) {
                    EZ_trace_rectangle_plein(x, game->height / 2 + last_ground_height, 0, game->height - last_ground_height, current_room->color.red, current_room->color.green, current_room->color.blue, 255);
                }
            }

        }
    }
}

double calc_height(double distance, double angle, int height, int width) {
    return HEIGHT_ADJUST / distance / cos(angle) * width;
}

bool is_complex_texture(void* tex) {
    return tex == &texture_checkerboard || tex == &texture_image;
}
