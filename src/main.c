#include "base.h"
#include "game.h"
#include "levels.h"
#include "graphics/color.h"
#include "graphics/room.h"
#include "graphics/draw.h"
#include "graphics/texture.h"
#include "physics/raytrace.h"
#include "physics/physics.h"
#include "maths/vec2d.h"
#include "maths/line.h"
#include "world/world.h"
#include <math.h>
#include <time.h>
#include <SDL2/SDL.h>

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
        else if (strncmp(argv[i], "--no-floor", 10) == 0)
            game->draw_floor = false;
    }
}

int main(int argc, char** argv) {
    Game game;
    init_game(&game, GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT);
    parse_command_line(&game, argc, argv);
    EZ_creation_fenetre(" ", game.width, game.height);

    World world;
    World_init(&world, Vec2D_new(1.5, 1.5));

    //LEVEL_2
    CREATE_ROOM(r1, 0, 0, 3, 3)
    ROOM_COLOR(r1, 255, 0, 0)

    CREATE_ROOM(r2, 0, 3, 3, 3)
    ROOM_COLOR(r2, 0, 255, 0)

    CREATE_ROOM(r3, 3, 0, 3, 3)
    ROOM_COLOR(r3, 0, 0, 255)


    Lines lines;
    size_t line_index = 0;
    lines.length = 18;
    lines.lines = (Line2D*) malloc(sizeof(Line2D) * lines.length);

    CREATE_LINE(r1w1, 0, 0, 3, 0)
    LINE_COLOR(r1w1, 176, 172, 184)
    LINE_CHECKERBOARD(r1w1)
    REG_LINE(r1w1)

    CREATE_LINE(r1w2, 0, 0, 0, 3)
    LINE_COLOR(r1w2, 176, 172, 184)
    LINE_CHECKERBOARD(r1w2)
    REG_LINE(r1w2)

    CREATE_LINE(w3, 3, 0, 3, 0.25)
    LINE_COLOR(w3, 176, 172, 184)
    REG_LINE(w3)

    CREATE_LINE(w4, 3, 3, 3, 2.75)
    LINE_COLOR(w4, 176, 172, 184)
    REG_LINE(w4)

    CREATE_LINE(w5, 0, 3, 0.25, 3)
    LINE_COLOR(w5, 176, 172, 184)
    REG_LINE(w5)

    CREATE_LINE(w6, 3, 3, 2.75, 3)
    LINE_COLOR(w6, 176, 172, 184)
    REG_LINE(w6)

    CREATE_LINE(r2w1, 0, 3, 0, 6)
    LINE_COLOR(r2w1, 176, 172, 184)
    LINE_CHECKERBOARD(r2w1)
    REG_LINE(r2w1)

    CREATE_LINE(r2w2, 0, 6, 3, 6)
    LINE_COLOR(r2w2, 176, 172, 184)
    LINE_CHECKERBOARD(r2w2)
    REG_LINE(r2w2)

    CREATE_LINE(r3w1, 3, 0, 6, 0)
    LINE_COLOR(r3w1, 176, 172, 184)
    LINE_CHECKERBOARD(r3w1)
    REG_LINE(r3w1)

    CREATE_LINE(r3w2, 6, 0, 6, 3)
    LINE_COLOR(r3w2, 176, 172, 184)
    LINE_CHECKERBOARD(r3w2)
    REG_LINE(r3w2)

    CREATE_LINE(w7, 3, 3, 3.25, 3)
    LINE_COLOR(w7, 176, 172, 184)
    LINE_CHECKERBOARD(w7)
    REG_LINE(w7)

    CREATE_LINE(w8, 6, 3, 5.75, 3)
    LINE_COLOR(w8, 176, 172, 184)
    LINE_CHECKERBOARD(w8)
    REG_LINE(w8)

    CREATE_LINE(w9, 3, 3, 3, 3.25)
    LINE_COLOR(w9, 176, 172, 184)
    LINE_CHECKERBOARD(w9)
    REG_LINE(w9)

    CREATE_LINE(w10, 3, 6, 3, 5.75)
    LINE_COLOR(w10, 176, 172, 184)
    LINE_CHECKERBOARD(w10)
    REG_LINE(w10)

    // CREATE_LINE(m1, 0, 1, 0, 2)
    // LINE_COLOR(m1, 173, 208, 230)
    // LINE_BOUNCE(m1)
    // ROOMS_AROUND(m1, r1, r1)
    // REG_LINE(m1)
    //
    // CREATE_LINE(m2, -5, 3, -5, 2)
    // LINE_COLOR(m2, 173, 208, 230)
    // LINE_BOUNCE(m2)
    // ROOMS_AROUND(m2, r2, r2)
    // REG_LINE(m2)

    CREATE_LINE(t1, 3, 3.25, 3, 5.75)
    CREATE_LINE(t2, 3.25, 3, 5.75, 3)
    LINE_TELEPORT(t1, t2)
    LINE_TELEPORT(t2, t1)
    ROOMS_AROUND(t1, r2, r1)
    ROOMS_AROUND(t2, r2, r1)
    REG_LINE(t1)
    REG_LINE(t2)

    CREATE_LINE(f1, .25, .25, .5, .25)
    LINE_IMAGE(f1, "../resources/flower.png", 0.5, 0.5)
    ROOMS_AROUND(f1, r2, r2)
    REG_LINE(f1)

    CREATE_LINE(g1, -5, 2, 0, 2)
    LINE_GHOST(g1)
    ROOMS_AROUND(g1, r2, r1)
    REG_LINE(g1)

    Color bg = Color_new(107, 110, 101);

    world.n_rooms = 2;
    world.rooms = (Room**)malloc(sizeof(Room*) * world.n_rooms);
    world.rooms[0] = &r1;
    world.rooms[1] = &r2;

    if (game.top_mode) world.player_angle = -M_PI / 2;
    world.layers = (Layer*) malloc(sizeof(Layer) * 1);
    world.n_layers = 1;
    world.layers[0].walls = lines;

    bool exit = false;

    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;
    bool rotate_left = false;
    bool rotate_right = false;

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
            draw(&game, &world, 0, 0.6, 100, &bg, 10000);

        // FPS-meter
        char str[50];
        sprintf(str, "%d", (int) (1 / dt));
        EZ_trace_texte(str, "../resources/DF-font.ttf", 16, 0, 0, 0, 0, 0, 255);

        sprintf(str, "X: %.4lf Y: %.4lf", world.player_position.x, world.player_position.y);
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
                        rotate_left = state;
                        break;
                    case ARROW | 0x4f:
                        rotate_right = state;
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
        if (rotate_right) world.player_angle += .8 * dt;
        if (rotate_left) world.player_angle -= .8 * dt;

        World_move(&world, &new_player_position);
    }

    return 0;
}
