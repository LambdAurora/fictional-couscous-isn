#include "game.h"
#include "easysdl.h"

void init_game(Game* game, const int width, const int height) {
    game->width = width;
    game->height = height;
    game->top_mode = false;
    game->zoom = 24;
}

uint32_t to_screen_coord(Game* game, double coordinate) {
    return (uint32_t) (256 + coordinate * game->zoom);
}

Vec2D get_last_point(Line2D* line) {
    Vec2D vec;
    vec.x = line->pos.x + line->vec.x * line->length;
    vec.y = line->pos.y + line->vec.y * line->length;
    return vec;
}

void render_top_mode(Game* g, World* world) {
    size_t layer_i;
    // On dessine chaque couche.
    for (layer_i = 0; layer_i < world->n_layers; layer_i++) {
        Layer layer = world->layers[layer_i];

        // On dessine chaque salle
        size_t room_i;
        for (room_i = 0; room_i < world->n_rooms; room_i++) {
            Room* room = world->rooms[room_i];
            EZ_trace_rectangle_plein(to_screen_coord(g, room->x), to_screen_coord(g, room->y), room->width * g->zoom, room->height * g->zoom, room->color.red, room->color.green, room->color.blue, 255);
        }

        size_t wall_i;
        // On dessine chaque mur.
        for (wall_i = 0; wall_i < layer.walls.length; wall_i++) {
            Line2D wall = layer.walls.lines[wall_i];
            Vec2D last = get_last_point(&wall);
            uint8_t alpha = 255;
            if (wall.type == TRANSPARENT_LINE)
                alpha = wall.data == NULL ? 128 : (uint8_t)(*((double*) wall.data) * 255);
            EZ_trace_segment(to_screen_coord(g, wall.pos.x), to_screen_coord(g, wall.pos.y), to_screen_coord(g, last.x), to_screen_coord(g, last.y), wall.color.red, wall.color.green, wall.color.blue, alpha);
        }
    }
    // On dessine le joueur.
    EZ_trace_rectangle_plein(to_screen_coord(g, world->player_position.x) - 1, to_screen_coord(g, world->player_position.y) - 1, 2, 2, 0, 0, 0, 255);
}
