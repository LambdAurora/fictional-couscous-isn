#define LEVEL_1 \
    world.n_rooms = 0; \
    world.rooms = (Room**)malloc(sizeof(Room*) * world.n_rooms); \
    world.player_position = Vec2D_new(-0.7, 0.35); \
    world.player_angle = 0; \
    Color bg = Color_new(209, 213, 201); \
    Lines lines; \
    lines.length = 9; \
    lines.lines = (Line2D*) malloc(sizeof(Line2D) * lines.length); \
     \
    CREATE_LINE(_w_0, 0, 0, 0.7, 0) \
    LINE_COLOR(_w_0, 83, 190, 187) \
    LINE_BOUNCE(_w_0) \
    LINE_GRADIENT(_w_0, 65,159,199) \
     \
    CREATE_LINE(_w_1, 0, 0, 0, 0.7) \
    LINE_COLOR(_w_1, 113, 190, 118) \
    LINE_CHECKERBOARD(_w_1) \
     \
    CREATE_LINE(_w_2, 0, 0.7, -0.35, 0.7) \
    LINE_COLOR(_w_2, 228, 214, 84) \
    LINE_GRADIENT(_w_2, 244,130,137) \
     \
    CREATE_LINE(_w_3, -1.4, -0.35, -1.4, 0.35) \
    LINE_COLOR(_w_3, 122, 58, 144) \
    LINE_TRANSPARENT(_w_3, 127.5) \
     \
    CREATE_LINE(_w_4, -1.0499999999999998, -0.35, -0.7, -0.35) \
    LINE_IMAGE(_w_4, "../resources/flower.png",0.5,0.5) \
    LINE_GHOST(_w_4) \
     \
    CREATE_LINE(_w_5, 1.4, 1.4, 1.4, -1.75) \
    LINE_COLOR(_w_5, 180, 191, 122) \
     \
    CREATE_LINE(_w_6, -1.75, 1.4, -1.75, -1.75) \
    LINE_COLOR(_w_6, 125, 125, 125) \
    LINE_BOUNCE(_w_6) \
     \
    CREATE_LINE(_w_7, 1.4, 1.4, -1.75, 1.4) \
     \
    CREATE_LINE(_w_8, 1.4, -1.75, -1.75, -1.75) \
     \
    LINE_TELEPORT(_w_7, _w_8) \
     \
    LINE_TELEPORT(_w_8, _w_7) \
     \
    lines.lines[0] = _w_0; \
    lines.lines[1] = _w_1; \
    lines.lines[2] = _w_2; \
    lines.lines[3] = _w_3; \
    lines.lines[4] = _w_4; \
    lines.lines[5] = _w_5; \
    lines.lines[6] = _w_6; \
    lines.lines[7] = _w_7; \
    lines.lines[8] = _w_8; \

