#ifndef FICTIONAL_COUSCOUS_ISN_WORLD_H
#define FICTIONAL_COUSCOUS_ISN_WORLD_H

struct Position {
	double x;
	double y;
};
typedef struct Position Position;

struct World {
	Position player_position;
};
typedef struct World World;

#endif //FICTIONAL_COUSCOUS_ISN_WORLD_H
