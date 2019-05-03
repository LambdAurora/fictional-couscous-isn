#ifndef FICTIONAL_COUSCOUS_ISN_BASE_H
#define FICTIONAL_COUSCOUS_ISN_BASE_H

#include <inttypes.h>
#include <stdbool.h>

struct Line2D;
struct Hit;

typedef void (*texture_t)(double, double, double, struct Line2D*, struct Hit*, double);

#define lc_maths_abs(number) (number < 0 ? -(number) : number)
#define lc_maths_min(a, b) (a < b ? a : b)
#define lc_maths_max(a, b) (a > b ? a : b)
#define lc_maths_clamp(number, min, max) lc_maths_min(lc_maths_max(number, min), max) //maths::min(maths::max(number, min), max)

#endif //FICTIONAL_COUSCOUS_ISN_BASE_H
