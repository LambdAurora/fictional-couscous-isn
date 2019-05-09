#include "geometry.h"
#include "../graphics/texture.h"

Line2D Line2D_new(const Vec2D* from, const Vec2D* to) {
    Line2D res;
    if (Vec2D_eq(from, to)) { // c'est un point, mais heh
        res.pos.x = from->x;
        res.pos.y = from->y;
        res.vec.x = 1;
        res.vec.y = 0;
        res.length = 0;
    } else {
        Vec2D diff = Vec2D_sub(to, from);
        Vec2D norm = norm2D(&diff);
        res.pos.x = from->x;
        res.pos.y = from->y;
        res.vec.x = norm.x;
        res.vec.y = norm.y;
        res.length = length2D(&diff);
    }
    // Définition des valeurs par défaut.
    res.type = NORMAL_LINE;
    res.data = NULL;
    res.texture = &texture_flat;
    res.texture_data = NULL;
    res.color.red = 255;
    res.color.green = 255;
    res.color.blue = 255;
    return res;
}
