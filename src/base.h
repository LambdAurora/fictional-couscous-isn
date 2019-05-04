#ifndef FICTIONAL_COUSCOUS_ISN_BASE_H
#define FICTIONAL_COUSCOUS_ISN_BASE_H

// Fichier définissant les bases et les imports de bases.

#include <inttypes.h>
#include <stdbool.h>
#include "easysdl.h"
#include "stb_image.h"

struct Line2D;
struct Hit;

typedef void (*texture_t)(double, double, double, struct Line2D*, struct Hit*, double);

// Quelques fonctions mathématiques utiles.
#define lc_maths_abs(number) (number < 0 ? -(number) : number)
#define lc_maths_min(a, b) (a < b ? a : b)
#define lc_maths_max(a, b) (a > b ? a : b)
#define lc_maths_clamp(number, min, max) lc_maths_min(lc_maths_max(number, min), max) //maths::min(maths::max(number, min), max)

#define CREATE_LINE(name, x1, y1, x2, y2)\
  Vec2D _##name##_start = Vec2D_new(x1, y1);\
  Vec2D _##name##_end = Vec2D_new(x2, y2);\
  Line2D name = Line2D_new(&_##name##_start, &_##name##_end);

#define LINE_TRANSPARENT(name, alpha)\
  uint8_t _##name##_alpha = alpha;\
  name.type = TRANSPARENT_LINE;\
  name.data = &_##name##_alpha;

#define LINE_BOUNCE(name) name.type = BOUNCE_LINE;

#define LINE_COLOR(name, red, green, blue) name.color = Color_new(red, green, blue);

#define LINE_IMAGE(name, img, w, h)\
  name.type = TRANSPARENT_LINE;\
  TextureImage _##name##_image;\
  int __##name##_channels__;\
  _##name##_image.pixels = stbi_load(img, &(_##name##_image.tex_width), &(_##name##_image.tex_height), &__##name##_channels__, 4);\
  _##name##_image.width = w;\
  _##name##_image.height = h;\
  name.data = &_##name##_image;\
  name.texture = &texture_image;

#define LINE_GRADIENT(name, red, green, blue)\
  Color _##name##_gradient_color = Color_new(red, green, blue);\
  name.texture = &texture_gradient;\
  name.data = &_##name##_gradient_color;

#define LINE_CHECKERBOARD(name) name.texture = &texture_checkerboard;

#define LINE_TELEPORT(name, target)\
  TeleportTarget _##name##_target = TeleportTarget_new(&target, 0);\
  name.data = &_##name##_target;\
  name.type = TELEPORT_LINE;

#endif //FICTIONAL_COUSCOUS_ISN_BASE_H
