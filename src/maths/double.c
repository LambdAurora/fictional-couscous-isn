/*
 * Copyright © 2019 LambdAurora <aurora42lambda@gmail.com>, Shad Amethyst <shad.amethyst@gmail.com>
 *
 * This file is part of fictional_couscous_isn.
 *
 * Licensed under the MIT license. For more information,
 * see the LICENSE file.
 */

#include "double.h"

bool approx_eq(double a, double b) {
  double c = a - b;
  if (c < 0) c = -c;
  return c < EPSILON && c > -EPSILON;
}

bool approx_gt(double a, double b) {
  return (a - b) > -EPSILON;
}

bool approx_lt(double a, double b) {
  return (a - b) < EPSILON;
}
