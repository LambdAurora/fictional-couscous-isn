/*
 * Copyright © 2019 LambdAurora <aurora42lambda@gmail.com>, Shad Amethyst <shad.amethyst@gmail.com>
 *
 * This file is part of fictional_couscous_isn.
 *
 * Licensed under the MIT license. For more information,
 * see the LICENSE file.
 */

#ifndef FICTIONAL_COUSCOUS_TEXTURE_H
#define FICTIONAL_COUSCOUS_TEXTURE_H

#include "draw.h"
#include "../base.h"
#include "../maths/line.h"
#include "../maths/vec2d.h"
#include "color.h"

#define IMAGE_ADJUST 2

/*!
 * Représente une texture à partir d'une image.
 */
struct TextureImage {
  // Pixels de la texture.
  uint8_t* pixels;
  // Taille de l'image.
  double height;
  double width;
  // Taille de la texture.
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
