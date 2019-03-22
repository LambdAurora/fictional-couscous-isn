#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include "easysdl.h"
#include "graphics/color.h"
#include "graphics/raytracing.h"
#include "physics/raytrace.h"
#include "physics/physics.h"
#include "maths/vec2d.h"
#include "maths/geometry.h"
#include "world/world.h"

#define ARROW 0x40000000

int main(int argc, char** argv) {
    const int height = 480;
    const int width = 1080;
    EZ_creation_fenetre(" ", width, height);

    Vec2D vec0 = Vec2D_new(.0, .0);
    Vec2D vec1 = Vec2D_new(1., .0);
    Vec2D vec2 = Vec2D_new(.0, 1.);
    Vec2D vec3 = Vec2D_new(-.5, 1.);
    Line2D a = Line2D_new(&vec0, &vec1);
    Line2D b = Line2D_new(&vec0, &vec2);
    Line2D c = Line2D_new(&vec2, &vec3);

    Vec2D d_start = Vec2D_new(-2, -0.5);
    Vec2D d_end = Vec2D_new(-2, 0.5);
    Line2D d = Line2D_new(&d_start, &d_end);

    Vec2D e_start = d_start;
    Vec2D e_end = Vec2D_new(-1, -0.5);
    Line2D e = Line2D_new(&e_start, &e_end);

    double D = 32;

    Vec2D f_start = Vec2D_new(2, D);
    Vec2D f_end = Vec2D_new(2, -D);
    Line2D f = Line2D_new(&f_start, &f_end);

    Vec2D g_start = Vec2D_new(-2.5, D);
    Vec2D g_end = Vec2D_new(-2.5, -D);
    Line2D g = Line2D_new(&g_start, &g_end);
    f.data = &g;
    g.data = &f;

    Vec2D h_start = Vec2D_new(D, 2);
    Vec2D h_end = Vec2D_new(-D, 2);
    Line2D h = Line2D_new(&h_start, &h_end);

    Vec2D i_start = Vec2D_new(D, -2.5);
    Vec2D i_end = Vec2D_new(-D, -2.5);
    Line2D i = Line2D_new(&i_start, &i_end);
    h.data = &i;
    i.data = &h;

    Color bg = Color_new(209, 213, 201);

    a.color = Color_new(83, 190, 187);
    b.color = Color_new(113, 190, 118);
    c.color = Color_new(228, 214, 84);
    d.color = Color_new(122, 58, 144);
    e.color = Color_new(217, 90, 75);
    f.color = Color_new(180, 191, 122);

    uint8_t alpha = 128;
    d.type = TRANSPARENT_LINE;
    d.data = &alpha;
    e.type = TRANSPARENT_LINE;
    e.data = &alpha;
    f.type = NORMAL_LINE;
    g.type = TELEPORT_LINE;
    h.type = TELEPORT_LINE;
    i.type = TELEPORT_LINE;

    Lines lines;
    lines.length = 9;
    lines.lines = (Line2D*) malloc(sizeof(Line2D) * lines.length);
    // copy the values in the allocated memory
    lines.lines[0] = a;
    lines.lines[1] = b;
    lines.lines[2] = c;
    lines.lines[3] = d;
    lines.lines[4] = e;
    lines.lines[5] = f;
    lines.lines[6] = g;
    lines.lines[7] = h;
    lines.lines[8] = i;

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
        EZ_trace_rectangle_plein(0, 0, width, height, bg.red, bg.green, bg.blue, 255);

        sweep(width, height, &world, 0, 0.6, 100, &bg, 1000);

        // FPS-meter
        char str[50];
        sprintf(str, "%d", (int) (1 / dt));
        EZ_trace_texte(str, "../resources/DF-font.ttf", 16, 0, 0, 0, 0, 0, 255);

        sprintf(str, "%d", collide(&world.player_position, &f));
        EZ_trace_texte(str, "../resources/DF-font.ttf", 16, 0, 20, 0, 0, 0, 255);

        EZ_mise_a_jour();

        int evt;
        while (evt = EZ_recupere_evenement_continu()) {
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
        if (rright) world.player_angle += .8 * dt;
        if (rleft) world.player_angle -= .8 * dt;

        Lines walls = world.layers[0].walls;
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
                world.player_position = world.spawn_position;
                break;
            }
        }
        if (!dont_move)
            world.player_position = new_player_position;
    }

    return 0;
}
