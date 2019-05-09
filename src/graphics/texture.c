#define STB_IMAGE_IMPLEMENTATION
#include "texture.h"

DEF_TEXTURE(texture_flat) {
    double y = height / 2 - h;
    EZ_trace_rectangle_plein((uint32_t)x, (uint32_t)y, 0, (uint32_t)(h * 2), line->color.red, line->color.green, line->color.blue, mix(0, 255, opacity));
}

DEF_TEXTURE(texture_checkerboard) {
    #define N 8
    double y = height / 2 - h;
    double sy = h * 2 / N;
    double texture_x = dist2D(&hit->pos, &line->pos);
    bool j = (uint32_t)(texture_x * N * 2) % 2;
    EZ_trace_rectangle_plein((uint32_t)x, (uint32_t)(height / 2 - h), 0, (uint32_t)(h * 2), line->color.red, line->color.green, line->color.blue, mix(0, 255, opacity));
    for (int i = 0; i < N; i++) {
        if (y > height) break;
        if (i % 2 != j) {
            EZ_trace_rectangle_plein((uint32_t)x, (uint32_t)y, 0, (uint32_t)sy, line->color.red * 0.95, line->color.green * 0.95, line->color.blue * 0.95, mix(0, 255, opacity));
        }
        y += sy;
    }
}

DEF_TEXTURE(texture_gradient) {
    Color* c = (Color*)line->texture_data;
    double texture_x = dist2D(&hit->pos, &line->pos) / line->length;
    double y = height / 2 - h;
    EZ_trace_rectangle_plein((uint32_t) x, (uint32_t) y, 0, (uint32_t)(h * 2),
    mix(line->color.red, c->red, texture_x),
    mix(line->color.green, c->green, texture_x),
    mix(line->color.blue, c->blue, texture_x),
    mix(0, 255, opacity));
}

DEF_TEXTURE(texture_image) {
    TextureImage* img = (TextureImage*) line->texture_data;
    double texture_x = dist2D(&hit->pos, &line->pos);
    if (texture_x < img->width / IMAGE_ADJUST) {
        double y = height / 2 - h + (1 - img->height) * h * 2;

        int tex_x = (int) (texture_x * img->tex_width / img->width * IMAGE_ADJUST);

        double sy = img->height * h * 2 / img->tex_height;
        for (int tex_y = 0; tex_y < img->tex_height; tex_y++) {
            if (y > height) break;
            uint8_t alpha = img->pixels[(4 * (tex_y * img->tex_width + tex_x) + 3)];

            if (alpha != 0) {
                uint8_t red = img->pixels[(4 * (tex_y * img->tex_width + tex_x))];
                uint8_t green = img->pixels[(4 * (tex_y * img->tex_width + tex_x) + 1)];
                uint8_t blue = img->pixels[(4 * (tex_y * img->tex_width + tex_x) + 2)];

                EZ_trace_rectangle_plein((uint32_t) x, (uint32_t) y, 0, (uint32_t) sy, red, green, blue, alpha);
            }
            y += sy;
        }
    }
}

DEF_TEXTURE(texture_empty) {
  // nothing!
}