#define LEVEL_2 \
    world.n_rooms = 2; \
    world.rooms = (Room**)malloc(sizeof(Room*) * world.n_rooms); \
    CREATE_ROOM(_r_0, -5, 0, 5, 2) \
    ROOM_COLOR(_r_0, 101, 120, 116) \
    world.rooms[0] = &_r_0; \
    CREATE_ROOM(_r_1, -5, 2, 5, 2) \
    ROOM_COLOR(_r_1, 100, 106, 115) \
    world.rooms[1] = &_r_1; \
    world.player_position = Vec2D_new(-1, 0.5); \
    world.player_angle = 0; \
    Color bg = Color_new(107, 110, 101); \
    Lines lines; \
    lines.length = 13; \
    lines.lines = (Line2D*) malloc(sizeof(Line2D) * lines.length); \
     \
    CREATE_LINE(_w_0, 0, 0, 0, 1) \
    LINE_COLOR(_w_0, 176, 172, 184) \
    LINE_CHECKERBOARD(_w_0) \
    ROOM_LEFT(_w_0, _r_0) \
     \
    CREATE_LINE(_w_1, 0, 2, 0, 4) \
    LINE_COLOR(_w_1, 176, 172, 184) \
    LINE_CHECKERBOARD(_w_1) \
    ROOM_LEFT(_w_1, _r_1) \
     \
    CREATE_LINE(_w_2, -1, 4, -5, 4) \
    LINE_COLOR(_w_2, 176, 172, 184) \
    ROOM_LEFT(_w_2, _r_1) \
     \
    CREATE_LINE(_w_3, -5, 4, -5, 3) \
    LINE_COLOR(_w_3, 176, 172, 184) \
    ROOM_LEFT(_w_3, _r_1) \
     \
    CREATE_LINE(_w_4, -5, 2, -5, 0) \
    LINE_COLOR(_w_4, 176, 172, 184) \
    ROOM_LEFT(_w_4, _r_0) \
     \
    CREATE_LINE(_w_5, -5, 0, -4, 0) \
    LINE_COLOR(_w_5, 176, 172, 184) \
    ROOM_LEFT(_w_5, _r_0) \
     \
    CREATE_LINE(_w_6, -3, 0, 0, 0) \
    LINE_COLOR(_w_6, 176, 172, 184) \
    LINE_CHECKERBOARD(_w_6) \
    ROOM_LEFT(_w_6, _r_0) \
     \
    CREATE_LINE(_w_7, 0, 1, 0, 2) \
    LINE_COLOR(_w_7, 182, 196, 190) \
    LINE_BOUNCE(_w_7) \
    ROOM_RIGHT(_w_7, _r_0) \
     \
    CREATE_LINE(_w_8, -5, 3, -5, 2) \
    LINE_COLOR(_w_8, 182, 196, 190) \
    LINE_BOUNCE(_w_8) \
    ROOM_RIGHT(_w_8, _r_1) \
     \
    CREATE_LINE(_w_9, -3, 0, -4, 0) \
    ROOM_LEFT(_w_9, _r_1) \
     \
    CREATE_LINE(_w_10, 0, 4, -1, 4) \
    ROOM_RIGHT(_w_10, _r_0) \
     \
    CREATE_LINE(_w_11, -4.25, 3, -4, 3) \
    LINE_IMAGE(_w_11, "../resources/flower.png",0.5,0.5) \
    ROOMS_AROUND(_w_11, _r_1, _r_1) \
     \
    CREATE_LINE(_w_12, -5, 2, 0, 2) \
    LINE_EMPTY(_w_12) \
    LINE_GHOST(_w_12) \
    ROOMS_AROUND(_w_12, _r_1, _r_0) \
     \
    LINE_TELEPORT(_w_9, _w_10) \
     \
    LINE_TELEPORT(_w_10, _w_9) \
     \
    lines.lines[0] = _w_0; \
    lines.lines[1] = _w_1; \
    lines.lines[2] = _w_2; \
    lines.lines[3] = _w_3; \
    lines.lines[4] = _w_4; \
    lines.lines[5] = _w_5; \
    lines.lines[6] = _w_6; \
    lines.lines[7] = _w_7; \
    lines.lines[8] = _w_8; \
    lines.lines[9] = _w_9; \
    lines.lines[10] = _w_10; \
    lines.lines[11] = _w_11; \
    lines.lines[12] = _w_12; \

