#ifndef FICTIONAL_COUSCOUS_COLOR_H
#define FICTIONAL_COUSCOUS_COLOR_H

#include <stdlib.h>
#include <inttypes.h>

/*!
 * Représente une couleur.
 */
struct Color {
  uint8_t red; // Composante rouge de la couleur.
  uint8_t green; // Composante verte de la couleur.
  uint8_t blue; // Composante bleue de la couleur.
};
typedef struct Color Color;

/*!
 * Mixe une composante d'une couleur avec une autre.
 *
 * @param a Composante de la première couleur.
 * @param b Composante de la deuxième couleur.
 * @param ratio Taux de mixage.
 * @return Composante mixée.
 */
uint8_t mix(uint8_t a, uint8_t b, double ratio);

/*!
 * Créer une nouvelle couleur à partir de ses trois composantes.
 *
 * @param red Composante rouge de la couleur.
 * @param green Composante verte de la couleur.
 * @param blue Composante bleue de la couleur.
 * @return La nouvelle couleur.
 */
Color Color_new(uint8_t red, uint8_t green, uint8_t blue);

#endif// FICTIONAL_COUSCOUS_COLOR_H
