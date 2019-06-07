/*
 * Copyright © 2019 LambdAurora <aurora42lambda@gmail.com>, Shad Amethyst <shad.amethyst@gmail.com>
 *
 * This file is part of fictional_couscous_isn.
 *
 * Licensed under the MIT license. For more information,
 * see the LICENSE file.
 */

#ifndef FICTIONAL_COUSCOUS_ISN_GAME_H
#define FICTIONAL_COUSCOUS_ISN_GAME_H

#include "world/world.h"

/*!
 * Structure du jeu.
 */
struct Game
{
    // Taille de la fenêtre.
    int width;
    int height;
    // Options de rendu.
    bool top_mode;
    bool draw_floor;
    int zoom;
    bool mouse_captured;
    bool draw_complex_textures;
};
typedef struct Game Game;

/*!
 * Initialise le jeu.
 *
 * @param game Instance du jeu.
 * @param width Longueur de la fenêtre.
 * @param height Hauteur de la fenêtre.
 */
void init_game(Game* game, int width, int height);

/*!
 * Fait le rendu en vue de haut.
 *
 * @param game Instance du jeu.
 * @param world Monde.
 */
void render_top_mode(Game* g, World* world);

/*!
 * Capture la souris.
 *
 * @param game Instance du jeu.
 */
void capture_mouse(Game* game);

/*!
 * Libère la souris.
 *
 * @param game Instance du jeu.
 */
void free_mouse(Game* game);

#endif //FICTIONAL_COUSCOUS_ISN_GAME_H
