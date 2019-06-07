/*
 * Copyright © 2019 LambdAurora <aurora42lambda@gmail.com>, Shad Amethyst <shad.amethyst@gmail.com>
 *
 * This file is part of fictional_couscous_isn.
 *
 * Licensed under the MIT license. For more information,
 * see the LICENSE file.
 */

#include "draw.h"

void draw(
        const Game* game,
        const World* world,
        size_t layer,double fov, double length,
        const Color* bg, double mist_length
) {
    int x;
    double last_dist = 0;
    for (x = 0; x < game->width; x++) { // on dessine chaque bande verticale de pixel, l'une après l'autre
        double angle = ((double) x - (double) game->width / 2) / (double) game->width * 2 * fov; // angle du rayon à envoyer

        // on crée le rayon à envoyer
        Line2D ray;
        ray.length = length;
        ray.pos = world->player_position;
        ray.vec.x = cos(angle + world->player_angle);
        ray.vec.y = sin(angle + world->player_angle);

        // on envoie le rayon
        RayIntersection cast = send_ray(world, &ray, layer);
        int last_ground_height = 0;
        Room* current_room; // salle se trouvant derrière le mur précédent

        if (cast.success) { // si on a en effet touché un mur
            size_t n_hit;

            for (n_hit = cast.n_hits - 1; n_hit != -1; n_hit--) { // on affiche chaque intersection, en commencant par la dernière
                Hit hit = cast.hits[n_hit]; // intersection en cours
                Line2D* line = hit.line; // mur de l'intersectoin
                if (hit.dist < DISTANCE_THRESHOLD) { // si le mur est trop près de la caméra

                    if (game->draw_floor) { // on affiche le sol derrière ce mur

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
                                EZ_trace_rectangle_plein(x, game->height / 2 + last_ground_height, 0, game->height - last_ground_height, current_room->color.red, current_room->color.green, current_room->color.blue, 255); // on affiche le sol si nécéssaire
                            }
                        }

                    }

                    last_ground_height = game->height; // on n'affiche pas de sol après (on lui dit de l'affiche en dessous de la fenêtre, en gros)
                    continue; // on skip la suite
                }
                int h = (int) (calc_height(hit.dist, angle, game->height, game->width)); // hauteur du mur
                double mist = 1 - 1 / (1 + hit.dist * hit.dist / mist_length); // intensité du brouillard

                if (game->draw_floor) { // si on doit afficher le sol
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
                    case BOUNCE_LINE: // la ligne est un mirroir
                        if (!game->draw_complex_textures && is_complex_texture(line->texture)) {
                            texture_flat(x, h, game->height, line, &hit, (1 - mist) * 0.25);
                        } else {
                            (*line->texture)(x, h, game->height, line, &hit, (1 - mist) * 0.25);
                        }
                        break;
                    case GHOST_LINE:
                    case TRANSPARENT_LINE: // la ligne est transparente: on récupère sa transparence et on l'affiche
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
                    default: // la ligne est normale ou est un miroir
                        if (!game->draw_complex_textures && is_complex_texture(line->texture)) {
                            texture_flat(x, h, game->height, line, &hit, 1 - mist);
                        } else {
                            (*line->texture)(x, h, game->height, line, &hit, 1 - mist);
                        }
                        break;
                }
                last_ground_height = h;
            }
        }

        if (game->draw_floor) { // on affiche le sol entre le mur le plus proche et le bord inférieur de l'écran
          current_room = find_current_room(world);
          if (current_room != NULL) {
            EZ_trace_rectangle_plein(x, game->height / 2 + last_ground_height, 0, game->height / 2 - last_ground_height, current_room->color.red, current_room->color.green, current_room->color.blue, 255);
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
