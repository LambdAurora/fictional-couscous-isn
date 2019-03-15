#include "raytracing.h"

// TODO: replace `lines` with `world`
void sweep(
  int width, int height,
  Lines *lines,
  const Vec2D *camera_pos,
  double rotation, double fov, double length,
  const Color *bg, double mist_length
) {
  int x;
  int last_h = 0;
  int last_index = -1;
  double last_dist = 0;
  Line2D* last_line = NULL;
  for (x = 0; x < width; x++) {
    double last_drawn_h = 0;
    double angle = rotation + ((double)x - (double)width / 2) / (double) width * 2 * fov;
    Line2D ray;
    Line2D* last_drawn_line;
    double dist = 0;
    ray.length = length;
    ray.pos = *camera_pos;
    ray.vec.x = cos(angle);
    ray.vec.y = sin(angle);
    int n = 0;
    RayIntersection r = cast_ray(lines, &ray);
    for (n = MAX_BOUNCES - 1; n >= 0; n--) {
      if (r.hits[n].line == NULL) continue;
      if (r.success) {
        Hit hit = r.hits[n];
        Line2D *line = hit.line;
        int h = (int)((double)height / 2 / hit.dist);
        double mist = 1 - 1 / (1 + hit.dist * hit.dist / mist_length);
        uint8_t red = line->color.red;
        uint8_t green = line->color.green;
        uint8_t blue = line->color.blue;
        // uint8_t red = mix(line->color.red, bg->red, mist);
        // uint8_t green = mix(line->color.green, bg->green, mist);
        // uint8_t blue = mix(line->color.blue, bg->blue, mist);
        int h2 = (int)((double)height / sqrt(hit.dist*hit.dist + 4));
        int mh = h < last_h ? h : last_h;
        int dh = h < last_h ? last_h - h : h - last_h;
        switch (line->type) {
          case NORMAL_LINE:
            last_drawn_line = line;
            EZ_trace_rectangle_plein(x, height / 2 - h, 0, h * 2, red, green, blue, mix(255, 0, mist));

            #ifdef DRAW_REFLECTION
            EZ_trace_rectangle_plein(
              x, height / 2 + h, 0, h2,
              mix(red, bg->red, REFLECTION_AMOUNT),
              mix(green, bg->green, REFLECTION_AMOUNT),
              mix(blue, bg->blue, REFLECTION_AMOUNT),
              255);
            #endif// DRAW_REFLECTION

            #ifdef DRAW_OUTLINE
            EZ_trace_rectangle_plein(x - 1, height / 2 - mh - dh - 1, 1, dh + 1,
              0, 0, 0,
              mix(255, 0, mist)
            );
            EZ_trace_rectangle_plein(x - 1, height / 2 + mh - 1, 1, dh + 1,
              0, 0, 0,
              mix(255, 0, mist)
            );
            last_drawn_h = h;
            dist = hit.dist;
            #endif// DRAW_OUTLINE
            break;
          case BOUNCE_LINE:
            EZ_trace_rectangle_plein(x, height / 2 - h, 0, h * 2, red, green, blue, mix(64, 0, mist));
        }
      }
    }
    #ifdef DRAW_OUTLINE
    if (last_drawn_h != 0 && last_drawn_line != last_line && x > 1 || last_drawn_h == 0 && last_h != 0) {
      double _dist = last_drawn_h > last_h ? dist : last_dist;
      double mist = 1 - 1 / (1 + _dist * _dist / mist_length);
      if (last_h != 0) {
        EZ_trace_rectangle_plein(x - 1, height / 2 - last_h, 1, last_h * 2,
          0, 0, 0,
          mix(255, 0, mist)
        );
        // EZ_trace_rectangle_plein(x - 1, height / 2 - last_h, 1, last_h * 2,
        //   mix(0, bg->red, mist),
        //   mix(0, bg->green, mist),
        //   mix(0, bg->blue, mist),
        //   255
        // );
      }
    }
    if (last_drawn_h != 0) {
      last_line = last_drawn_line;
    } else {
      last_line = NULL;
    }
    last_dist = dist;
    last_h = last_drawn_h;
    #endif// DRAW_OUTLINE
  }
}
