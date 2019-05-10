#define LEVEL_1 \
    CREATE_LINE(a, 0, 0, 1, 0)\
    LINE_COLOR(a, 83, 190, 187)\
    LINE_GRADIENT(a, 65, 159, 199)\
    LINE_BOUNCE(a)\
\
    CREATE_LINE(b, 0, 0, 0, 1)\
    LINE_COLOR(b, 113, 190, 118)\
    LINE_CHECKERBOARD(b)\
\
    CREATE_LINE(c, 0, 1, -0.5, 1)\
    LINE_COLOR(c, 228, 214, 84)\
    LINE_GRADIENT(c, 244, 130, 137)\
\
    CREATE_LINE(d, -2, -0.5, -2, 0.5)\
    LINE_TRANSPARENT(d, 128)\
    LINE_COLOR(d, 122, 58, 144)\
\
    CREATE_LINE(e, -1.5, -0.5, -1, -0.5)\
    LINE_IMAGE(e, "../resources/flower.png", 0.5, 0.5)\
\
    double D = 32;\
\
    CREATE_LINE(f, 2, D, 2, -D)\
    LINE_COLOR(f, 180, 191, 122)\
\
    CREATE_LINE(g, -2.5, D, -2.5, -D)\
    LINE_COLOR(g, 125, 125, 125)\
    LINE_BOUNCE(g)\
\
    CREATE_LINE(h, D, 2, -D, 2)\
    CREATE_LINE(i, D, -2.5, -D, -2.5)\
\
    LINE_TELEPORT(h, i)\
    LINE_TELEPORT(i, h)\
\
    Color bg = Color_new(209, 213, 201);\
\
    Lines lines;\
    lines.length = 9;\
    lines.lines = (Line2D*) malloc(sizeof(Line2D) * lines.length);\
\
    lines.lines[0] = a;\
    lines.lines[1] = b;\
    lines.lines[2] = c;\
    lines.lines[3] = d;\
    lines.lines[4] = e;\
    lines.lines[5] = f;\
    lines.lines[6] = g;\
    lines.lines[7] = h;\
    lines.lines[8] = i;

#define REG_LINE(name) lines.lines[line_index++] = name;

#define LEVEL_2 \
    CREATE_ROOM(r1, -5, 0, 5, 2)\
    ROOM_COLOR(r1, 101, 120, 116)\
\
    CREATE_ROOM(r2, -5, 2, 5, 2)\
    ROOM_COLOR(r2, 100, 106, 115)\
\
    Lines lines;\
    size_t line_index = 0;\
    lines.length = 13;\
    lines.lines = (Line2D*) malloc(sizeof(Line2D) * lines.length);\
\
    CREATE_LINE(w1, 0, 0, 0, 1)\
    LINE_COLOR(w1, 176, 172, 184)\
    LINE_CHECKERBOARD(w1)\
    REG_LINE(w1)\
\
    CREATE_LINE(w2, 0, 2, 0, 4)\
    LINE_COLOR(w2, 176, 172, 184)\
    LINE_CHECKERBOARD(w2)\
    REG_LINE(w2)\
\
    CREATE_LINE(w3, -1, 4, -5, 4)\
    LINE_COLOR(w3, 176, 172, 184)\
    REG_LINE(w3)\
\
    CREATE_LINE(w4, -5, 4, -5, 3)\
    LINE_COLOR(w4, 176, 172, 184)\
    REG_LINE(w4)\
\
    CREATE_LINE(w5, -5, 2, -5, 0)\
    LINE_COLOR(w5, 176, 172, 184)\
    REG_LINE(w5)\
\
    CREATE_LINE(w6, -5, 0, -4, 0)\
    LINE_COLOR(w6, 176, 172, 184)\
    REG_LINE(w6)\
\
    CREATE_LINE(w7, -3, 0, 0, 0)\
    LINE_COLOR(w7, 176, 172, 184)\
    LINE_CHECKERBOARD(w7)\
    REG_LINE(w7)\
\
    CREATE_LINE(m1, 0, 1, 0, 2)\
    LINE_COLOR(m1, 173, 208, 230)\
    LINE_BOUNCE(m1)\
    ROOMS_AROUND(m1, r1, r1)\
    REG_LINE(m1)\
\
    CREATE_LINE(m2, -5, 3, -5, 2)\
    LINE_COLOR(m2, 173, 208, 230)\
    LINE_BOUNCE(m2)\
    ROOMS_AROUND(m2, r2, r2)\
    REG_LINE(m2)\
\
    CREATE_LINE(t1, -3, 0, -4, 0)\
    CREATE_LINE(t2, 0, 4, -1, 4)\
    LINE_TELEPORT(t1, t2)\
    LINE_TELEPORT(t2, t1)\
    ROOMS_AROUND(t1, r2, r1)\
    ROOMS_AROUND(t2, r2, r1)\
    REG_LINE(t1)\
    REG_LINE(t2)\
\
    CREATE_LINE(f1, -4.25, 3, -4, 3)\
    LINE_IMAGE(f1, "../resources/flower.png", 0.5, 0.5)\
    ROOMS_AROUND(f1, r2, r2)\
    REG_LINE(f1)\
\
    CREATE_LINE(g1, -5, 2, 0, 2)\
    LINE_GHOST(g1)\
    ROOMS_AROUND(g1, r2, r1)\
    REG_LINE(g1)\
\
    Color bg = Color_new(107, 110, 101);\
\
    world.n_rooms = 2;\
    world.rooms = (Room**)malloc(sizeof(Room*) * world.n_rooms);\
    world.rooms[0] = &r1;\
    world.rooms[1] = &r2;
