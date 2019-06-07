#ifndef ISN_LOGO_WAGNER_H
#define ISN_LOGO_WAGNER_H

#include <stdbool.h>
// Dimensions de la fenêtre
#define WAGNER_WIDTH 800
#define WAGNER_HEIGHT 600

// Le nombre de millisecondes à attendre avant de mettre à jour les calculs.
#define WAGNER_CLOCK_SPEED 50
// Le nombre de couleurs maximum, représente en même temps le nombre maximum de colonnes.
#define WAGNER_COLORS_MAX 57
// Représente le nombre de traînées de caractère maximum
#define WAGNER_TRAILS_MAX 57
// La police utilisée, venant de Google: https://fonts.google.com/specimen/Roboto
#define WAGNER_FONT_NAME "../resources/DF-font.ttf"
// Dimensions (maximum) des caractères
#define WAGNER_CHAR_HEIGHT 18
#define WAGNER_CHAR_WIDTH 14

// Où commence le "ISN" écrit en caractères.
#define WAGNER_LOGO_START_X 13
#define WAGNER_LOGO_START_Y 11

#define WAGNER_CLOCKS_PER_MS (CLOCKS_PER_SEC / 1000)

// Structure caractérisant une couleur RGB.
struct wagner_Color
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};

// Structure caractérisant une trainée de 5 caractères.
struct wagner_Trail
{
    // Est-elle active?
    bool active;
    // Position de départ X.
    unsigned int x;
    // Position de départ Y.
    int y;
    // Caractères.
    char chars[5];
};

// On créé des types pour ces structures
typedef struct wagner_Trail w_Trail_t;
typedef struct wagner_Color w_Color_t;

// Prend un caractère aléatoire dans: 0123456789ABCDEF
char wagner_pick_char();

// Fonction de dessin.
void wagner_draw();

// Fonction de mis à jour.
void wagner_update();

// Fonction de lancement, si tout va bien: retourne 0.
int wagner_logo();

#endif //ISN_LOGO_WAGNER_H
