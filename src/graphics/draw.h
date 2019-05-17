#ifndef FICTIONAL_COUSCOUS_RAYTRACING_H
#define FICTIONAL_COUSCOUS_RAYTRACING_H

#include "../game.h"
#include "easysdl.h"
#include "../maths/line.h"
#include "../maths/vec2d.h"
#include "../maths/double.h"
#include "../physics/raytrace.h"
#include "color.h"
#include "texture.h"
#include "room.h"
#include <stdlib.h>

#define DISTANCE_THRESHOLD 0.01 // trust me, that'll make things better!

#define HEIGHT_ADJUST 0.21

void draw(
        const Game* game,
        const World* world,
        size_t layer, double fov, double length,
        const Color* bg, double mist_length
);

double calc_height(double distance, double angle, int height, int width);

#endif //FICTIONAL_COUSCOUS_RAYTRACING_H