#define LEVEL_3 \
    world.n_rooms = 3; \
    world.rooms = (Room**)malloc(sizeof(Room*) * world.n_rooms); \
    CREATE_ROOM(_r_0, 0, 0, 3, 3) \
    ROOM_COLOR(_r_0, 230, 32, 32) \
    world.rooms[0] = &_r_0; \
    CREATE_ROOM(_r_1, 0, 3, 3, 3) \
    ROOM_COLOR(_r_1, 32, 230, 32) \
    world.rooms[1] = &_r_1; \
    CREATE_ROOM(_r_2, 3, 0, 3, 3) \
    ROOM_COLOR(_r_2, 32, 32, 230) \
    world.rooms[2] = &_r_2; \
    world.player_position = Vec2D_new(1.5, 1.5); \
    world.player_angle = 0; \
    Color bg = Color_new(107, 110, 101); \
    Lines lines; \
    lines.length = 21; \
    lines.lines = (Line2D*) malloc(sizeof(Line2D) * lines.length); \
     \
    CREATE_LINE(_w_0, 3, 0, 3, 0.25) \
    LINE_COLOR(_w_0, 95, 94, 97) \
    LINE_GRADIENT(_w_0, 106,106,106) \
    ROOMS_AROUND(_w_0, _r_0, _r_2) \
     \
    CREATE_LINE(_w_1, 3, 3, 3, 2.75) \
    LINE_COLOR(_w_1, 95, 94, 97) \
    LINE_GRADIENT(_w_1, 106,106,106) \
    ROOMS_AROUND(_w_1, _r_2, _r_0) \
     \
    CREATE_LINE(_w_2, 0, 3, 0.25, 3) \
    LINE_COLOR(_w_2, 95, 94, 97) \
    LINE_GRADIENT(_w_2, 106,106,106) \
    ROOMS_AROUND(_w_2, _r_1, _r_0) \
     \
    CREATE_LINE(_w_3, 3, 3, 2.75, 3) \
    LINE_COLOR(_w_3, 95, 94, 97) \
    LINE_GRADIENT(_w_3, 106,106,106) \
    ROOMS_AROUND(_w_3, _r_0, _r_1) \
     \
    CREATE_LINE(_w_4, 3, 3, 3.25, 3) \
    LINE_COLOR(_w_4, 95, 94, 97) \
    LINE_GRADIENT(_w_4, 106,106,106) \
    ROOM_RIGHT(_w_4, _r_2) \
     \
    CREATE_LINE(_w_5, 6, 3, 5.75, 3) \
    LINE_COLOR(_w_5, 95, 94, 97) \
    LINE_GRADIENT(_w_5, 106,106,106) \
    ROOM_LEFT(_w_5, _r_2) \
     \
    CREATE_LINE(_w_6, 3, 3, 3, 3.25) \
    LINE_COLOR(_w_6, 95, 94, 97) \
    LINE_GRADIENT(_w_6, 106,106,106) \
    ROOM_LEFT(_w_6, _r_1) \
     \
    CREATE_LINE(_w_7, 3, 6, 3, 5.75) \
    LINE_COLOR(_w_7, 95, 94, 97) \
    LINE_GRADIENT(_w_7, 106,106,106) \
    ROOM_RIGHT(_w_7, _r_1) \
     \
    CREATE_LINE(_w_8, 0, 0, 0.5, 0) \
    LINE_COLOR(_w_8, 164, 119, 116) \
    LINE_CHECKERBOARD(_w_8) \
    ROOM_LEFT(_w_8, _r_0) \
     \
    CREATE_LINE(_w_9, 0.5, 0, 2.5, 0) \
    LINE_COLOR(_w_9, 227, 202, 233) \
    LINE_BOUNCE(_w_9) \
    ROOM_RIGHT(_w_9, _r_0) \
     \
    CREATE_LINE(_w_10, 2.5, 0, 3, 0) \
    LINE_COLOR(_w_10, 164, 119, 116) \
    LINE_CHECKERBOARD(_w_10) \
    ROOM_LEFT(_w_10, _r_0) \
     \
    CREATE_LINE(_w_11, 0, 0, 0, 3) \
    LINE_COLOR(_w_11, 164, 119, 116) \
    LINE_CHECKERBOARD(_w_11) \
    ROOM_RIGHT(_w_11, _r_0) \
     \
    CREATE_LINE(_w_12, 0, 3, 0, 6) \
    LINE_COLOR(_w_12, 138, 171, 150) \
    LINE_CHECKERBOARD(_w_12) \
    ROOM_RIGHT(_w_12, _r_1) \
     \
    CREATE_LINE(_w_13, 0, 6, 3, 6) \
    LINE_COLOR(_w_13, 138, 171, 150) \
    LINE_CHECKERBOARD(_w_13) \
    ROOM_RIGHT(_w_13, _r_1) \
     \
    CREATE_LINE(_w_14, 3, 0, 6, 0) \
    LINE_COLOR(_w_14, 126, 145, 177) \
    LINE_CHECKERBOARD(_w_14) \
    ROOM_LEFT(_w_14, _r_2) \
     \
    CREATE_LINE(_w_15, 6, 0, 6, 3) \
    LINE_COLOR(_w_15, 126, 145, 177) \
    LINE_CHECKERBOARD(_w_15) \
    ROOM_LEFT(_w_15, _r_2) \
     \
    CREATE_LINE(_w_16, 3, 3.25, 3, 5.75) \
    ROOM_RIGHT(_w_16, _r_2) \
     \
    CREATE_LINE(_w_17, 3.25, 3, 5.75, 3) \
    ROOM_LEFT(_w_17, _r_1) \
     \
    CREATE_LINE(_w_18, 0.25, 0.25, 0.5, 0.25) \
    LINE_IMAGE(_w_18, "../resources/flower.png",0.5,0.5) \
    LINE_GHOST(_w_18) \
    ROOMS_AROUND(_w_18, _r_0, _r_0) \
     \
    CREATE_LINE(_w_19, 0.25, 3, 2.75, 3) \
    LINE_EMPTY(_w_19) \
    LINE_GHOST(_w_19) \
    ROOMS_AROUND(_w_19, _r_1, _r_0) \
     \
    CREATE_LINE(_w_20, 3, 0.25, 3, 2.75) \
    LINE_EMPTY(_w_20) \
    LINE_GHOST(_w_20) \
    ROOMS_AROUND(_w_20, _r_0, _r_2) \
     \
    LINE_TELEPORT(_w_16, _w_17) \
     \
    LINE_TELEPORT(_w_17, _w_16) \
     \
    lines.lines[0] = _w_0; \
    lines.lines[1] = _w_1; \
    lines.lines[2] = _w_2; \
    lines.lines[3] = _w_3; \
    lines.lines[4] = _w_4; \
    lines.lines[5] = _w_5; \
    lines.lines[6] = _w_6; \
    lines.lines[7] = _w_7; \
    lines.lines[8] = _w_8; \
    lines.lines[9] = _w_9; \
    lines.lines[10] = _w_10; \
    lines.lines[11] = _w_11; \
    lines.lines[12] = _w_12; \
    lines.lines[13] = _w_13; \
    lines.lines[14] = _w_14; \
    lines.lines[15] = _w_15; \
    lines.lines[16] = _w_16; \
    lines.lines[17] = _w_17; \
    lines.lines[18] = _w_18; \
    lines.lines[19] = _w_19; \
    lines.lines[20] = _w_20; \

