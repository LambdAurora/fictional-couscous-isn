#ifndef FICTIONAL_COUSCOUS_VEC2D_H
#define FICTIONAL_COUSCOUS_VEC2D_H

#include <stdio.h>
#include <math.h>
#include "double.h"

struct Vec2D {
  double x;
  double y;
};

typedef struct Vec2D Vec2D;

double dot2D(Vec2D a, Vec2D b);

#endif //FICTIONAL_COUSCOUS_VEC2D_H
