/*
 * Copyright © 2019 LambdAurora <aurora42lambda@gmail.com>, Shad Amethyst <shad.amethyst@gmail.com>
 *
 * This file is part of fictional_couscous_isn.
 *
 * Licensed under the MIT license. For more information,
 * see the LICENSE file.
 */

#ifndef FICTIONAL_COUSCOUS_MATH_DOUBLE_H
#define FICTIONAL_COUSCOUS_MATH_DOUBLE_H

#include <math.h>
#include <stdbool.h>

#define EPSILON 1e-8

bool approx_eq(double a, double b);
bool approx_gt(double a, double b);
bool approx_lt(double a, double b);

#endif //FICTIONAL_COUSCOUS_MATH_DOUBLE_H