#define LEVEL_4 \
    world.n_rooms = 5; \
    world.rooms = (Room**)malloc(sizeof(Room*) * world.n_rooms); \
    CREATE_ROOM(_r_0, 1.6, -0.4, 0.4, 2) \
    ROOM_COLOR(_r_0, 56, 56, 56) \
    world.rooms[0] = &_r_0; \
    CREATE_ROOM(_r_1, -0.2, -0.4, 0.4, 0.8) \
    ROOM_COLOR(_r_1, 56, 56, 56) \
    world.rooms[1] = &_r_1; \
    CREATE_ROOM(_r_2, 1.5, 2.3000000000000003, 0.6000000000000001, 0.6000000000000001) \
    ROOM_COLOR(_r_2, 58, 131, 32) \
    world.rooms[2] = &_r_2; \
    CREATE_ROOM(_r_3, -0.30000000000000004, -1.3, 0.6000000000000001, 0.6000000000000001) \
    ROOM_COLOR(_r_3, 41, 74, 125) \
    world.rooms[3] = &_r_3; \
    CREATE_ROOM(_r_4, -858993459.2, -858993459.2, 1717986918.4, 1717986918.4) \
    ROOM_COLOR(_r_4, 139, 143, 147) \
    world.rooms[4] = &_r_4; \
    world.player_position = Vec2D_new(1.75, -1.5); \
    world.player_angle = 1.5707963267948966; \
    Color bg = Color_new(169, 180, 189); \
    Lines lines; \
    lines.length = 24; \
    lines.lines = (Line2D*) malloc(sizeof(Line2D) * lines.length); \
     \
    CREATE_LINE(_w_0, -0.2, -0.39996000000000004, 0.2, -0.39996000000000004) \
    ROOMS_AROUND(_w_0, _r_0, _r_4) \
     \
    CREATE_LINE(_w_1, -0.2, 0.39996000000000004, 0.2, 0.39996000000000004) \
    ROOMS_AROUND(_w_1, _r_4, _r_0) \
     \
    CREATE_LINE(_w_2, 1.6, -0.39996000000000004, 2, -0.39996000000000004) \
    ROOMS_AROUND(_w_2, _r_1, _r_4) \
     \
    CREATE_LINE(_w_3, 1.6, 1.59996, 2, 1.59996) \
    ROOMS_AROUND(_w_3, _r_4, _r_1) \
     \
    CREATE_LINE(_w_4, -0.2, -0.4, 0.2, -0.4) \
    ROOMS_AROUND(_w_4, _r_0, _r_0) \
     \
    CREATE_LINE(_w_5, -0.2, 0.4, 0.2, 0.4) \
    ROOMS_AROUND(_w_5, _r_0, _r_0) \
     \
    CREATE_LINE(_w_6, 1.6, -0.4, 2, -0.4) \
    ROOMS_AROUND(_w_6, _r_1, _r_1) \
     \
    CREATE_LINE(_w_7, 1.6, 1.6, 2, 1.6) \
    ROOMS_AROUND(_w_7, _r_1, _r_1) \
     \
    CREATE_LINE(_w_8, -0.2, -0.4, -0.2, 0.4) \
    LINE_COLOR(_w_8, 13, 74, 55) \
    LINE_CHECKERBOARD(_w_8) \
    ROOMS_AROUND(_w_8, _r_4, _r_1) \
     \
    CREATE_LINE(_w_9, 0.2, -0.4, 0.2, 0.4) \
    LINE_COLOR(_w_9, 13, 74, 55) \
    LINE_CHECKERBOARD(_w_9) \
    ROOMS_AROUND(_w_9, _r_1, _r_4) \
     \
    CREATE_LINE(_w_10, -0.19996000000000003, -0.4, -0.19996000000000003, 0.4) \
    LINE_COLOR(_w_10, 13, 48, 74) \
    LINE_CHECKERBOARD(_w_10) \
    ROOMS_AROUND(_w_10, _r_1, _r_1) \
     \
    CREATE_LINE(_w_11, 0.19996000000000003, -0.4, 0.19996000000000003, 0.4) \
    LINE_COLOR(_w_11, 13, 48, 74) \
    LINE_CHECKERBOARD(_w_11) \
    ROOMS_AROUND(_w_11, _r_1, _r_1) \
     \
    CREATE_LINE(_w_12, 1.6, -0.4, 1.6, 1.6) \
    LINE_COLOR(_w_12, 13, 48, 74) \
    LINE_CHECKERBOARD(_w_12) \
    ROOMS_AROUND(_w_12, _r_4, _r_0) \
     \
    CREATE_LINE(_w_13, 2, -0.4, 2, 1.6) \
    LINE_COLOR(_w_13, 13, 48, 74) \
    LINE_CHECKERBOARD(_w_13) \
    ROOMS_AROUND(_w_13, _r_0, _r_4) \
     \
    CREATE_LINE(_w_14, 1.60004, -0.4, 1.60004, 1.6) \
    LINE_COLOR(_w_14, 13, 74, 55) \
    LINE_CHECKERBOARD(_w_14) \
    ROOMS_AROUND(_w_14, _r_4, _r_0) \
     \
    CREATE_LINE(_w_15, 1.9999600000000002, -0.4, 1.9999600000000002, 1.6) \
    LINE_COLOR(_w_15, 13, 74, 55) \
    LINE_CHECKERBOARD(_w_15) \
    ROOMS_AROUND(_w_15, _r_0, _r_0) \
     \
    CREATE_LINE(_w_16, 1.5, 2.3000000000000003, 2.1, 2.3000000000000003) \
    LINE_EMPTY(_w_16) \
    LINE_GHOST(_w_16) \
    ROOMS_AROUND(_w_16, _r_2, _r_4) \
     \
    CREATE_LINE(_w_17, 2.1, 2.3000000000000003, 2.1, 2.9000000000000004) \
    LINE_EMPTY(_w_17) \
    LINE_GHOST(_w_17) \
    ROOMS_AROUND(_w_17, _r_2, _r_4) \
     \
    CREATE_LINE(_w_18, 2.1, 2.9000000000000004, 1.5, 2.9000000000000004) \
    LINE_EMPTY(_w_18) \
    LINE_GHOST(_w_18) \
    ROOMS_AROUND(_w_18, _r_2, _r_4) \
     \
    CREATE_LINE(_w_19, 1.5, 2.9000000000000004, 1.5, 2.3000000000000003) \
    LINE_EMPTY(_w_19) \
    LINE_GHOST(_w_19) \
    ROOMS_AROUND(_w_19, _r_2, _r_4) \
     \
    CREATE_LINE(_w_20, -0.30000000000000004, -1.3, 0.30000000000000004, -1.3) \
    LINE_EMPTY(_w_20) \
    LINE_GHOST(_w_20) \
    ROOMS_AROUND(_w_20, _r_3, _r_4) \
     \
    CREATE_LINE(_w_21, 0.30000000000000004, -1.3, 0.30000000000000004, -0.7000000000000001) \
    LINE_EMPTY(_w_21) \
    LINE_GHOST(_w_21) \
    ROOMS_AROUND(_w_21, _r_3, _r_4) \
     \
    CREATE_LINE(_w_22, 0.30000000000000004, -0.7000000000000001, -0.30000000000000004, -0.7000000000000001) \
    LINE_EMPTY(_w_22) \
    LINE_GHOST(_w_22) \
    ROOMS_AROUND(_w_22, _r_3, _r_4) \
     \
    CREATE_LINE(_w_23, -0.30000000000000004, -0.7000000000000001, -0.30000000000000004, -1.3) \
    LINE_EMPTY(_w_23) \
    LINE_GHOST(_w_23) \
    ROOMS_AROUND(_w_23, _r_3, _r_4) \
     \
    LINE_TELEPORT(_w_0, _w_6) \
     \
    LINE_TELEPORT(_w_1, _w_7) \
     \
    LINE_TELEPORT(_w_2, _w_4) \
     \
    LINE_TELEPORT(_w_3, _w_5) \
     \
    LINE_TELEPORT(_w_4, _w_2) \
     \
    LINE_TELEPORT(_w_5, _w_3) \
     \
    LINE_TELEPORT(_w_6, _w_0) \
     \
    LINE_TELEPORT(_w_7, _w_1) \
     \
    lines.lines[0] = _w_0; \
    lines.lines[1] = _w_1; \
    lines.lines[2] = _w_2; \
    lines.lines[3] = _w_3; \
    lines.lines[4] = _w_4; \
    lines.lines[5] = _w_5; \
    lines.lines[6] = _w_6; \
    lines.lines[7] = _w_7; \
    lines.lines[8] = _w_8; \
    lines.lines[9] = _w_9; \
    lines.lines[10] = _w_10; \
    lines.lines[11] = _w_11; \
    lines.lines[12] = _w_12; \
    lines.lines[13] = _w_13; \
    lines.lines[14] = _w_14; \
    lines.lines[15] = _w_15; \
    lines.lines[16] = _w_16; \
    lines.lines[17] = _w_17; \
    lines.lines[18] = _w_18; \
    lines.lines[19] = _w_19; \
    lines.lines[20] = _w_20; \
    lines.lines[21] = _w_21; \
    lines.lines[22] = _w_22; \
    lines.lines[23] = _w_23; \

