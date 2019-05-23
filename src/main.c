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
    extern SDL_Window* EZ_fenetre;
    Game game;
    init_game(&game, GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT);
    parse_command_line(&game, argc, argv);
    EZ_creation_fenetre("Non-euclidian 3D rendering engine", game.width, game.height);

    free_mouse(&game);

    World world;
    World_init(&world, Vec2D_new(1.5, 1.5));

    LEVEL_4

    if (game.top_mode) world.player_angle = -M_PI / 2;
    world.layers = (Layer*) malloc(sizeof(Layer) * 1);
    world.n_layers = 1;
    world.layers[0].walls = lines;

    bool exit = false;

    bool key_shift = false;

    bool key_w = false;
    bool key_s = false;
    bool key_a = false;
    bool key_d = false;
    bool key_q = false;
    bool key_z = false;
    bool key_left = false;
    bool key_right = false;

    bool key_h = false;


    bool drag = false;
    int drag_x = 0;

    clock_t last_clock = clock();

    while (!exit) {
        double dt = (double) (clock() - last_clock) / CLOCKS_PER_SEC;
        last_clock = clock();

        SDL_GetWindowSize(EZ_fenetre, &game.width, &game.height);

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

        if (key_h) {
            EZ_trace_texte("1: capture mouse", "../resources/DF-font.ttf", 16, 0, 20, 0, 0, 0, 255);
            EZ_trace_texte("2: toggle ground", "../resources/DF-font.ttf", 16, 0, 40, 0, 0, 0, 255);
            EZ_trace_texte("3: toggle top view", "../resources/DF-font.ttf", 16, 0, 60, 0, 0, 0, 255);
            EZ_trace_texte("4: toggle complex textures", "../resources/DF-font.ttf", 16, 0, 80, 0, 0, 0, 255);
        } else {
            sprintf(str, "X: %.4lf Y: %.4lf", world.player_position.x, world.player_position.y);
            EZ_trace_texte(str, "../resources/DF-font.ttf", 16, 0, 20, 0, 0, 0, 255);
        }

        EZ_mise_a_jour();

        int evt;
        while ((evt = EZ_recupere_evenement_continu())) {
            if (evt == EZ_EXIT) exit = true;
            if (evt == EZ_TOUCHE_ENFONCEE || evt == EZ_TOUCHE_RELACHEE) {
                bool state = evt == EZ_TOUCHE_ENFONCEE;
                switch (EZ_touche()) {
                    case ARROW | 0x52:
                    case 'w':
                        key_w = state;
                        break;
                    case 'z':
                        key_z = state;
                        break;
                    case ARROW | 0x50:
                        key_left = state;
                        break;
                    case ARROW | 0x4f:
                        key_right = state;
                        break;
                    case ARROW | 0x51:
                    case 's':
                        key_s = state;
                        break;
                    case 'd':
                        key_d = state;
                        break;
                    case 'a':
                        key_a = state;
                        break;
                    case 'q':
                        key_q = state;
                        break;
                    case 'h':
                        key_h = state;
                        break;
                    case 'r':
                        world.player_position = world.spawn_position;
                        break;
                    case 'o':
                        game.zoom++;
                        break;
                    case 'l':
                        game.zoom = lc_maths_max(game.zoom - 1., 1);
                        break;
                    case 0x1B:
                        exit = true;
                        break;
                    case 0x400000e1:
                        key_shift = state;
                        break;
                    case 0x40000044:
                        if (state) {
                            if (game.mouse_captured) {
                                SDL_SetWindowFullscreen(EZ_fenetre, 0);
                                free_mouse(&game);
                            } else {
                                SDL_SetWindowFullscreen(EZ_fenetre, SDL_WINDOW_FULLSCREEN_DESKTOP);
                                capture_mouse(&game);
                            }
                        }
                        break;
                    case 0x31:
                        if (state) {
                            if (game.mouse_captured) {
                                free_mouse(&game);
                            } else {
                                capture_mouse(&game);
                            }
                        }
                        break;
                    case 0x32:
                        if (state) game.draw_floor = !game.draw_floor;
                        break;
                    case 0x33:
                        if (state) game.top_mode = !game.top_mode;
                        break;
                    case 0x34:
                        if (state) game.draw_complex_textures = !game.draw_complex_textures;
                        break;
                    default:
                        printf("%x\n", EZ_touche());
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
            if (evt == EZ_SOURIS_MOUVEMENT && game.mouse_captured) {
                int x = EZ_souris_x() - GAME_WINDOW_WIDTH / 2;
                world.player_angle += ((double) x / 128) * .25;
            }
        }
        if (game.mouse_captured) {
            SDL_WarpMouseInWindow(EZ_fenetre, GAME_WINDOW_WIDTH / 2, GAME_WINDOW_HEIGHT / 2);
        }

        // Créé la nouvelle position du joueur en fonction des entrées.
        Vec2D new_player_position = world.player_position;

        double speed = key_shift ? 1.8 : 1;

        if (key_w || key_z) {
            new_player_position.x += speed * 1.4 * cos(world.player_angle) * dt;
            new_player_position.y += speed * 1.4 * sin(world.player_angle) * dt;
        }
        if (key_s) {
            new_player_position.x -= speed * 1.4 * cos(world.player_angle) * dt;
            new_player_position.y -= speed * 1.4 * sin(world.player_angle) * dt;
        }
        if (key_d) {
            new_player_position.x -= speed * 1 * sin(world.player_angle) * dt;
            new_player_position.y += speed * 1 * cos(world.player_angle) * dt;
        }
        if (key_a || key_q) {
            new_player_position.x += speed * 1 * sin(world.player_angle) * dt;
            new_player_position.y -= speed * 1 * cos(world.player_angle) * dt;
        }

        // Change l'angle de vision.
        if (key_right) world.player_angle += .8 * dt;
        if (key_left) world.player_angle -= .8 * dt;

        World_move(&world, &new_player_position);
    }

    return 0;
}
