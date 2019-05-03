#include "texture.h"

void texture_flat(double x, double h, double height, Line2D* line, Hit* hit, double mist) {
  double y = height / 2 - h;
  EZ_trace_rectangle_plein((uint32_t)x, (uint32_t)y, 1, (uint32_t)(h * 2), line->color.red, line->color.green, line->color.blue, mix(255, 0, mist));
}

void texture_checkerboard(double x, double h, double height, Line2D* line, Hit* hit, double mist) {
  #define N 8
  double y = height / 2 - h;
  double sy = h * 2 / N;
  double texture_x = dist2D(&hit->pos, &line->pos);
  bool j = (uint32_t)(texture_x * N * 2) % 2;
  for (int i = 0; i < N; i++) {
    if (i % 2 != j) {
      EZ_trace_rectangle_plein((uint32_t)x, (uint32_t)y, 1, (uint32_t)sy, line->color.red, line->color.green, line->color.blue, mix(255, 0, mist));
    } else {
      EZ_trace_rectangle_plein((uint32_t)x, (uint32_t)y, 1, (uint32_t)sy, line->color.red * 0.95, line->color.green * 0.95, line->color.blue * 0.95, mix(255, 0, mist));
    }
    y += sy;
  }
}

void texture_gradient(double x, double h, double height, Line2D* line, Hit* hit, double mist) {
  Color* c = (Color*)line->data;
  double texture_x = dist2D(&hit->pos, &line->pos) / line->length;
  double y = height / 2 - h;
  EZ_trace_rectangle_plein((uint32_t)x, (uint32_t)y, 1, (uint32_t)(h * 2),
  mix(line->color.red, c->red, texture_x),
  mix(line->color.green, c->green, texture_x),
  mix(line->color.blue, c->blue, texture_x),
  mix(255, 0, mist));
}