#define LEVEL_5 \
    world.n_rooms = 0; \
    world.rooms = (Room**)malloc(sizeof(Room*) * world.n_rooms); \
    world.player_position = Vec2D_new(0.5, 1.5); \
    world.player_angle = -1.5707963267948966; \
    Color bg = Color_new(128, 128, 128); \
    Lines lines; \
    lines.length = 3; \
    lines.lines = (Line2D*) malloc(sizeof(Line2D) * lines.length); \
     \
    CREATE_LINE(_w_0, 0, 0, 1, 0) \
    LINE_COLOR(_w_0, 53, 92, 50) \
    LINE_CHECKERBOARD(_w_0) \
     \
    CREATE_LINE(_w_1, 0.25, 0.01, 0.75, 0.01) \
    LINE_IMAGE(_w_1, "../resources/bone.png",0.5,0.5) \
     \
    CREATE_LINE(_w_2, 0, 0, 0, 1) \
    LINE_COLOR(_w_2, 31, 110, 120) \
    LINE_BOUNCE(_w_2) \
     \
    lines.lines[0] = _w_0; \
    lines.lines[1] = _w_1; \
    lines.lines[2] = _w_2; \

#define LEVEL_6 \
    world.n_rooms = 0; \
    world.rooms = (Room**)malloc(sizeof(Room*) * world.n_rooms); \
    world.player_position = Vec2D_new(0.5, 1.5); \
    world.player_angle = -1.5707963267948966; \
    Color bg = Color_new(128, 128, 128); \
    Lines lines; \
    lines.length = 4; \
    lines.lines = (Line2D*) malloc(sizeof(Line2D) * lines.length); \
     \
    CREATE_LINE(_w_0, 0, 0, 1, 0) \
    LINE_COLOR(_w_0, 53, 92, 50) \
    LINE_CHECKERBOARD(_w_0) \
     \
    CREATE_LINE(_w_1, 0.25, 0.01, 0.75, 0.01) \
    LINE_IMAGE(_w_1, "../resources/bone.png",0.5,0.5) \
     \
    CREATE_LINE(_w_2, 0, 0, 0, 0.75) \
    LINE_COLOR(_w_2, 31, 110, 120) \
    LINE_BOUNCE(_w_2) \
     \
    CREATE_LINE(_w_3, 1, 0, 1, 0.75) \
    LINE_COLOR(_w_3, 208, 121, 39) \
    LINE_BOUNCE(_w_3) \
     \
    lines.lines[0] = _w_0; \
    lines.lines[1] = _w_1; \
    lines.lines[2] = _w_2; \
    lines.lines[3] = _w_3; \

