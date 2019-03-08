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
