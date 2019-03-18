#include "vec2d.h"

Vec2D Vec2D_new(double x, double y) {
    Vec2D res;
    res.x = x;
    res.y = y;
    return res;
}

double dot2D(const Vec2D* a, const Vec2D* b) {
    return a->x * b->x + a->y * b->y;
}

Vec2D norm2D(const Vec2D* in) {
    if (approx_eq(in->x, 0) && approx_eq(in->y, 0)) {
        // ERROR ERROR
        fprintf(stderr, "Tried to normalize a null vector!\n");
    }
    double l = sqrt(in->x * in->x + in->y * in->y);
    Vec2D res;
    res.x = in->x / l;
    res.y = in->y / l;
    return res;
}

double dist2D(const Vec2D* a, const Vec2D* b) {
    double c = a->x - b->x;
    double d = a->y - b->y;
    return sqrt(c * c + d * d);
}

double length2D(const Vec2D* a) {
    return sqrt(a->x * a->x + a->y * a->y);
}

Vec2D Vec2D_sub(const Vec2D* a, const Vec2D* b) {
    Vec2D res;
    res.x = a->x - b->x;
    res.y = a->y - b->y;
    return res;
}

Vec2D Vec2D_sum(const Vec2D* a, const Vec2D* b) {
    Vec2D res;
    res.x = a->x + b->x;
    res.y = a->y + b->y;
    return res;
}

Vec2D Vec2D_mult(const Vec2D* a, double by) {
    Vec2D res;
    res.x = a->x * by;
    res.y = a->y * by;
    return res;
}

bool Vec2D_eq(const Vec2D* a, const Vec2D* b) {
    return approx_eq(a->x, b->x) && approx_eq(a->y, b->y);
}

Vec2D Vec2D_normal(const Vec2D* vec) {
    return Vec2D_new(-vec->y, vec->x);
}
