#ifndef EASYSDL_H_INCLUDED
#define EASYSDL_H_INCLUDED

///////////////////////// Definitions  //////////////////////////////////////////

#define EZ_NB_MAX_SON 10
#define EZ_NB_MAX_IMAGE 10

enum {EZ_RIEN,EZ_TOUCHE_ENFONCEE,EZ_TOUCHE_RELACHEE,EZ_SOURIS_MOUVEMENT,EZ_SOURIS_BOUTON_DROITE_ENFONCE,EZ_SOURIS_BOUTON_GAUCHE_ENFONCE,
      EZ_SOURIS_BOUTON_DROITE_RELACHE,EZ_SOURIS_BOUTON_GAUCHE_RELACHE,
      EZ_BOUTON_ENFONCE,EZ_BOUTON_RELACHE,EZ_CROIX_ENFONCEE,EZ_CROIX_RELACHEE,EZ_EXIT};

typedef struct{
    void* surface;
}EZ_image;

/// Fonction de graphique ///

// Ferme les extensions et la SDL
void EZ_destruction_fenetre();

//Initialise SDL ses extensions et crée une fenetre
int EZ_creation_fenetre(char* nom,unsigned int x, unsigned int y);

// Place un point de la couleur donnée
int EZ_trace_point(unsigned int x,unsigned int y,unsigned char rouge,unsigned char vert,unsigned char bleu,unsigned char transparence);

// trace un rectangle de la couleur donnée (x et y sont les coordonnées du coin supérieur gauche
int EZ_trace_rectangle_plein(unsigned int x,unsigned int y,unsigned int base,unsigned int hauteur,unsigned char rouge,unsigned char vert,unsigned char bleu,unsigned char transparence);

// trace le contour d'un rectangle de la couleur donnée (x et y sont les coordonnées du coin supérieur gauche
int EZ_trace_rectangle(unsigned int x,unsigned int y,unsigned int base,unsigned int hauteur,unsigned char rouge,unsigned char vert,unsigned char bleu,unsigned char transparence);



// trace un segment de couleur donné, la fonction peut utiliser antialisaing mais est plus lente
int EZ_trace_segment( int x,int y,int x2, int y2,unsigned char rouge,unsigned char vert,unsigned char bleu,unsigned char transparence);

// trace un triangle de couleur et de sommets donnés
int EZ_trace_triangle_plein(int x1,int y1,int x2,int y2,int x3,int y3,unsigned char rouge,unsigned char vert,unsigned char bleu,unsigned char transparence);

// Trace un cercle de centre et rayon la fonction peut utiliser antialisaing mais est plus lente
int EZ_trace_cercle(int x,int y,unsigned int rayon,unsigned char rouge,unsigned char vert,unsigned char bleu,unsigned char transparence);

// Trace un disque plein centre et rayon
int EZ_trace_disque(int x,int y,unsigned int rayon,unsigned char rouge,unsigned char vert,unsigned char bleu,unsigned char transparence);

// Trace un arc angulair de centre x et y, R1 rayon petit cercle R2 rayon grand cercle angle 1 et angle 2 puis couleur.
int EZ_trace_secteur(int x,int y,int r1,int r2,double a1,double a2,unsigned char rouge,unsigned char vert,unsigned char bleu,unsigned char transparence);

// trace une image de nom donné é la position donné
int EZ_trace_image(char* nom,unsigned int x,unsigned int y);

// trace une image (x et y sont les coordonnées du coin supérieur gauche avec une trasparence 0 transparent 255 opaque
int EZ_trace_image_transparence(char* nom,unsigned int x,unsigned int y,unsigned char transparence);

// Stocke une image de nom donné é la position donné
void EZ_stocke_image(int position,char* nom);

// Trace l'image stocké a la position donné.
void EZ_trace_image_stocke(int position,int x,int y);

// La méme mais avec la transparence
void EZ_trace_image_stocke_transparence(int position,int x,int y,unsigned char transparence);

// Mise é jour graphique
void EZ_mise_a_jour();


/// REGLER LES OTPTIONS DE TRANSPARENCE ET D ALLISING ///

// Active l'aliasing
void EZ_antialiasing_on();

// Désactive l'aliasing
void EZ_antialiasing_off();

// Test si l'aliasing est activée 1 si oui
int EZ_test_aliasing();

/// Fonction de texte ///

// trace un texte (x et y sont les coordonnées du coin supérieur gauche
int EZ_trace_texte(char* txt,char* nom_police,int taille, unsigned int x,unsigned int y,unsigned char rouge,unsigned char vert,unsigned char bleu,unsigned char transparence);

// trace un texte lissé sur une couleur de fond (x et y sont les coordonnées du coin supérieur gauche
int EZ_trace_texte_shaded(char* txt,char* nom_police,int taille, unsigned int x,unsigned int y,unsigned char rouge,unsigned char vert,unsigned char bleu,unsigned char rougef,unsigned char vertf,unsigned char bleuf);

