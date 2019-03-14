#include "raytracing.h"

// TODO: replace `lines` with `world`
void sweep(
  int width, int height,
  Lines lines,
  const Vec2D camera_pos,
  double rotation, double fov, double length,
  const Color bg
) {
  int x;
  int last_h = 0;
  int last_index = -1;
  double last_dist = 0;
  for (x = 0; x < width; x++) {
    double angle = rotation + ((double)x - (double)width / 2) / (double) width * 2 * fov;
    Line2D ray;
    double dist = 0;
    ray.length = length;
    ray.pos = camera_pos;
    ray.vec.x = cos(angle);
    ray.vec.y = sin(angle);
    int n = 0;
    RayIntersection r = cast_ray(lines, ray);
    if (r.pos.success) {
      dist += dist2D(ray.pos, r.pos.pos);
      Line2D line = lines.lines[r.index];
      int h = (int)((double)height / 2 / dist);
      double mist = 1 - 1 / (1 + dist * dist / sqrt(length));
      uint8_t red = mix(line.color.red, bg.red, mist);
      uint8_t green = mix(line.color.green, bg.green, mist);
      uint8_t blue = mix(line.color.blue, bg.blue, mist);
      int h2 = (int)((double)height / sqrt(dist*dist + 4));
      int mh = h < last_h ? h : last_h;
      int dh = h < last_h ? last_h - h : h - last_h;
      switch (line.type) {
        case NORMAL_LINE:
          EZ_trace_rectangle_plein(x, height / 2 - h, 0, h * 2, red, green, blue, 255);
          #ifdef DRAW_REFLECTION
          EZ_trace_rectangle_plein(
            x, height / 2 + h, 0, h2,
            mix(red, bg.red, REFLECTION_AMOUNT),
            mix(green, bg.green, REFLECTION_AMOUNT),
            mix(blue, bg.blue, REFLECTION_AMOUNT),
            255);
          #endif// DRAW_REFLECTION
          #ifdef DRAW_OUTLINE
          EZ_trace_rectangle_plein(x - 1, height / 2 - mh - dh - 1, 1, dh + 1,
            mix(0, bg.red, mist),
            mix(0, bg.green, mist),
            mix(0, bg.blue, mist),
            255
          );
          EZ_trace_rectangle_plein(x - 1, height / 2 + mh - 1, 1, dh + 1,
            mix(0, bg.red, mist),
            mix(0, bg.green, mist),
            mix(0, bg.blue, mist),
            255
          );
          break;
          #endif// DRAW_OUTLINE
      }
      #ifdef DRAW_OUTLINE
      last_h = h;
      last_dist = dist;
      #endif// DRAW_OUTLINE
    }
    #ifdef DRAW_OUTLINE
    if (r.pos.success && r.index != last_index && x > 1 || !r.pos.success && last_index != -1) {
      double mist = 1 - 1 / (1 + last_dist * last_dist / sqrt(length));
      EZ_trace_rectangle_plein(x - 1, height / 2 - last_h, 1, last_h * 2,
        mix(0, bg.red, mist),
        mix(0, bg.green, mist),
        mix(0, bg.blue, mist),
        255
      );
    }
    if (r.pos.success) {
      last_index = r.index;
    } else {
      last_index = -1;
    }
    #endif// DRAW_OUTLINE
  }
}