#define LEVEL_7 \
    world.n_rooms = 0; \
    world.rooms = (Room**)malloc(sizeof(Room*) * world.n_rooms); \
    world.player_position = Vec2D_new(0.5, 0.75); \
    world.player_angle = -0.5235987755982988; \
    Color bg = Color_new(128, 128, 128); \
    Lines lines; \
    lines.length = 6; \
    lines.lines = (Line2D*) malloc(sizeof(Line2D) * lines.length); \
     \
    CREATE_LINE(_w_0, 0, 0, 1.5, 0) \
    LINE_COLOR(_w_0, 53, 92, 50) \
    LINE_CHECKERBOARD(_w_0) \
     \
    CREATE_LINE(_w_1, 0.25, 0.01, 0.75, 0.01) \
    LINE_IMAGE(_w_1, "../resources/bone.png",0.5,0.5) \
     \
    CREATE_LINE(_w_2, 0, 1, 1.5, 1) \
    LINE_COLOR(_w_2, 50, 92, 87) \
    LINE_CHECKERBOARD(_w_2) \
     \
    CREATE_LINE(_w_3, 0.75, 0.99, 1.25, 0.99) \
    LINE_IMAGE(_w_3, "../resources/flower.png",0.5,0.5) \
     \
    CREATE_LINE(_w_4, 0, 0, 0, 1) \
    LINE_COLOR(_w_4, 31, 110, 120) \
     \
    CREATE_LINE(_w_5, 1.5, 0, 1.5, 1) \
    LINE_COLOR(_w_5, 208, 121, 39) \
     \
    LINE_TELEPORT(_w_4, _w_5) \
     \
    LINE_TELEPORT(_w_5, _w_4) \
     \
    lines.lines[0] = _w_0; \
    lines.lines[1] = _w_1; \
    lines.lines[2] = _w_2; \
    lines.lines[3] = _w_3; \
    lines.lines[4] = _w_4; \
    lines.lines[5] = _w_5; \

