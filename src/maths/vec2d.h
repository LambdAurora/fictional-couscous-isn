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

double dot2D(const Vec2D* a, const Vec2D* b);

Vec2D norm2D(const Vec2D* in);

double dist2D(const Vec2D* a, const Vec2D* b);

double length2D(const Vec2D* a);

Vec2D Vec2D_sub(const Vec2D* a, const Vec2D* b);

Vec2D Vec2D_sum(const Vec2D* a, const Vec2D* b);

Vec2D Vec2D_mult(const Vec2D* a, double by);

bool Vec2D_eq(const Vec2D* a, const Vec2D* b);

#endif //FICTIONAL_COUSCOUS_VEC2D_H
