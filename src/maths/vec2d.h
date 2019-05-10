#ifndef FICTIONAL_COUSCOUS_VEC2D_H
#define FICTIONAL_COUSCOUS_VEC2D_H

#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "double.h"

/*!
 * Représente un vecteur 2D.
 */
struct Vec2D {
    double x;
    double y;
};
typedef struct Vec2D Vec2D;

/*!
 * Créer un nouveau vecteur à partir des coordonnées données.
 *
 * @param x Coordonée en X du vecteur.
 * @param y Coordonée en Y du vecteur.
 * @return Une copie du nouveau vecteur créé.
 */
Vec2D Vec2D_new(double x, double y);

/*!
 * Calcule le produit scalaire entre deux vecteurs.
 *
 * @param a Vecteur a.
 * @param b Vecteur b.
 * @return Le produit scalaire entre les vecteurs a et b.
 */
double dot2D(const Vec2D* a, const Vec2D* b);

/*!
 * Normalise le vecteur.
 *
 * @param in Le vecteur donnée.
 * @return Le vecteur normalisé.
 */
Vec2D norm2D(const Vec2D* in);

/*!
 * Calcule la distance entre deux vecteurs a et b.
 *
 * @param a Pointer du vecteur a.
 * @param b Pointer du vecteur b.
 * @return La distance entre les deux vecteurs.
 */
double dist2D(const Vec2D* a, const Vec2D* b);

/*!
 * Donne la longueur d'un vecteur.
 *
 * @param a Pointer du vecteur dont on veut connaître la longueur.
 * @return La longueur du vecteur.
 */
double length2D(const Vec2D* a);

/*!
 * Soustracte deux vecteurs.
 *
 * @param Premier vecteur.
 * @param Deuxième vecteur.
 * @return Résultat de la soustraction des vecteurs.
 */
Vec2D Vec2D_sub(const Vec2D* a, const Vec2D* b);

/*!
 * Additionne deux vecteurs.
 *
 * @param a Premier vecteur.
 * @param b Deuxième vecteur.
 * @return Résultat de la somme des vecteurs.
 */
Vec2D Vec2D_sum(const Vec2D* a, const Vec2D* b);

Vec2D Vec2D_mult(const Vec2D* a, double by);

/*!
 * Vérifie que deux vecteurs sont égaux.
 *
 * @param a Premier vecteur.
 * @param b Deuxième vecteur.
 * @return Vrai si les deux vecteurs sont égaux, sinon faux.
 */
bool Vec2D_eq(const Vec2D* a, const Vec2D* b);

/*!
 * Créer le vecteur normal au vecteur donné.
 *
 * @param vec Le vecteur donné.
 * @return Le vecteur normal.
 */
Vec2D Vec2D_normal(const Vec2D* vec);

// TODO: doc
Vec2D Vec2D_rotate(const Vec2D* vec, double angle);

#endif //FICTIONAL_COUSCOUS_VEC2D_H
