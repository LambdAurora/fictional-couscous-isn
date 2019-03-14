#ifndef FICTIONAL_COUSCOUS_COLOR_H
#define FICTIONAL_COUSCOUS_COLOR_H

#include <stdlib.h>
#include <inttypes.h>

struct Color {
  uint8_t red;
  uint8_t green;
  uint8_t blue;
};

typedef struct Color Color;

u_int8_t mix(u_int8_t a, u_int8_t b, double ratio);
Color Color_new(uint8_t red, uint8_t green, uint8_t blue);

#endif// FICTIONAL_COUSCOUS_COLOR_H
