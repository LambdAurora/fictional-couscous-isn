#include "room.h"
#include "../world/world.h"


Room Room_new(double x, double y, double width, double height) {
    Room res;
    res.color.red = 255;
    res.color.green = 255;
    res.color.blue = 255;
    res.x = x;
    res.y = y;
    res.width = width;
    res.height = height;
    return res;
}

Room* find_current_room(const World* world) {
    size_t n;
    double x = world->player_position.x;
    double y = world->player_position.y;
    for (n = 0; n < world->n_rooms; n++) {
        Room* room = world->rooms[n];
        if (x >= room->x && x <= room->x + room->width && y >= room->y && y <= room->y + room->height) return room;
    }
    return NULL;
}
