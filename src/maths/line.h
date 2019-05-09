#ifndef FICTIONAL_COUSCOUS_GEOMETRY_H
#define FICTIONAL_COUSCOUS_GEOMETRY_H

#include "../base.h"
#include "double.h"
#include "vec2d.h"
#include "../graphics/color.h"
#include "../graphics/room.h"

/*!
 * Représente le type de mur.
 */
enum LINE_TYPE {
    NORMAL_LINE,
    BOUNCE_LINE,
    TELEPORT_LINE,
    TRANSPARENT_LINE,
    GHOST_LINE
};
typedef enum LINE_TYPE LINE_TYPE;

/*!
 * Représente une ligne 2D pouvant être un mur par exemple.
 * On y retrouve la position, sa longueur, son type, sa couleur et quelques données supplémentaires.
 */
struct Line2D {
    Vec2D pos; // Position de la ligne.
    Vec2D vec; // should be normalized
    double length; // Longueur de la ligne.
    LINE_TYPE type; // Type de la ligne.
    Color color; // Couleur de la ligne.
    void* data; // Données supplémentaires de la ligne.
    texture_t texture; // Texture de la ligne
    void* texture_data; // Données supplémentaires de la texture
    Room* room_left;
    Room* room_right;
};
typedef struct Line2D Line2D;

/*!
 * Représente une liste de ligne.
 */
struct Lines {
    Line2D* lines;
    size_t length;
};
typedef struct Lines Lines;

/*!
 * Créer une nouvelle ligne à partir de 2 points.
 *
 * @param from Point de départ de la ligne.
 * @param to Point d'arrivée de la ligne.
 * @return Une copie de la nouvelle ligne.
 */
Line2D Line2D_new(const Vec2D* from, const Vec2D* to);

#endif// FICTIONAL_COUSCOUS_GEOMETRY_H
