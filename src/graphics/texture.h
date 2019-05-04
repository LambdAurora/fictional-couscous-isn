#ifndef FICTIONAL_COUSCOUS_TEXTURE_H
#define FICTIONAL_COUSCOUS_TEXTURE_H

#include "raytracing.h"
#include "../base.h"
#include "../maths/geometry.h"
#include "../maths/vec2d.h"
#include "color.h"

#define IMAGE_ADJUST 1.8

struct TextureImage {
  struct EZ_Image* image;
  double height;
  double width;
};
typedef struct TextureImage TextureImage;

void texture_flat(double x, double h, double height, Line2D* line, Hit* hit, double opacity);
void texture_checkerboard(double x, double h, double height, Line2D* line, Hit* hit, double opacity);
void texture_gradient(double x, double h, double height, Line2D* line, Hit* hit, double opacity);
void texture_image(double x, double h, double height, Line2D* line, Hit* hit, double opacity);
void texture_ground(double x, double h, double height, Line2D* line, Hit* hit, double opacity);

#endif // FICTIONAL_COUSCOUS_TEXTURE_H
