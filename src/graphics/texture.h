#ifndef FICTIONAL_COUSCOUS_TEXTURE_H
#define FICTIONAL_COUSCOUS_TEXTURE_H

#include "raytracing.h"
#include "../maths/geometry.h"
#include "../maths/vec2d.h"
#include "color.h"

void texture_flat(double x, double h, double height, Line2D* line, Hit* hit, double mist);
void texture_checkerboard(double x, double h, double height, Line2D* line, Hit* hit, double mist);
void texture_gradient(double x, double h, double height, Line2D* line, Hit* hit, double mist);

#endif // FICTIONAL_COUSCOUS_TEXTURE_H
