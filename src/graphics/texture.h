#ifndef FICTIONAL_COUSCOUS_TEXTURE_H
#define FICTIONAL_COUSCOUS_TEXTURE_H

#include "draw.h"
#include "../base.h"
#include "../maths/line.h"
#include "../maths/vec2d.h"
#include "color.h"

#define IMAGE_ADJUST 1.8

struct TextureImage {
  uint8_t* pixels;
  double height;
  double width;
  int tex_width;
  int tex_height;
};
typedef struct TextureImage TextureImage;

#define DEF_TEXTURE(name) void name(double x, double h, double height, Line2D* line, Hit* hit, double opacity)

DEF_TEXTURE(texture_flat);
DEF_TEXTURE(texture_checkerboard);
DEF_TEXTURE(texture_gradient);
DEF_TEXTURE(texture_image);
DEF_TEXTURE(texture_empty);

#endif // FICTIONAL_COUSCOUS_TEXTURE_H
