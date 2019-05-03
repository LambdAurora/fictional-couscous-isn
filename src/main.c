#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include "base.h"
#include "game.h"
#include "levels.h"
#include "graphics/color.h"
#include "graphics/raytracing.h"
#include "graphics/texture.h"
#include "physics/raytrace.h"
#include "physics/physics.h"
#include "maths/vec2d.h"
#include "maths/geometry.h"
#include "world/world.h"

#ifndef GAME_WINDOW_HEIGHT
#  define GAME_WINDOW_HEIGHT 480
#endif
#ifndef GAME_WINDOW_WIDTH
#  define GAME_WINDOW_WIDTH 1080
#endif

#define ARROW 0x40000000

/*!
 * Traite les options passées en arguments au programme.
 * @param game L'instance du jeu.
 * @param argc Le nombre d'arguments.
 * @param argv Les arguments.
 */
void parse_command_line(Game *game, int argc, char** argv) {
    size_t i;
    for (i = 1; i < argc; i++) {
        if (strncmp(argv[i], "--top-mode", 11) == 0)
            game->top_mode = true;
    }
}

int main(int argc, char** argv) {
    Game game;
    init_game(&game, GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT);
    parse_command_line(&game, argc, argv);
    EZ_creation_fenetre(" ", game.width, game.height);

    LEVEL_2

    World world;
    World_init(&world, Vec2D_new(-1., .5));
    world.layers = (Layer*) malloc(sizeof(Layer) * 1);
    world.n_layers = 1;
    world.layers[0].walls = lines;

    bool exit = false;

    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;
    bool rleft = false;
    bool rright = false;

    bool drag = false;
    int drag_x = 0;

    clock_t last_clock = clock();

    while (!exit) {
        double dt = (double) (clock() - last_clock) / CLOCKS_PER_SEC;
        last_clock = clock();
        // On efface tout.
        EZ_trace_rectangle_plein(0, 0, game.width, game.height, bg.red, bg.green, bg.blue, 255);

        // On fait le rendu en fonction du mode choisi.
        if (game.top_mode)
            render_top_mode(&game, &world);
        else
            sweep(game.width, game.height, &world, 0, 0.6, 100, &bg, 10000);

        // FPS-meter
        char str[50];
        sprintf(str, "%d", (int) (1 / dt));
        EZ_trace_texte(str, "../resources/DF-font.ttf", 16, 0, 0, 0, 0, 0, 255);

        sprintf(str, "X: %lf Y: %lf", world.player_position.x, world.player_position.y);
        EZ_trace_texte(str, "../resources/DF-font.ttf", 16, 0, 20, 0, 0, 0, 255);

        EZ_mise_a_jour();

        int evt;
        while ((evt = EZ_recupere_evenement_continu())) {
            if (evt == EZ_EXIT) exit = true;
            if (evt == EZ_TOUCHE_ENFONCEE || evt == EZ_TOUCHE_RELACHEE) {
                bool state = evt == EZ_TOUCHE_ENFONCEE;
                switch (EZ_touche()) {
                    case ARROW | 0x52:
                    case 'w':
                        up = state;
                        break;
                    case ARROW | 0x50:
                        rleft = state;
                        break;
                    case ARROW | 0x4f:
                        rright = state;
                        break;
                    case ARROW | 0x51:
                    case 's':
                        down = state;
                        break;
                    case 'd':
                        right = state;
                        break;
                    case 'a':
                        left = state;
                        break;
                    case 'r':
                        world.player_position = world.spawn_position;
                        break;
                    case 'o':
                        game.zoom++;
                        break;
                    case 'l':
                        game.zoom = lc_maths_max(game.zoom - 1., 1);
                    case 0x1B:
                        exit = true;
                        break;
                    default:
                        break;
                }
            }
            if (evt == EZ_SOURIS_BOUTON_GAUCHE_ENFONCE) {
                drag_x = EZ_souris_x();
                drag = true;
            } else if (evt == EZ_SOURIS_BOUTON_GAUCHE_RELACHE) {
                drag = false;
                world.player_angle -= ((double) (EZ_souris_x() - drag_x) / 128) * .5;
            }
        }
        // Créé la nouvelle position du joueur en fonction des entrées.
        Vec2D new_player_position = world.player_position;
        if (up) {
            new_player_position.x += 1.4 * cos(world.player_angle) * dt;
            new_player_position.y += 1.4 * sin(world.player_angle) * dt;
        }
        if (down) {
            new_player_position.x -= 1.4 * cos(world.player_angle) * dt;
            new_player_position.y -= 1.4 * sin(world.player_angle) * dt;
        }
        if (right) {
            new_player_position.x -= 1 * sin(world.player_angle) * dt;
            new_player_position.y += 1 * cos(world.player_angle) * dt;
        }
        if (left) {
            new_player_position.x += 1 * sin(world.player_angle) * dt;
            new_player_position.y -= 1 * cos(world.player_angle) * dt;
        }
        // Change l'angle de vision.
        if (rright) world.player_angle += .8 * dt;
        if (rleft) world.player_angle -= .8 * dt;

        World_move(&world, &new_player_position);

        /*Lines walls = world.layers[0].walls;
        size_t i;
        bool dont_move = false;
        for (i = 0; i < walls.length; i++) {
            Line2D* wall = &(walls.lines[i]);
            bool blocked = !can_move(&world.player_position, &new_player_position, wall);
            if (blocked && wall->type != TELEPORT_LINE) {
                dont_move = true;
                break;
            } else if (blocked && wall->type == TELEPORT_LINE) {
                dont_move = true;
                TeleportTarget* target = (TeleportTarget*) wall->data;
                Vec2D last_pos = world.player_position;
                double x_diff = last_pos.x - new_player_position.x;
                double y_diff = last_pos.y - new_player_position.y;
                double x_offset = 0;
                double y_offset = 0;
                if (lc_maths_abs(x_diff) > lc_maths_abs(y_diff)) {
                    if (last_pos.x - new_player_position.x > 0) x_offset = -.1495;
                    else x_offset = .1495;
                } else {
                    if (last_pos.y - new_player_position.y > 0) y_offset = -.1495;
                    else y_offset = .1495;
                }
                Vec2D new_pos;
                new_pos.x = last_pos.x - wall->pos.x + target->line->pos.x + x_offset;//(target->line->pos.x + target->line->vec.x * target->line->length) / 2.;
                new_pos.y = last_pos.y - wall->pos.y + target->line->pos.y + y_offset;//(target->line->pos.y + target->line->vec.y * target->line->length) / 2.;
                world.player_position = new_pos;
                break;
            }
        }
        if (!dont_move)
            world.player_position = new_player_position;*/
    }

    return 0;
}
