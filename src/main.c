#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "easysdl.h"
#include "graphics/color.h"
#include "graphics/raytracing.h"
#include "physics/raytrace.h"
#include "maths/vec2d.h"
#include "maths/geometry.h"
#include "world/world.h"

#define ARROW 0x40000000

int main() {
    const int height = 480;
    const int width = 1080;
    EZ_creation_fenetre(" ", width, height);

    Vec2D vec0 = Vec2D_new(.0, .0);
    Vec2D vec1 = Vec2D_new(1., .0);
    Vec2D vec2 = Vec2D_new(.0, 1.);
    Vec2D vec3 = Vec2D_new(-.5, 1.);
    Line2D a = Line2D_new(&vec0, &vec1);
    Line2D b = Line2D_new(&vec0, &vec2);
    Line2D c = Line2D_new(&vec1, &vec3);
    Color bg = Color_new(209, 213, 201);

    a.color = Color_new(83, 190, 187);
    b.color = Color_new(113, 190, 118);
    c.color = Color_new(228, 214, 84);

    Lines lines;
    lines.lines = (Line2D*) malloc(sizeof(Line2D) * 3);
    lines.length = 3;
    // copy the values in the allocated memory
    lines.lines[0] = a;
    lines.lines[1] = b;
    lines.lines[2] = c;

    Level level;
    level.spawn_position = Vec2D_new(-1., .5);
    level.walls = lines;
    World world;
    world.level = level;
    world.player_position.x = -1;
    world.player_position.y = 0.5;

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

        sweep(width, height, &(world.level.walls), &(world.player_position), world.player_angle, 0.6, 100, &bg, 5);
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
        if (up) {
            world.player_position.x += 1.4 * cos(world.player_angle) * dt;
            world.player_position.y += 1.4 * sin(world.player_angle) * dt;
        }
        if (down) {
            world.player_position.x -= 1.4 * cos(world.player_angle) * dt;
            world.player_position.y -= 1.4 * sin(world.player_angle) * dt;
        }
        if (right) {
            world.player_position.x -= 1 * sin(world.player_angle) * dt;
            world.player_position.y += 1 * cos(world.player_angle) * dt;
        }
        if (left) {
            world.player_position.x += 1 * sin(world.player_angle) * dt;
            world.player_position.y -= 1 * cos(world.player_angle) * dt;
        }
        if (rright) world.player_angle += .8 * dt;
        if (rleft) world.player_angle -= .8 * dt;
    }

    return 0;
}