// trace un texte (x et y sont les coordonnées du coin supérieur gauche
int EZ_trace_texte_droite(char* txt,char* nom_police,int taille, unsigned int x,unsigned int y,unsigned char rouge,unsigned char vert,unsigned char bleu,unsigned char transparence);

// trace un texte lissé sur une couleur de fond (x et y sont les coordonnées du coin supérieur gauche
int EZ_trace_texte_shaded_droite(char* txt,char* nom_police,int taille, unsigned int x,unsigned int y,unsigned char rouge,unsigned char vert,unsigned char bleu,unsigned char rougef,unsigned char vertf,unsigned char bleuf);


/// Fonction de traitement sur l'image sauvegardé ///


 //Sauvegarde l'ecran
int EZ_sauvegarde_ecran();

// Récupére la couleur d'un pixel de la sauvegarde
int EZ_recupere_pixel(unsigned x,unsigned y,unsigned char *rouge,unsigned char *vert,unsigned char *bleu);

// Restore l'ecran sauvegardé préalablement
int EZ_restoration_ecran();

// Recupére les dimensions de l'image
void EZ_recupere_dimension(int *x,int* y);


///Fonction musicale ///


// Charge le son "nom" et le place é la position donnee
void EZ_stocke_son(int position,char* nom);

// joue le son un nombre nb de fois.
void EZ_joue_son(int position,int nb);

// Joue de la musique un certain nombre de fois.
int EZ_musique_on(char* nom,int repetition);

// fin de la musique
void EZ_musique_off();

// Verifie musique verifie si la musique joue 1 (0 sinon)
int EZ_verifie_musique();

/// Fonction d evenement ///

// Donne le type d'un evenement
int EZ_recupere_evenement();

// Donne le type d'un evenement avec une limite de temps
int EZ_recupere_evenement_temps_limite(int temps);

// Donne le type de l'événement dans le buffer (non bloquant)
int EZ_recupere_evenement_continu();

//donne la position de la souris en x
int EZ_souris_x();

//donne la position de la souris en y
int EZ_souris_y();

// Donne la touche appuyée
int EZ_touche();

// Attendre un certain temps
void EZ_attendre(unsigned int temps);

//Attendre temps qu'une touche ou exit n'est pas enfoncée
int EZ_attendre_touche();

//Attendre temps qu'une touche ou un click ou exit n'est pas enfoncée si Exit alors retourn 0;
int EZ_attendre_action();

// Vide le buffer evenement
void EZ_vide_buffer();

/// Joystick  ///

// Donne le bouton du joystick qui a recu l'action
int EZ_bouton();

// Donne direction croix en degre mesure entre 0 et 360 (-1 si pas de direction ou -2 pas d'action de la croix)
int EZ_direction_croix();


/// Gestion des images ///

// initialise une EZ_image;
EZ_image* EZ_creation_image(int largeur,int hauteur);

// destruction d une EZ_image
void EZ_destruction_image(EZ_image * image);

// donne les dimensions de l'image
void EZ_donne_dimension_image(EZ_image * image,int* largeur,int * hauteur);

//charge une image
EZ_image* EZ_charge_image(char* nom);

// retourne la couleur en RGB
void EZ_recupere_rvb_image(EZ_image* image,int x,int y,unsigned char* r,unsigned char* v,unsigned char* b);

// colorie un pixel
void EZ_colorie_rvb_image(EZ_image* image,int x,int y,unsigned char r,unsigned char v,unsigned char b);

// Sauvegarde une image en format ppm P3
void EZ_sauvegarde_EZ_image_P3(EZ_image* image,char* nom);

// Sauvegarde une image en format BMP
void EZ_sauvegarde_EZ_image_BMP(EZ_image* image,char* nom);

// trace une EZ_image (x et y sont les coordonnées du coin supérieur gauche avec une trasparence 0 transparent 255 opaque
int EZ_trace_EZ_image_transparence(EZ_image* image,unsigned int x,unsigned int y,unsigned char transparence);

// colorie un pixel avec la transparence t
void EZ_colorie_rvb_image_transparence(EZ_image* image,int x,int y,unsigned char r,unsigned char v,unsigned char b,unsigned char t);

// retourne la couleur en RGBA
void EZ_recupere_rvb_image_transparence(EZ_image* image,int x,int y,unsigned char* r,unsigned char* v,unsigned char* b,unsigned char* t);

// Comme la fonction EZ_trace_image sauf que l'on donne l'image déjé chargée
int EZ_trace_EZ_image(EZ_image* image,int x,int y);

// retourne l'image transformée avec une rotation et un zoom
EZ_image* EZ_transforme_EZ_image(EZ_image* image,double angle,double zoom);

#endif // EASYSDL_H_INCLUDED
