#define STB_IMAGE_IMPLEMENTATION
#include "texture.h"

void texture_flat(double x, double h, double height, Line2D* line, Hit* hit, double opacity) {
  double y = height / 2 - h;
  EZ_trace_rectangle_plein((uint32_t)x, (uint32_t)y, 1, (uint32_t)(h * 2), line->color.red, line->color.green, line->color.blue, mix(0, 255, opacity));
}

void texture_checkerboard(double x, double h, double height, Line2D* line, Hit* hit, double opacity) {
  #define N 8
  double y = height / 2 - h;
  double sy = h * 2 / N;
  double texture_x = dist2D(&hit->pos, &line->pos);
  bool j = (uint32_t)(texture_x * N * 2) % 2;
  for (int i = 0; i < N; i++) {
    if (i % 2 != j) {
      EZ_trace_rectangle_plein((uint32_t)x, (uint32_t)y, 1, (uint32_t)sy, line->color.red, line->color.green, line->color.blue, mix(0, 255, opacity));
    } else {
      EZ_trace_rectangle_plein((uint32_t)x, (uint32_t)y, 1, (uint32_t)sy, line->color.red * 0.95, line->color.green * 0.95, line->color.blue * 0.95, mix(0, 255, opacity));
    }
    y += sy;
  }
}

void texture_gradient(double x, double h, double height, Line2D* line, Hit* hit, double opacity) {
  Color* c = (Color*)line->data;
  double texture_x = dist2D(&hit->pos, &line->pos) / line->length;
  double y = height / 2 - h;
  EZ_trace_rectangle_plein((uint32_t)x, (uint32_t)y, 1, (uint32_t)(h * 2),
  mix(line->color.red, c->red, texture_x),
  mix(line->color.green, c->green, texture_x),
  mix(line->color.blue, c->blue, texture_x),
  mix(0, 255, opacity));
}

void texture_image(double x, double h, double height, Line2D* line, Hit* hit, double opacity) {
    TextureImage* img = (TextureImage*) line->data;
    double texture_x = dist2D(&hit->pos, &line->pos);
    if (texture_x < img->width / IMAGE_ADJUST) {
        double y = height / 2 - h + (1 - img->height) * h * 2;

        int tex_x = (int) (texture_x * img->tex_width / img->width * IMAGE_ADJUST);

        double sy = img->height * h * 2 / img->tex_height;
        for (int i = 0; i < img->tex_height; i++) {
            uint8_t red = img->pixels[(4 * (i * img->tex_width + tex_x))];
            uint8_t green = img->pixels[(4 * (i * img->tex_width + tex_x) + 1)];
            uint8_t blue = img->pixels[(4 * (i * img->tex_width + tex_x) + 2)];
            uint8_t alpha = img->pixels[(4 * (i * img->tex_width + tex_x) + 3)];
            EZ_trace_rectangle_plein(x, y, 1, sy, red, green, blue, alpha);
            y += sy;
        }
    }
}
