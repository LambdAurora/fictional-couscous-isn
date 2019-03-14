#include "color.h"

uint8_t mix(uint8_t a, uint8_t b, double ratio) {
  return (uint8_t)((double)a * (1 - ratio) + (double)b * ratio);
}

Color Color_new(uint8_t red, uint8_t green, uint8_t blue) {
  Color res;
  res.red = red;
  res.green = green;
  res.blue = blue;
  return res;
}
