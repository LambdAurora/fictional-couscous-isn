#ifndef FICTIONAL_COUSCOUS_VEC2D_H
#define FICTIONAL_COUSCOUS_VEC2D_H

#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "double.h"

struct Vec2D {
  double x;
  double y;
};

typedef struct Vec2D Vec2D;
Vec2D Vec2D_new(double x, double y);

double dot2D(Vec2D a, Vec2D b);
Vec2D norm2D(Vec2D in);
double dist2D(Vec2D a, Vec2D b);
double length2D(Vec2D a);

Vec2D Vec2D_sub(Vec2D a, Vec2D b);
Vec2D Vec2D_sum(Vec2D a, Vec2D b);
Vec2D Vec2D_mult(Vec2D a, double by);
bool Vec2D_eq(Vec2D a, Vec2D b);

#endif //FICTIONAL_COUSCOUS_VEC2D_H
