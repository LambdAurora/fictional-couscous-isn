#include "texture.h"

void texture_flat(double x, double h, double height, Line2D* line, Hit* hit, double opacity) {
  double y = height / 2 - h;
  EZ_trace_rectangle_plein((uint32_t)x, (uint32_t)y, 0, (uint32_t)(h * 2), line->color.red, line->color.green, line->color.blue, mix(0, 255, opacity));
}

void texture_checkerboard(double x, double h, double height, Line2D* line, Hit* hit, double opacity) {
  #define N 8
  double y = height / 2 - h;
  double sy = h * 2 / N;
  double texture_x = dist2D(&hit->pos, &line->pos);
  bool j = (uint32_t)(texture_x * N * 2) % 2;
  for (int i = 0; i < N; i++) {
    if (i % 2 != j) {
      EZ_trace_rectangle_plein((uint32_t)x, (uint32_t)y, 0, (uint32_t)sy, line->color.red, line->color.green, line->color.blue, mix(0, 255, opacity));
    } else {
      EZ_trace_rectangle_plein((uint32_t)x, (uint32_t)y, 0, (uint32_t)sy, line->color.red * 0.95, line->color.green * 0.95, line->color.blue * 0.95, mix(0, 255, opacity));
    }
    y += sy;
  }
}

void texture_gradient(double x, double h, double height, Line2D* line, Hit* hit, double opacity) {
  Color* c = (Color*)line->data;
  double texture_x = dist2D(&hit->pos, &line->pos) / line->length;
  double y = height / 2 - h;
  EZ_trace_rectangle_plein((uint32_t)x, (uint32_t)y, 0, (uint32_t)(h * 2),
  mix(line->color.red, c->red, texture_x),
  mix(line->color.green, c->green, texture_x),
  mix(line->color.blue, c->blue, texture_x),
  mix(0, 255, opacity));
}

void texture_image(double x, double h, double height, Line2D* line, Hit* hit, double opacity) {
  TextureImage* img = (TextureImage*)line->data;
  double texture_x = dist2D(&hit->pos, &line->pos);
  if (texture_x < img->width / IMAGE_ADJUST) {
    double y = height / 2 - h + (1 - img->height) * h * 2;

    int imgw;
    int imgh;
    EZ_donne_dimension_image(img->image, &imgw, &imgh);

    int tex_x = (int)(texture_x * imgw / img->width * IMAGE_ADJUST);

    double sy = img->height * h * 2 / imgh;
    for (int i = 0; i < imgh; i++) {
      uint8_t red;
      uint8_t green;
      uint8_t blue;
      uint8_t alpha;
      EZ_recupere_rvb_image_transparence(img->image, tex_x, i, &red, &green, &blue, &alpha);
      EZ_trace_rectangle_plein(x, y, 0, sy, red, green, blue, alpha);
      y += sy;
    }
  }
}