#define LEVEL_BOUNCE \
    world.n_rooms = 1; \
    world.rooms = (Room**)malloc(sizeof(Room*) * world.n_rooms); \
    CREATE_ROOM(_r_0, -2147483648, -2147483648, 4294967296, 4294967296) \
    ROOM_COLOR(_r_0, 87, 87, 87) \
    world.rooms[0] = &_r_0; \
    world.player_position = Vec2D_new(0, -1); \
    world.player_angle = 0; \
    Color bg = Color_new(99, 99, 99); \
    Lines lines; \
    lines.length = 2; \
    lines.lines = (Line2D*) malloc(sizeof(Line2D) * lines.length); \
     \
    CREATE_LINE(_w_0, -0.5, 0, 0.5, 0) \
    LINE_IMAGE(_w_0, "../resources/carton-detoure-s.png",1,1) \
    ROOMS_AROUND(_w_0, _r_0, _r_0) \
     \
    CREATE_LINE(_w_1, -0.5, -0.33, -0.5, -0.66) \
    LINE_COLOR(_w_1, 127, 210, 149) \
    LINE_BOUNCE(_w_1) \
    ROOMS_AROUND(_w_1, _r_0, _r_0) \
     \
    lines.lines[0] = _w_0; \
    lines.lines[1] = _w_1; \

