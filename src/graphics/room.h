#ifndef FICTIONAL_COUSCOUS_ROOM_H
#define FICTIONAL_COUSCOUS_ROOM_H

#include "color.h"
#include "../base.h"

struct Room {
  Color color;
  double x;
  double y;
  double width;
  double height;
};
typedef struct Room Room;

Room Room_new(double x, double y, double width, double height);
Room* find_current_room(const struct World* world);

#endif // FICTIONAL_COUSCOUS_ROOM_H
