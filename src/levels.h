#define LEVEL_1 \
  CREATE_LINE(a, 0, 0, 1, 0);\
  LINE_COLOR(a, 83, 190, 187);\
  LINE_GRADIENT(a, 65, 159, 199);\
  LINE_BOUNCE(a);\
\
  CREATE_LINE(b, 0, 0, 0, 1);\
  LINE_COLOR(b, 113, 190, 118);\
  LINE_CHECKERBOARD(b);\
\
  CREATE_LINE(c, 0, 1, -0.5, 1);\
  LINE_COLOR(c, 228, 214, 84);\
  LINE_GRADIENT(c, 244, 130, 137);\
\
  CREATE_LINE(d, -2, -0.5, -2, 0.5);\
  LINE_TRANSPARENT(d, 128);\
  LINE_COLOR(d, 122, 58, 144);\
\
  CREATE_LINE(e, -1.5, -0.5, -1, -0.5);\
  LINE_IMAGE(e, "../resources/flower.png", 0.5, 0.5);\
\
  double D = 32;\
\
  CREATE_LINE(f, 2, D, 2, -D);\
  LINE_COLOR(f, 180, 191, 122);\
\
  CREATE_LINE(g, -2.5, D, -2.5, -D);\
  LINE_COLOR(g, 125, 125, 125);\
  LINE_BOUNCE(g);\
\
  CREATE_LINE(h, D, 2, -D, 2);\
  CREATE_LINE(i, D, -2.5, -D, -2.5);\
\
  LINE_TELEPORT(h, i);\
  LINE_TELEPORT(i, h);\
\
  Color bg = Color_new(209, 213, 201);\
\
  Lines lines;\
  lines.length = 9;\
  lines.lines = (Line2D*) malloc(sizeof(Line2D) * lines.length);\
  lines.lines[0] = a;\
  lines.lines[1] = b;\
  lines.lines[2] = c;\
  lines.lines[3] = d;\
  lines.lines[4] = e;\
  lines.lines[5] = f;\
  lines.lines[6] = g;\
  lines.lines[7] = h;\
  lines.lines[8] = i;


#define LEVEL_2 \
  CREATE_LINE(w1, 0, 0, 0, 1);\
  LINE_COLOR(w1, 176, 172, 184);\
  LINE_CHECKERBOARD(w1);\
\
  CREATE_LINE(w2, 0, 2, 0, 4);\
  LINE_COLOR(w2, 176, 172, 184);\
  LINE_CHECKERBOARD(w2);\
\
  CREATE_LINE(w3, -1, 4, -5, 4);\
  LINE_COLOR(w3, 176, 172, 184);\
\
  CREATE_LINE(w4, -5, 4, -5, 3);\
  LINE_COLOR(w4, 176, 172, 184);\
\
  CREATE_LINE(w5, -5, 2, -5, 0);\
  LINE_COLOR(w5, 176, 172, 184);\
\
  CREATE_LINE(w6, -5, 0, -4, 0);\
  LINE_COLOR(w6, 176, 172, 184);\
\
  CREATE_LINE(w7, -3, 0, 0, 0);\
  LINE_COLOR(w7, 176, 172, 184);\
  LINE_CHECKERBOARD(w7);\
\
  CREATE_LINE(m1, 0, 1, 0, 2);\
  LINE_COLOR(m1, 173, 208, 230);\
  LINE_BOUNCE(m1);\
\
  CREATE_LINE(m2, -5, 2, -5, 3);\
  LINE_COLOR(m2, 173, 208, 230);\
  LINE_BOUNCE(m2);\
\
  CREATE_LINE(t1, -3, 0, -4, 0);\
  CREATE_LINE(t2, 0, 4, -1, 4);\
  LINE_TELEPORT(t1, t2);\
  LINE_TELEPORT(t2, t1);\
\
  CREATE_LINE(f1, -4.25, 3, -3.75, 3);\
  LINE_IMAGE(f1, "../resources/flower.png", 0.5, 0.5);\
\
  CREATE_LINE(g1, 0, 2 - EPSILON, -5, 2 - EPSILON);\
  LINE_TRANSPARENT(g1, 255);\
  LINE_COLOR(g1, 76, 144, 87);\
  g1.texture = &texture_ground;\
\
  CREATE_LINE(g2a, 0, 2 + EPSILON, -5, 2 + EPSILON);\
  LINE_TRANSPARENT(g2a, 255);\
  LINE_COLOR(g2a, 196, 146, 87);\
  g2a.texture = &texture_ground;\
\
  CREATE_LINE(g2b, -5 + 4 * EPSILON, 2 + EPSILON, -5 + 4 * EPSILON, 4 - 4 * EPSILON);\
  LINE_TRANSPARENT(g2b, 255);\
  LINE_COLOR(g2b, 196, 146, 87);\
  g2b.texture = &texture_ground;\
\
  CREATE_LINE(g2c, 0 - 4 * EPSILON, 2 + EPSILON, 0 - 4 * EPSILON, 4 - 4 * EPSILON);\
  LINE_TRANSPARENT(g2c, 255);\
  LINE_COLOR(g2c, 196, 146, 87);\
  g2c.texture = &texture_ground;\
\
  CREATE_LINE(g2d, 0 - 4 * EPSILON, 4 - 4 * EPSILON, -5 + 4 * EPSILON, 4 - 4 * EPSILON);\
  LINE_TRANSPARENT(g2d, 255);\
  LINE_COLOR(g2d, 196, 146, 87);\
  g2d.texture = &texture_ground;\
\
  Color bg = Color_new(107, 110, 101);\
\
  Lines lines;\
  lines.length = 17;\
  lines.lines = (Line2D*) malloc(sizeof(Line2D) * lines.length);\
  lines.lines[0] = w1;\
  lines.lines[1] = w2;\
  lines.lines[2] = w3;\
  lines.lines[3] = w4;\
  lines.lines[4] = w5;\
  lines.lines[5] = w6;\
  lines.lines[6] = w7;\
  lines.lines[7] = m1;\
  lines.lines[8] = m2;\
  lines.lines[9] = t1;\
  lines.lines[10] = t2;\
  lines.lines[11] = f1;\
  lines.lines[12] = g1;\
  lines.lines[13] = g2a;\
  lines.lines[14] = g2b;\
  lines.lines[15] = g2c;\
  lines.lines[16] = g2d;