#define LEVEL_CREDITS \
    world.n_rooms = 3; \
    world.rooms = (Room**)malloc(sizeof(Room*) * world.n_rooms); \
    CREATE_ROOM(_r_0, 5, 1, 1, 1) \
    ROOM_COLOR(_r_0, 163, 122, 127) \
    world.rooms[0] = &_r_0; \
    CREATE_ROOM(_r_1, 1, -2, 1, 1) \
    ROOM_COLOR(_r_1, 132, 146, 164) \
    world.rooms[1] = &_r_1; \
    CREATE_ROOM(_r_2, -2147483648, -2147483648, 4294967296, 4294967296) \
    ROOM_COLOR(_r_2, 84, 67, 87) \
    world.rooms[2] = &_r_2; \
    world.player_position = Vec2D_new(1.5, -5); \
    world.player_angle = 1.2566370614359172; \
    Color bg = Color_new(180, 183, 212); \
    Lines lines; \
    lines.length = 17; \
    lines.lines = (Line2D*) malloc(sizeof(Line2D) * lines.length); \
     \
    CREATE_LINE(_w_0, 0, 0, 0, 3) \
    LINE_COLOR(_w_0, 161, 132, 158) \
    LINE_CHECKERBOARD(_w_0) \
    ROOMS_AROUND(_w_0, _r_2, _r_2) \
     \
    CREATE_LINE(_w_1, 0, 3, 3, 3) \
    LINE_COLOR(_w_1, 180, 182, 159) \
    LINE_CHECKERBOARD(_w_1) \
    ROOMS_AROUND(_w_1, _r_2, _r_2) \
     \
    CREATE_LINE(_w_2, 0, 0, 1, 0) \
    LINE_COLOR(_w_2, 85, 80, 136) \
    LINE_GRADIENT(_w_2, 184,184,184) \
    ROOMS_AROUND(_w_2, _r_2, _r_2) \
     \
    CREATE_LINE(_w_3, 2, 0, 3, 0) \
    LINE_COLOR(_w_3, 184, 184, 184) \
    LINE_GRADIENT(_w_3, 85,80,136) \
    ROOMS_AROUND(_w_3, _r_2, _r_2) \
     \
    CREATE_LINE(_w_4, 3, 0, 3, 1) \
    LINE_COLOR(_w_4, 214, 111, 167) \
    LINE_GRADIENT(_w_4, 184,184,184) \
    ROOMS_AROUND(_w_4, _r_2, _r_2) \
     \
    CREATE_LINE(_w_5, 3, 2, 3, 3) \
    LINE_COLOR(_w_5, 184, 184, 184) \
    LINE_GRADIENT(_w_5, 214,111,167) \
    ROOMS_AROUND(_w_5, _r_2, _r_2) \
     \
    CREATE_LINE(_w_6, 1, 0, 2, 0) \
    ROOMS_AROUND(_w_6, _r_2, _r_2) \
     \
    CREATE_LINE(_w_7, 3, 2, 3, 1) \
    ROOMS_AROUND(_w_7, _r_2, _r_2) \
     \
    CREATE_LINE(_w_8, 4, 3, 7, 3) \
    LINE_IMAGE(_w_8, "../resources/flower.png",1,1) \
    LINE_GHOST(_w_8) \
    ROOMS_AROUND(_w_8, _r_2, _r_2) \
     \
    CREATE_LINE(_w_9, 5, 1, 6, 1) \
    LINE_EMPTY(_w_9) \
    LINE_GHOST(_w_9) \
    ROOMS_AROUND(_w_9, _r_0, _r_2) \
     \
    CREATE_LINE(_w_10, 6, 1, 6, 2) \
    LINE_EMPTY(_w_10) \
    LINE_GHOST(_w_10) \
    ROOMS_AROUND(_w_10, _r_0, _r_2) \
     \
    CREATE_LINE(_w_11, 6, 2, 5, 2) \
    LINE_EMPTY(_w_11) \
    LINE_GHOST(_w_11) \
    ROOMS_AROUND(_w_11, _r_0, _r_2) \
     \
    CREATE_LINE(_w_12, 5, 2, 5, 1) \
    LINE_EMPTY(_w_12) \
    LINE_GHOST(_w_12) \
    ROOMS_AROUND(_w_12, _r_0, _r_2) \
     \
    CREATE_LINE(_w_13, 1, -2, 2, -2) \
    LINE_EMPTY(_w_13) \
    LINE_GHOST(_w_13) \
    ROOMS_AROUND(_w_13, _r_1, _r_2) \
     \
    CREATE_LINE(_w_14, 2, -2, 2, -1) \
    LINE_EMPTY(_w_14) \
    LINE_GHOST(_w_14) \
    ROOMS_AROUND(_w_14, _r_1, _r_2) \
     \
    CREATE_LINE(_w_15, 2, -1, 1, -1) \
    LINE_EMPTY(_w_15) \
    LINE_GHOST(_w_15) \
    ROOMS_AROUND(_w_15, _r_1, _r_2) \
     \
    CREATE_LINE(_w_16, 1, -1, 1, -2) \
    LINE_EMPTY(_w_16) \
    LINE_GHOST(_w_16) \
    ROOMS_AROUND(_w_16, _r_1, _r_2) \
     \
    LINE_TELEPORT(_w_6, _w_7) \
     \
    LINE_TELEPORT(_w_7, _w_6) \
     \
    lines.lines[0] = _w_0; \
    lines.lines[1] = _w_1; \
    lines.lines[2] = _w_2; \
    lines.lines[3] = _w_3; \
    lines.lines[4] = _w_4; \
    lines.lines[5] = _w_5; \
    lines.lines[6] = _w_6; \
    lines.lines[7] = _w_7; \
    lines.lines[8] = _w_8; \
    lines.lines[9] = _w_9; \
    lines.lines[10] = _w_10; \
    lines.lines[11] = _w_11; \
    lines.lines[12] = _w_12; \
    lines.lines[13] = _w_13; \
    lines.lines[14] = _w_14; \
    lines.lines[15] = _w_15; \
    lines.lines[16] = _w_16; \

#define LEVEL_TRANS \
    world.n_rooms = 1; \
    world.rooms = (Room**)malloc(sizeof(Room*) * world.n_rooms); \
    CREATE_ROOM(_r_0, -2147483648, -2147483648, 4294967296, 4294967296) \
    ROOM_COLOR(_r_0, 87, 87, 87) \
    world.rooms[0] = &_r_0; \
    world.player_position = Vec2D_new(0, -1); \
    world.player_angle = 0; \
    Color bg = Color_new(99, 99, 99); \
    Lines lines; \
    lines.length = 2; \
    lines.lines = (Line2D*) malloc(sizeof(Line2D) * lines.length); \
     \
    CREATE_LINE(_w_0, -0.5, 0, 0.5, 0) \
    LINE_IMAGE(_w_0, "../resources/carton-detoure-s.png",1,1) \
    ROOMS_AROUND(_w_0, _r_0, _r_0) \
     \
    CREATE_LINE(_w_1, 0, -0.33, 0.5, -0.33) \
    LINE_COLOR(_w_1, 127, 210, 149) \
    LINE_TRANSPARENT(_w_1, 76.5) \
    LINE_GHOST(_w_1) \
    ROOMS_AROUND(_w_1, _r_0, _r_0) \
     \
    lines.lines[0] = _w_0; \
    lines.lines[1] = _w_1; \

