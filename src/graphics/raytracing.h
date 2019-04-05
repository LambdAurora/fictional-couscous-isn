#ifndef FICTIONAL_COUSCOUS_RAYTRACING_H
#define FICTIONAL_COUSCOUS_RAYTRACING_H

#include "../base.h"
#include "easysdl.h"
#include "../maths/geometry.h"
#include "../maths/vec2d.h"
#include "../maths/double.h"
#include "../physics/raytrace.h"
#include "color.h"
#include <stdlib.h>

void sweep(
        int width, int height,
        const World* world,
        size_t layer, double fov, double length,
        const Color* bg, double mist_length
);

double calc_height(double distance, double angle);

#define DRAW_OUTLINE

#endif //FICTIONAL_COUSCOUS_RAYTRACING_H
