#include "color.h"

u_int8_t mix(u_int8_t a, u_int8_t b, double ratio) {
  return (u_int8_t)((double)a * (1 - ratio) + (double)b * ratio);
}
