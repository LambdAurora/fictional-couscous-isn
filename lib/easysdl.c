#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_rotozoom.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <time.h>
#include "easysdl.h"
#include "math.h"

// On d�finit ici des fonctions de haut niveau permettant de simplifier l'utilisation de la SDL
//


// EZ_fenetre est une variable externe.
SDL_Window *EZ_fenetre = NULL;
SDL_Renderer *EZ_rendu = NULL;

SDL_Event EZ_evenement;
Mix_Music *EZ_musique = NULL;
Mix_Chunk *EZ_son[EZ_NB_MAX_SON];
SDL_Surface *EZ_sauvegarde;
SDL_Texture *EZ_tableau_image[EZ_NB_MAX_IMAGE];
SDL_Joystick *EZ_joystick;
TTF_Font *EZ_police;
unsigned char EZ_aliasing = 0;

static unsigned int EZ_mouse_x = 0;
static unsigned int EZ_mouse_y = 0;

void EZ_destruction_son();

void EZ_initialisation_son();

void EZ_initialisation_tab_image();

void EZ_destruction_tab_image();

void EZ_initialisation_joystick();

void EZ_destruction_joystick();

void EZ_destruction_police();

int EZ_charge_police(char *nom_police, int taille);

// Ferme les extensions et la SDL
void EZ_destruction_fenetre()
{
	extern SDL_Window *EZ_fenetre;
	extern SDL_Renderer *EZ_rendu;
	extern SDL_Surface *EZ_sauvegarde;
	extern Mix_Music *EZ_musique;
	EZ_musique_off();
	EZ_destruction_son();
	EZ_destruction_tab_image();
	EZ_destruction_joystick();
	EZ_destruction_police();
	SDL_DestroyRenderer(EZ_rendu);


	SDL_DestroyWindow(EZ_fenetre);
	SDL_FreeSurface(EZ_sauvegarde);

	EZ_rendu = NULL;
	EZ_fenetre = NULL;
	EZ_sauvegarde = NULL;
	EZ_musique = NULL;
	Mix_CloseAudio();
	TTF_Quit();
	SDL_Quit();
}

//Initialise SDL ses extensions et cr�e une fenetre
int EZ_creation_fenetre(char *nom, unsigned int x, unsigned int y)
{
	extern SDL_Window *EZ_fenetre;
	extern SDL_Renderer *EZ_rendu;
	extern TTF_Font *EZ_police;
	extern int lisage;
	extern unsigned char EZ_aliasing;
	if (EZ_fenetre) {
		EZ_destruction_fenetre();
	}
	// Ouverture de le SDL et de ses extensions.
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0) {
		fprintf(stderr, "�chec de l'initialisation de la SDL (%s)\n", SDL_GetError());
		return 0;
	}

	if (TTF_Init() == -1) {
		fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
		return 0;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0) //Initialisation de l'API Mixer
	{
		fprintf(stderr, "Erreur d'open audio %s", Mix_GetError());
		return 0;
	}
	EZ_police = NULL;
	EZ_charge_police("", 1);
	Mix_AllocateChannels(EZ_NB_MAX_SON);
	EZ_initialisation_son();
	EZ_initialisation_tab_image();
	EZ_initialisation_joystick();
	EZ_fenetre = SDL_CreateWindow(nom, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, x, y, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_UTILITY);
	EZ_rendu = SDL_CreateRenderer(EZ_fenetre, -1, SDL_RENDERER_ACCELERATED);
	printf("%s\n", SDL_GetError());
	SDL_SetRenderDrawColor(EZ_rendu, 255, 255, 255, 255);
	SDL_RenderClear(EZ_rendu);
	SDL_RenderPresent(EZ_rendu);
	SDL_SetRenderDrawColor(EZ_rendu, 0, 0, 0, 255);
	EZ_aliasing = 0;


	return 1;
}

/// REGLER LES OTPTIONS DE TRANSPARENCE ET D ALLISING ///

// Active l'aliasing
void EZ_antialiasing_on()
{
	extern unsigned char EZ_aliasing;
	EZ_aliasing = 1;
}

// D�sactive l'aliasing
void EZ_antialiasing_off()
{
	extern unsigned char EZ_aliasing;
	EZ_aliasing = 0;
}

// Test si l'aliasing est activ�e 1 si oui
int EZ_test_aliasing()
{
	extern unsigned char EZ_aliasing;
	return EZ_aliasing;
}

/// FONCTIONS DE PAUSE ///

void EZ_attendre(unsigned int temps)
{
	SDL_Delay(temps);
}

//Attendre temps qu'une touche ou exit n'est pas enfonc�e si exit alors retourne 0
int EZ_attendre_touche()
{
	int EZ_evenement;
	do {
		EZ_evenement = EZ_recupere_evenement();
	} while (EZ_evenement != EZ_TOUCHE_ENFONCEE && EZ_evenement != EZ_EXIT);
	if (EZ_evenement == EZ_EXIT)return 0;
	return 1;
}

//Attendre temps qu'une touche ou un click ou exit n'est pas enfonc�e si Exit alors retourn 0;
int EZ_attendre_action()
{
	int EZ_evenement;
	do {
		EZ_evenement = EZ_recupere_evenement();
	} while (EZ_evenement != EZ_TOUCHE_ENFONCEE && EZ_evenement != EZ_EXIT
			 && EZ_evenement != EZ_SOURIS_BOUTON_DROITE_ENFONCE
			 && EZ_evenement != EZ_SOURIS_BOUTON_GAUCHE_ENFONCE);
	if (EZ_evenement == EZ_EXIT)return 0;
	return 1;
}


/// FONCTION GRAPHIQUE ///

// Place un point de la couleur donn�e
int EZ_trace_point(unsigned int x, unsigned int y, unsigned char rouge, unsigned char vert, unsigned char bleu, unsigned char transparence)
{
	extern SDL_Renderer *EZ_rendu;
	if (!EZ_rendu)            // Si fentre ou EZ_rendu n'existe pas on arrete
		return 0;
	pixelRGBA(EZ_rendu, x, y, (Uint8) rouge, (Uint8) vert, (Uint8) bleu, (Uint8) transparence);
	return 1;
}

// trace un rectangle de la couleur donn�e (x et y sont les coordonn�es du coin sup�rieur gauche
int EZ_trace_rectangle_plein(unsigned int x, unsigned int y, unsigned int base, unsigned int hauteur, unsigned char rouge, unsigned char vert, unsigned char bleu,
							 unsigned char transparence)
{
	extern SDL_Renderer *EZ_rendu;
	if (!EZ_rendu)            // Si fentre ou EZ_rendu n'existe pas on arrete
		return 0;
	boxRGBA(EZ_rendu, x, y, x + base, y + hauteur, (Uint8) rouge, (Uint8) vert, (Uint8) bleu, (Uint8) transparence);
	return 1;
}

// trace le contour d'un rectangle de la couleur donn�e (x et y sont les coordonn�es du coin sup�rieur gauche
int
EZ_trace_rectangle(unsigned int x, unsigned int y, unsigned int base, unsigned int hauteur, unsigned char rouge, unsigned char vert, unsigned char bleu, unsigned char transparence)
{
	extern SDL_Renderer *EZ_rendu;
	if (!EZ_rendu)            // Si fentre ou EZ_rendu n'existe pas on arrete
		return 0;
	rectangleRGBA(EZ_rendu, x, y, x + base, y + hauteur, (Uint8) rouge, (Uint8) vert, (Uint8) bleu, (Uint8) transparence);
	return 1;
}

// Trace un disque plein centre et rayon
int EZ_trace_disque(int x, int y, unsigned int rayon, unsigned char rouge, unsigned char vert, unsigned char bleu, unsigned char transparence)
{
	extern SDL_Renderer *EZ_rendu;
	filledCircleRGBA(EZ_rendu, x, y, rayon, (Uint8) rouge, (Uint8) vert, (Uint8) bleu, (Uint8) transparence);
	return 1;
}

// Trace un cercle de centre et rayon
int EZ_trace_cercle(int x, int y, unsigned int rayon, unsigned char rouge, unsigned char vert, unsigned char bleu, unsigned char transparence)
{
	extern SDL_Renderer *EZ_rendu;
	extern unsigned char EZ_aliasing;
	if (EZ_aliasing)
		return aacircleRGBA(EZ_rendu, x, y, rayon, (Uint8) rouge, (Uint8) vert, (Uint8) bleu, (Uint8) transparence);
	return circleRGBA(EZ_rendu, x, y, rayon, (Uint8) rouge, (Uint8) vert, (Uint8) bleu, (Uint8) transparence);
}

//Fonction auxilliaire de trace secteur
int EZ_trace_secteur_rec(int x, int y, int r1, int r2, double a1, double a2, unsigned char rouge, unsigned char vert, unsigned char bleu, unsigned char transparence, int signe)
{
	int i, mini, maxi, absmax, absmax2, absmin;
	double ta1 = tan(a1), ta2 = tan(a2);

	if (a1 <= M_PI / 2.0 && a2 <= M_PI / 2.0) {
		absmax = r2 * cos(a1);
		absmin = r1 * cos(a1);
		absmax2 = r2 * cos(a2);

		for (i = r1 * cos(a2); i <= absmax; i++) {
			mini = (i > absmin) ? i * ta1 : sqrt(r1 * r1 - i * i);
			maxi = (i < absmax2) ? i * ta2 : sqrt(r2 * r2 - i * i);
			if (mini > maxi)maxi = sqrt(r1 * r1 - i * i);
			EZ_trace_segment(x + i, y - signe * mini, x + i, y - signe * maxi, rouge, vert, bleu, transparence);
		}
	} else if (a1 >= M_PI / 2.0 && a2 >= M_PI / 2.0) {
		absmax = r1 * cos(a1);
		absmin = r1 * cos(a2);
		absmax2 = r2 * cos(a1);
		for (i = r2 * cos(a2); i <= absmax; i++) {
			mini = (i < absmin) ? i * ta2 : sqrt(r1 * r1 - i * i);
			maxi = (i > absmax2) ? i * ta1 : sqrt(r2 * r2 - i * i);
			if (mini > maxi)maxi = sqrt(r1 * r1 - i * i);
			EZ_trace_segment(x + i, y - signe * mini, x + i, y - signe * maxi, rouge, vert, bleu, transparence);
		}
	} else {
		EZ_trace_secteur_rec(x, y, r1, r2, a1, M_PI / 2.0, rouge, vert, bleu, transparence, signe);
		EZ_trace_secteur_rec(x, y, r1, r2, M_PI / 2.0, a2, rouge, vert, bleu, transparence, signe);
	}

	return 1;
}

// Trace un arc angulair de centre x et y, R1 rayon petit cercle R2 rayon grand cercle angle 1 et angle 2 puis couleur.
int EZ_trace_secteur(int x, int y, int r1, int r2, double a1, double a2, unsigned char rouge, unsigned char vert, unsigned char bleu, unsigned char transparence)
{
	double anglemin, anglemax;
	anglemin = a1 - floor(a1 / (2 * M_PI)) * 2 * M_PI;
	anglemax = a2 - floor(a2 / (2 * M_PI)) * 2 * M_PI;
	if (anglemin <= anglemax) {
		if (anglemin < M_PI) {
			if (anglemax <= M_PI)
				EZ_trace_secteur_rec(x, y, r1, r2, anglemin, anglemax, rouge, vert, bleu, transparence, 1);
			else {
				EZ_trace_secteur_rec(x, y, r1, r2, anglemin, M_PI, rouge, vert, bleu, transparence, 1);
				EZ_trace_secteur_rec(x, y, r1, r2, 2 * M_PI - anglemax, M_PI, rouge, vert, bleu, transparence, -1);
			}
		} else
			EZ_trace_secteur_rec(x, y, r1, r2, 2 * M_PI - anglemax, 2 * M_PI - anglemin, rouge, vert, bleu, transparence, -1);
	} else {
		if (anglemin <= M_PI) {
			EZ_trace_secteur_rec(x, y, r1, r2, anglemin, M_PI, rouge, vert, bleu, transparence, 1);
			EZ_trace_secteur_rec(x, y, r1, r2, 0, M_PI, rouge, vert, bleu, transparence, -1);
			EZ_trace_secteur_rec(x, y, r1, r2, 0, anglemax, rouge, vert, bleu, transparence, 1);
		} else {
			if (anglemax <= M_PI) {
				EZ_trace_secteur_rec(x, y, r1, r2, 0, 2 * M_PI - anglemin, rouge, vert, bleu, transparence, -1);
				EZ_trace_secteur_rec(x, y, r1, r2, 0, anglemax, rouge, vert, bleu, transparence, 1);
			} else {
				EZ_trace_secteur_rec(x, y, r1, r2, 0, 2 * M_PI - anglemin, rouge, vert, bleu, transparence, -1);
				EZ_trace_secteur_rec(x, y, r1, r2, 0, M_PI, rouge, vert, bleu, transparence, 1);
				EZ_trace_secteur_rec(x, y, r1, r2, 2 * M_PI - anglemax, M_PI, rouge, vert, bleu, transparence, -1);
			}
		}
	}
	return 1;
}


//Sauvegarde l'ecran
int EZ_sauvegarde_ecran()
{
	extern SDL_Window *EZ_fenetre;
	extern SDL_Surface *EZ_sauvegarde;
	extern SDL_Renderer *EZ_rendu;
	int x, y;
	SDL_GetWindowSize(EZ_fenetre, &x, &y);
	SDL_FreeSurface(EZ_sauvegarde);
	EZ_sauvegarde = SDL_CreateRGBSurface(0, x, y, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
	SDL_RenderReadPixels(EZ_rendu, NULL, SDL_PIXELFORMAT_ARGB8888, EZ_sauvegarde->pixels, EZ_sauvegarde->pitch);
	return 0;
}

// Restore l'ecran sauvegard� pr�alablement
int EZ_restoration_ecran()
{
	extern SDL_Surface *EZ_sauvegarde;
	extern SDL_Renderer *EZ_rendu;
	extern SDL_Window *EZ_fenetre;
	SDL_Texture *texture;
	texture = SDL_CreateTextureFromSurface(EZ_rendu, EZ_sauvegarde);
	SDL_RenderCopy(EZ_rendu, texture, NULL, NULL);
	SDL_DestroyTexture(texture);

	return 1;
}

// R�cup�re la couleur d'un pixel de la sauvegarde
int EZ_recupere_pixel(unsigned x, unsigned y, unsigned char *rouge, unsigned char *vert, unsigned char *bleu)
{
	extern SDL_Surface *EZ_sauvegarde;
	int nbOctetsParPixel = EZ_sauvegarde->format->BytesPerPixel;

	Uint32 *p = (Uint32 *) ((Uint8 *) EZ_sauvegarde->pixels + y * EZ_sauvegarde->pitch + x * nbOctetsParPixel);
	SDL_GetRGB(*(p), EZ_sauvegarde->format, rouge, vert, bleu);
	return 1;
}

// trace un segment de couleur donn�
int EZ_trace_segment(int x1, int y1, int x2, int y2, unsigned char rouge, unsigned char vert, unsigned char bleu, unsigned char transparence)
{
	extern SDL_Renderer *EZ_rendu;
	extern unsigned char EZ_aliasing;
	if (EZ_aliasing)
		return aalineRGBA(EZ_rendu, x1, y1, x2, y2, (Uint8) rouge, (Uint8) vert, (Uint8) bleu, (Uint8) transparence);
	return lineRGBA(EZ_rendu, x1, y1, x2, y2, (Uint8) rouge, (Uint8) vert, (Uint8) bleu, (Uint8) transparence);
}

// trace un triangle de couleur et de sommets donn�s
int EZ_trace_triangle_plein(int x1, int y1, int x2, int y2, int x3, int y3, unsigned char rouge, unsigned char vert, unsigned char bleu, unsigned char transparence)
{
	extern SDL_Renderer *EZ_rendu;
	return filledTrigonRGBA(EZ_rendu, x1, y1, x2, y2, x3, y3, (Uint8) rouge, (Uint8) vert, (Uint8) bleu, (Uint8) transparence);
}

//////////////////////////////// Fonction de texte  /////////////////////////////////


//Charge une police
int EZ_charge_police(char *nom_police, int taille)
{
	static char nom_memoire[100];
	static int longueur_memoire;
	extern TTF_Font *EZ_police;
	int i = 0, compare = 0;
	if (*nom_police == '\0') // Le nom est vide fait un reset du nom
	{
		nom_memoire[0] = '\0';
		return 1;
	}
	//regarde si la police n'est pas d�j� charg�e.
	while (i < 100 && nom_police[i] && nom_police[i] == nom_memoire[i])i++;
	if (i < 100 && i > 0 && !nom_police[i] && !nom_memoire[i])compare = 1;
	if (EZ_police != NULL && compare && taille == longueur_memoire)
		return 1;
	if (EZ_police != NULL)
		TTF_CloseFont(EZ_police);
	EZ_police = TTF_OpenFont(nom_police, taille);
	if (EZ_police == NULL) {
		fprintf(stderr, "Erreur d'initialisation de la police\n");
		return 0;
	}
	i = 0;
	while (i < 100 && (nom_memoire[i] = nom_police[i]))i++;
	longueur_memoire = taille;
	return 1;
}

//detruit la police
void EZ_destruction_police()
{
	extern TTF_Font *EZ_police;
	TTF_CloseFont(EZ_police);
	EZ_police = NULL;
}


// trace un texte (x et y sont les coordonn�es du coin sup�rieur gauche
int EZ_trace_texte(char *txt, char *nom_police, int taille, unsigned int x, unsigned int y, unsigned char rouge, unsigned char vert, unsigned char bleu, unsigned char transparence)
{
	extern SDL_Renderer *EZ_rendu;
	SDL_Rect rectangle;
	SDL_Color couleur = {rouge, vert, bleu};
	SDL_Surface *surface;
	extern TTF_Font *EZ_police;
	EZ_charge_police(nom_police, taille);
	if (EZ_police == NULL) {
		fprintf(stderr, "Erreur d'initialisation de la police\n");
		return 0;
	}

	surface = TTF_RenderText_Blended(EZ_police, txt, couleur);
	if (surface == NULL) {
		fprintf(stderr, "Erreur d'initialisation de la surface dans trace texte\n");
		return 0;
	}
	SDL_Texture *texture = SDL_CreateTextureFromSurface(EZ_rendu, surface);
	if (texture == NULL) {
		SDL_FreeSurface(surface);
		fprintf(stderr, "Erreur d'initialisation de la texture dans trace texte\n");
		return 0;
	}
	SDL_SetTextureAlphaMod(texture, transparence);
	SDL_QueryTexture(texture, NULL, NULL, &(rectangle.w), &(rectangle.h));


	rectangle.x = x;
	rectangle.y = y;
	SDL_RenderCopy(EZ_rendu, texture, NULL, &rectangle);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
	return 1;
}


// trace un texte liss� sur une couleur de fond (x et y sont les coordonn�es du coin sup�rieur gauche
int
EZ_trace_texte_shaded(char *txt, char *nom_police, int taille, unsigned int x, unsigned int y, unsigned char rouge, unsigned char vert, unsigned char bleu, unsigned char rougef,
					  unsigned char vertf, unsigned char bleuf)
{
	extern SDL_Renderer *EZ_rendu;
	SDL_Rect rectangle;
	SDL_Color couleur = {rouge, vert, bleu};
	SDL_Color couleur_fond = {rougef, vertf, bleuf};
	extern TTF_Font *EZ_police;
	EZ_charge_police(nom_police, taille);
	if (EZ_police == NULL) {
		fprintf(stderr, "Erreur d'initialisation de la police\n");
		return 0;
	}

	SDL_Surface *surface = TTF_RenderText_Shaded(EZ_police, txt, couleur, couleur_fond);
	if (surface == NULL) {
		fprintf(stderr, "Erreur d'initialisation de la surface dans texte shaded\n");
		return 0;
	}

	SDL_Texture *texture = SDL_CreateTextureFromSurface(EZ_rendu, surface);
	if (texture == NULL) {
		SDL_FreeSurface(surface);
		fprintf(stderr, "Erreur d'initialisation de la texture dans texte shaded\n");
		return 0;
	}
	SDL_QueryTexture(texture, NULL, NULL, &(rectangle.w), &(rectangle.h));


	rectangle.x = x;
	rectangle.y = y;

	SDL_RenderCopy(EZ_rendu, texture, NULL, &rectangle);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
	return 1;
}


// trace un texte (x et y sont les coordonn�es du coin sup�rieur gauche
int EZ_trace_texte_droite(char *txt, char *nom_police, int taille, unsigned int x, unsigned int y, unsigned char rouge, unsigned char vert, unsigned char bleu,
						  unsigned char transparence)
{
	extern SDL_Renderer *EZ_rendu;
	SDL_Rect rectangle;
	SDL_Color couleur = {rouge, vert, bleu};
	extern TTF_Font *EZ_police;
	EZ_charge_police(nom_police, taille);
	if (EZ_police == NULL) {
		fprintf(stderr, "Erreur d'initialisation de la police\n");
		return 0;
	}

	SDL_Surface *surface = TTF_RenderText_Blended(EZ_police, txt, couleur);
	if (surface == NULL) {
		fprintf(stderr, "Erreur d'initialisation de la surface dans texte droit\n");
		return 0;
	}

	SDL_Texture *texture = SDL_CreateTextureFromSurface(EZ_rendu, surface);
	if (texture == NULL) {
		SDL_FreeSurface(surface);
		fprintf(stderr, "Erreur d'initialisation de la texture\n");
		return 0;
	}
	SDL_SetTextureAlphaMod(texture, transparence);
	SDL_QueryTexture(texture, NULL, NULL, &(rectangle.w), &(rectangle.h));


	rectangle.x = x - rectangle.w;
	rectangle.y = y;

	SDL_RenderCopy(EZ_rendu, texture, NULL, &rectangle);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
	return 1;
}


// trace un texte liss� sur une couleur de fond (x et y sont les coordonn�es du coin sup�rieur gauche
int EZ_trace_texte_shaded_droite(char *txt, char *nom_police, int taille, unsigned int x, unsigned int y, unsigned char rouge, unsigned char vert, unsigned char bleu,
								 unsigned char rougef, unsigned char vertf, unsigned char bleuf)
{
	extern SDL_Renderer *EZ_rendu;
	SDL_Rect rectangle;
	SDL_Color couleur = {rouge, vert, bleu};
	SDL_Color couleur_fond = {rougef, vertf, bleuf};
	extern TTF_Font *EZ_police;
	EZ_charge_police(nom_police, taille);
	if (EZ_police == NULL) {
		fprintf(stderr, "Erreur d'initialisation de la police\n");
		return 0;
	}

	SDL_Surface *surface = TTF_RenderText_Shaded(EZ_police, txt, couleur, couleur_fond);
	if (surface == NULL) {
		fprintf(stderr, "Erreur d'initialisation de la police\n");
		return 0;
	}

	SDL_Texture *texture = SDL_CreateTextureFromSurface(EZ_rendu, surface);
	if (texture == NULL) {
		SDL_FreeSurface(surface);
		fprintf(stderr, "Erreur d'initialisation de la police\n");
		return 0;
	}
	SDL_QueryTexture(texture, NULL, NULL, &(rectangle.w), &(rectangle.h));


	rectangle.x = x - rectangle.w;
	rectangle.y = y;

	SDL_RenderCopy(EZ_rendu, texture, NULL, &rectangle);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
	return 1;
}

/////////////// Affichage des images /////////////////////////////

// trace une image (x et y sont les coordonn�es du coin sup�rieur gauche
int EZ_trace_image(char *nom, unsigned int x, unsigned int y)
{
	extern SDL_Renderer *EZ_rendu;
	SDL_Rect rectangle;
	SDL_Surface *surface;
	surface = IMG_Load(nom);
	if (surface == NULL) {
		fprintf(stderr, "Erreur de chargement de l'image\n");
		return 0;
	}

	SDL_Texture *texture = SDL_CreateTextureFromSurface(EZ_rendu, surface);
	if (texture == NULL) {
		SDL_FreeSurface(surface);
		fprintf(stderr, "Erreur d'initialisation de la texture\n");
		return 0;
	}
	SDL_QueryTexture(texture, NULL, NULL, &(rectangle.w), &(rectangle.h));

	rectangle.x = x;
	rectangle.y = y;

	SDL_RenderCopy(EZ_rendu, texture, NULL, &rectangle);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
	return 1;
}


// trace une image (x et y sont les coordonn�es du coin sup�rieur gauche avec une trasparence 0 transparent 255 opaque
int EZ_trace_image_transparence(char *nom, unsigned int x, unsigned int y, unsigned char transparence)
{
	extern SDL_Renderer *EZ_rendu;
	SDL_Rect rectangle;
	SDL_Surface *surface;
	surface = IMG_Load(nom);
	if (surface == NULL) {
		fprintf(stderr, "Erreur de chargement de l'image\n");
		return 0;
	}
	SDL_Texture *texture = SDL_CreateTextureFromSurface(EZ_rendu, surface);
	if (texture == NULL) {
		SDL_FreeSurface(surface);
		fprintf(stderr, "Erreur d'initialisation de la texture\n");
		return 0;
	}
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(texture, transparence);
	SDL_QueryTexture(texture, NULL, NULL, &(rectangle.w), &(rectangle.h));
	rectangle.x = x;
	rectangle.y = y;

	SDL_RenderCopy(EZ_rendu, texture, NULL, &rectangle);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
	return 1;
}


// Recup�re les dimensions de l'image
void EZ_recupere_dimension(int *x, int *y)
{
	extern SDL_Window *EZ_fenetre;
	SDL_GetWindowSize(EZ_fenetre, x, y);
}


void EZ_initialisation_tab_image()
{
	extern SDL_Texture *EZ_tableau_image[EZ_NB_MAX_IMAGE];
	int i;
	for (i = 0; i < EZ_NB_MAX_IMAGE; i++) {
		EZ_tableau_image[i] = NULL;
	}
}

void EZ_destruction_tab_image()
{
	extern SDL_Texture *EZ_tableau_image[EZ_NB_MAX_IMAGE];
	int i;
	for (i = 0; i < EZ_NB_MAX_IMAGE; i++) {
		SDL_DestroyTexture(EZ_tableau_image[i]);
		EZ_tableau_image[i] = NULL;
	}
}

void EZ_stocke_image(int position, char *nom)
{
	extern SDL_Texture *EZ_tableau_image[EZ_NB_MAX_IMAGE];
	extern SDL_Renderer *EZ_rendu;
	SDL_Surface *surface;

	SDL_DestroyTexture(EZ_tableau_image[position % EZ_NB_MAX_IMAGE]);
	EZ_tableau_image[position % EZ_NB_MAX_IMAGE] = NULL;

	surface = IMG_Load(nom);
	if (surface == NULL) {
		fprintf(stderr, "Erreur de chargement de l'image %s\n", nom);
		return;
	}
	EZ_tableau_image[position % EZ_NB_MAX_IMAGE] = SDL_CreateTextureFromSurface(EZ_rendu, surface);
	if (EZ_tableau_image[position % EZ_NB_MAX_IMAGE] == NULL) {
		SDL_FreeSurface(surface);
		fprintf(stderr, "Erreur d'initialisation de la texture %s\n", nom);
		return;
	}
	SDL_SetTextureBlendMode(EZ_tableau_image[position % EZ_NB_MAX_IMAGE], SDL_BLENDMODE_BLEND);
}

void EZ_trace_image_stocke(int position, int x, int y)
{
	extern SDL_Texture *EZ_tableau_image[EZ_NB_MAX_IMAGE];
	extern SDL_Renderer *EZ_rendu;
	SDL_Rect rectangle;

	SDL_QueryTexture(EZ_tableau_image[position % EZ_NB_MAX_IMAGE], NULL, NULL, &(rectangle.w), &(rectangle.h));

	rectangle.x = x;
	rectangle.y = y;

	SDL_RenderCopy(EZ_rendu, EZ_tableau_image[position % EZ_NB_MAX_IMAGE], NULL, &rectangle);
}

void EZ_trace_image_stocke_transparence(int position, int x, int y, unsigned char transparence)
{
	extern SDL_Texture *EZ_tableau_image[EZ_NB_MAX_IMAGE];
	extern SDL_Renderer *EZ_rendu;
	SDL_Rect rectangle;

	SDL_QueryTexture(EZ_tableau_image[position % EZ_NB_MAX_IMAGE], NULL, NULL, &(rectangle.w), &(rectangle.h));

	rectangle.x = x;
	rectangle.y = y;
	SDL_SetTextureAlphaMod(EZ_tableau_image[position % EZ_NB_MAX_IMAGE], transparence);
	SDL_RenderCopy(EZ_rendu, EZ_tableau_image[position % EZ_NB_MAX_IMAGE], NULL, &rectangle);
	SDL_SetTextureAlphaMod(EZ_tableau_image[position % EZ_NB_MAX_IMAGE], 255);
}


//void EZ_trace_image_stocke_rotation(int position,int x,int y,int angle)
//{
//    extern SDL_Texture* EZ_tableau_image[NB_MAX_IMAGE];
//    extern SDL_Renderer* EZ_rendu;
//	SDL_Rect rectangle;
//    if(SDL_RenderCopyEx(renderer, texture, &crop , &rect, angle, &center, flip);
//    SDL_QueryTexture(EZ_tableau_image[position%NB_MAX_IMAGE], NULL, NULL, &(rectangle.w), &(rectangle.h));
//
//    rectangle.x=x;
//    rectangle.y=y;
//    SDL_SetTextureAlphaMod(EZ_tableau_image[position%NB_MAX_IMAGE],transparence);
//    SDL_RenderCopy(EZ_rendu,EZ_tableau_image[position%NB_MAX_IMAGE],NULL,&rectangle);
//    SDL_SetTextureAlphaMod(EZ_tableau_image[position%NB_MAX_IMAGE],255);
//}




///////////////////////   Son et musique ///////////////////////////


// Charge le son "nom" et le place � la position donnee
void EZ_stocke_son(int position, char *nom)
{
	extern Mix_Chunk *EZ_son[EZ_NB_MAX_SON];
	Mix_FreeChunk(EZ_son[position % EZ_NB_MAX_SON]);
	EZ_son[position % EZ_NB_MAX_SON] = NULL;
	EZ_son[position % EZ_NB_MAX_SON] = Mix_LoadWAV(nom);
}

// joue le son un nombre nb de fois.
void EZ_joue_son(int position, int nb)
{
	extern Mix_Chunk *EZ_son[EZ_NB_MAX_SON];
	Mix_PlayChannel(position % EZ_NB_MAX_SON, EZ_son[position % EZ_NB_MAX_SON], nb - 1);
}

void EZ_initialisation_son()
{
	extern Mix_Chunk *EZ_son[EZ_NB_MAX_SON];
	int i;
	for (i = 0; i < EZ_NB_MAX_SON; i++) {
		EZ_son[i] = NULL;
	}
}

void EZ_destruction_son()
{
	extern Mix_Chunk *EZ_son[EZ_NB_MAX_SON];
	int i;
	for (i = 0; i < EZ_NB_MAX_SON; i++) {
		Mix_FreeChunk(EZ_son[i]);
		EZ_son[i] = NULL;
	}
}

void EZ_musique_off()
{
	extern Mix_Music *EZ_musique;
	if (EZ_musique != NULL) {
		Mix_FreeMusic(EZ_musique);
		EZ_musique = NULL;
	}
}

// Joue de la musique un certain nombre de fois.
int EZ_musique_on(char *nom, int repetition)
{
	extern Mix_Music *EZ_musique;

	if (EZ_musique)
		EZ_musique_off();
	EZ_musique = Mix_LoadMUS(nom);
	if (!EZ_musique) {
		fprintf(stderr, "Erreur d'initialisation de la musique\n");
		return 0;
	}
	Mix_PlayMusic(EZ_musique, repetition);
	return 1;
}

// Verifie musique verifie si la musique joue 1 (0 sinon)
int EZ_verifie_musique()
{
	return Mix_PlayingMusic();
}

// Mise � jour graphique
void EZ_mise_a_jour()
{
	extern SDL_Renderer *EZ_rendu;
	SDL_RenderPresent(EZ_rendu);
}


//////////////////////////////// Partie sur la gestion des �venements ///////////////////


// Donne le type d'un evenement
int EZ_recupere_evenement()
{

	extern SDL_Event EZ_evenement;
	SDL_WaitEvent(&EZ_evenement);
	switch (EZ_evenement.type) {
		case (SDL_MOUSEBUTTONDOWN):
			if (EZ_evenement.button.button == SDL_BUTTON_RIGHT)
				return EZ_SOURIS_BOUTON_DROITE_ENFONCE;
			if (EZ_evenement.button.button == SDL_BUTTON_LEFT)
				return EZ_SOURIS_BOUTON_GAUCHE_ENFONCE;
			return EZ_RIEN;
		case (SDL_MOUSEBUTTONUP):
			if (EZ_evenement.button.button == SDL_BUTTON_RIGHT)
				return EZ_SOURIS_BOUTON_DROITE_RELACHE;
			if (EZ_evenement.button.button == SDL_BUTTON_LEFT)
				return EZ_SOURIS_BOUTON_GAUCHE_RELACHE;
			return EZ_RIEN;
		case (SDL_KEYDOWN):
			return EZ_TOUCHE_ENFONCEE;
		case (SDL_KEYUP):
			return EZ_TOUCHE_RELACHEE;
		case (SDL_MOUSEMOTION):
			EZ_mouse_x = EZ_evenement.motion.x;
			EZ_mouse_y = EZ_evenement.motion.y;
			return EZ_SOURIS_MOUVEMENT;
		case (SDL_QUIT):
			return EZ_EXIT;
		case (SDL_JOYBUTTONDOWN):
			return EZ_BOUTON_ENFONCE;
		case (SDL_JOYBUTTONUP):
			return EZ_BOUTON_RELACHE;
		case (SDL_JOYHATMOTION):
			if (EZ_evenement.jhat.value == SDL_HAT_CENTERED)
				return EZ_CROIX_RELACHEE;
			return EZ_CROIX_ENFONCEE;
		default:
			return EZ_RIEN;
	}
}


// Donne le type d'un evenement avec une limite de temps
int EZ_recupere_evenement_temps_limite(int temps)
{
	extern SDL_Event EZ_evenement;
	int temps_debut = clock();

	if (SDL_PollEvent(&EZ_evenement))
		switch (EZ_evenement.type) {
			case (SDL_MOUSEBUTTONDOWN):
				if (EZ_evenement.button.button == SDL_BUTTON_RIGHT)
					return EZ_SOURIS_BOUTON_DROITE_ENFONCE;
				if (EZ_evenement.button.button == SDL_BUTTON_LEFT)
					return EZ_SOURIS_BOUTON_GAUCHE_ENFONCE;
				return EZ_RIEN;
			case (SDL_MOUSEBUTTONUP):
				if (EZ_evenement.button.button == SDL_BUTTON_RIGHT)
					return EZ_SOURIS_BOUTON_DROITE_RELACHE;
				if (EZ_evenement.button.button == SDL_BUTTON_LEFT)
					return EZ_SOURIS_BOUTON_GAUCHE_RELACHE;
				return EZ_RIEN;
			case (SDL_KEYDOWN):
				return EZ_TOUCHE_ENFONCEE;
			case (SDL_KEYUP):
				return EZ_TOUCHE_RELACHEE;
			case (SDL_MOUSEMOTION):
				EZ_mouse_x = EZ_evenement.motion.x;
				EZ_mouse_y = EZ_evenement.motion.y;
				return EZ_SOURIS_MOUVEMENT;
			case (SDL_QUIT):
				return EZ_EXIT;
			default:
				return EZ_RIEN;
		}
	while (clock() - temps_debut < temps);
	return EZ_RIEN;
}

int EZ_recupere_evenement_continu()
{
	extern SDL_Event EZ_evenement;
	if (SDL_PollEvent(&EZ_evenement)) {
		switch (EZ_evenement.type) {
			case (SDL_MOUSEBUTTONDOWN):
				if (EZ_evenement.button.button == SDL_BUTTON_RIGHT)
					return EZ_SOURIS_BOUTON_DROITE_ENFONCE;
				if (EZ_evenement.button.button == SDL_BUTTON_LEFT)
					return EZ_SOURIS_BOUTON_GAUCHE_ENFONCE;
				return EZ_RIEN;
			case (SDL_MOUSEBUTTONUP):
				if (EZ_evenement.button.button == SDL_BUTTON_RIGHT)
					return EZ_SOURIS_BOUTON_DROITE_RELACHE;
				if (EZ_evenement.button.button == SDL_BUTTON_LEFT)
					return EZ_SOURIS_BOUTON_GAUCHE_RELACHE;
				return EZ_RIEN;
			case (SDL_KEYDOWN):
				return EZ_TOUCHE_ENFONCEE;
			case (SDL_KEYUP):
				return EZ_TOUCHE_RELACHEE;
			case (SDL_MOUSEMOTION):
				EZ_mouse_x = EZ_evenement.motion.x;
				EZ_mouse_y = EZ_evenement.motion.y;
				return EZ_SOURIS_MOUVEMENT;
			case (SDL_QUIT):
				return EZ_EXIT;
			default:
				return EZ_RIEN;
		}
	}
	return EZ_RIEN;
}

// Vide le buffer evenement
void EZ_vide_buffer()
{
	SDL_Event event;
	while (SDL_PollEvent(&event));
}


//donne la position de la souris en x
int EZ_souris_x()
{
	return EZ_mouse_x;
}

//donne la position de la souris en y
int EZ_souris_y()
{
	return EZ_mouse_y;
}

// Donne la touche appuy�e
int EZ_touche()
{
	extern SDL_Event EZ_evenement;
	if (EZ_evenement.type == SDL_KEYDOWN || EZ_evenement.type == SDL_KEYUP)
		return EZ_evenement.key.keysym.sym;
	return 0;
}

///////////////////////////// Gestion du joystick /////////////////////////////////////////////

// initialise le joystick
void EZ_initialisation_joystick()
{
	extern SDL_Joystick *EZ_joystick;
	EZ_joystick = SDL_JoystickOpen(0);
	if (EZ_joystick != NULL)
		SDL_JoystickEventState(SDL_ENABLE);
}

// detruit le joysctick
void EZ_destruction_joystick()
{
	extern SDL_Joystick *EZ_joystick;
	SDL_JoystickClose(EZ_joystick);
	SDL_JoystickEventState(SDL_IGNORE);
}

// Donne le bouton du joystick qui a recu l'action
int EZ_bouton()
{
	extern SDL_Event EZ_evenement;
	if (EZ_evenement.type == SDL_JOYBUTTONDOWN || EZ_evenement.type == SDL_JOYBUTTONUP)
		return EZ_evenement.jbutton.button;
	return -1;
}

// Donne direction croix en degre mesure entre 0 et 360 (-1 si pas de direction ou -2 pas d'action de la croix)
int EZ_direction_croix()
{
	extern SDL_Event EZ_evenement;

	if (EZ_evenement.type == SDL_JOYHATMOTION) {
		switch (EZ_evenement.jhat.value) {
			case SDL_HAT_RIGHT:
				return 0;
			case SDL_HAT_RIGHTUP:
				return 45;
			case SDL_HAT_UP:
				return 90;
			case SDL_HAT_LEFTUP:
				return 135;
			case SDL_HAT_LEFT:
				return 180;
			case SDL_HAT_LEFTDOWN:
				return 225;
			case SDL_HAT_DOWN:
				return 270;
			case SDL_HAT_RIGHTDOWN:
				return 315;
			default:
				return -1;
		}
	}
	return -2;
}

///////////////////////  Partie de gestion des surfaces  ///////////////////



// initialise une EZ_image;
EZ_image *EZ_creation_image(int largeur, int hauteur)
{
	{
		EZ_image *image;
		SDL_Surface *surface = NULL;
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			surface = SDL_CreateRGBSurface(0, largeur, hauteur, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
		else
			surface = SDL_CreateRGBSurface(0, largeur, hauteur, 32, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);

		if (surface == NULL) {
			printf("Erreur lors de la creation de la surface dans EZ_creation_image : %s", SDL_GetError());
			return NULL;
		}
		image = malloc(sizeof(*image));
		image->surface = surface;
		return image;
	}
}

// destruction d une EZ_image
void EZ_destruction_image(EZ_image *image)
{
	SDL_FreeSurface(image->surface);
	free(image);
}

// donne les dimensions de l'image
void EZ_donne_dimension_image(EZ_image *image, int *largeur, int *hauteur)
{
	*largeur = ((SDL_Surface *) image->surface)->w;
	*hauteur = ((SDL_Surface *) image->surface)->h;
}

//charge une image
EZ_image *EZ_charge_image(char *nom)
{
	EZ_image *image;
	SDL_Surface *surface;
	surface = IMG_Load(nom);
	if (surface == NULL) {
		fprintf(stderr, "Erreur de chargement de l'image\n");
		return NULL;
	}
	image = malloc(sizeof(*image));
	image->surface = surface;
	return image;
}

// retourne la couleur en RGB
void EZ_recupere_rvb_image(EZ_image *image, int x, int y, unsigned char *r, unsigned char *v, unsigned char *b)
{
	int largeur, hauteur;
	EZ_donne_dimension_image(image, &largeur, &hauteur);

	if (x < 0 || x >= largeur || y < 0 || y >= hauteur) {
		*r = 0;
		*v = 0;
		*b = 0;
		return;
	}
	int nbOctetsParPixel = ((SDL_Surface *) (image->surface))->format->BytesPerPixel;
	Uint32 *p = (Uint32 *) ((Uint8 *) ((SDL_Surface *) (image->surface))->pixels + y * ((SDL_Surface *) (image->surface))->pitch + x * nbOctetsParPixel);
	SDL_GetRGB(*(p), ((SDL_Surface *) (image->surface))->format, r, v, b);
}

// colorie un pixel
void EZ_colorie_rvb_image(EZ_image *image, int x, int y, unsigned char r, unsigned char v, unsigned char b)
{
	int largeur, hauteur;
	EZ_donne_dimension_image(image, &largeur, &hauteur);

	if (x < 0 || x >= largeur || y < 0 || y >= hauteur) {
		return;
	}

	int nbOctetsParPixel = ((SDL_Surface *) (image->surface))->format->BytesPerPixel;
	Uint32 pixel;

	pixel = SDL_MapRGBA(((SDL_Surface *) (image->surface))->format, r, v, b, 0);

	Uint8 *p = (Uint8 *) ((SDL_Surface *) (image->surface))->pixels + y * ((SDL_Surface *) (image->surface))->pitch + x * nbOctetsParPixel;


	switch (nbOctetsParPixel) {
		case 1:
			*p = pixel;
			break;

		case 2:
			*(Uint16 *) p = pixel;
			break;

		case 3:
			/*Suivant l'architecture de la machine*/
			if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
				p[0] = (pixel >> 16) & 0xff;
				p[1] = (pixel >> 8) & 0xff;
				p[2] = pixel & 0xff;
			} else {
				p[0] = pixel & 0xff;
				p[1] = (pixel >> 8) & 0xff;
				p[2] = (pixel >> 16) & 0xff;
			}
			break;

		case 4:
			*(Uint32 *) p = pixel;
			break;
	}
}

// retourne la couleur en RGBA
void EZ_recupere_rvb_image_transparence(EZ_image *image, int x, int y, unsigned char *r, unsigned char *v, unsigned char *b, unsigned char *t)
{
	int largeur, hauteur;
	EZ_donne_dimension_image(image, &largeur, &hauteur);

	if (x < 0 || x >= largeur || y < 0 || y >= hauteur) {
		*r = 0;
		*v = 0;
		*b = 0;
		*t = 0;
		return;
	}
	int nbOctetsParPixel = ((SDL_Surface *) (image->surface))->format->BytesPerPixel;
	Uint32 *p = (Uint32 *) ((Uint8 *) ((SDL_Surface *) (image->surface))->pixels + y * ((SDL_Surface *) (image->surface))->pitch + x * nbOctetsParPixel);
	SDL_GetRGBA(*(p), ((SDL_Surface *) (image->surface))->format, r, v, b, t);
}

// colorie un pixel avec la transparence t
void EZ_colorie_rvb_image_transparence(EZ_image *image, int x, int y, unsigned char r, unsigned char v, unsigned char b, unsigned char t)
{
	int largeur, hauteur;
	EZ_donne_dimension_image(image, &largeur, &hauteur);

	if (x < 0 || x >= largeur || y < 0 || y >= hauteur) {
		return;
	}

	int nbOctetsParPixel = ((SDL_Surface *) (image->surface))->format->BytesPerPixel;
	Uint32 pixel;

	pixel = SDL_MapRGBA(((SDL_Surface *) (image->surface))->format, r, v, b, t);

	Uint8 *p = (Uint8 *) ((SDL_Surface *) (image->surface))->pixels + y * ((SDL_Surface *) (image->surface))->pitch + x * nbOctetsParPixel;


	switch (nbOctetsParPixel) {
		case 1:
			*p = pixel;
			break;

		case 2:
			*(Uint16 *) p = pixel;
			break;

		case 3:
			/*Suivant l'architecture de la machine*/
			if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
				p[0] = (pixel >> 16) & 0xff;
				p[1] = (pixel >> 8) & 0xff;
				p[2] = pixel & 0xff;
			} else {
				p[0] = pixel & 0xff;
				p[1] = (pixel >> 8) & 0xff;
				p[2] = (pixel >> 16) & 0xff;
			}
			break;

		case 4:
			*(Uint32 *) p = pixel;
			break;
	}
}


// Sauvegarde une image en format ppm P3
void EZ_sauvegarde_EZ_image_P3(EZ_image *image, char *nom)
{
	FILE *fichier = NULL;
	int i, j, largeur, hauteur;
	unsigned char r, v, b;
	if ((fichier = fopen(nom, "w+")) == NULL) {
		printf("erreur");
		exit(EXIT_FAILURE);
	}
	EZ_donne_dimension_image(image, &largeur, &hauteur);
	fprintf(fichier, "P3\n");
	fprintf(fichier, "%d %d\n", largeur, hauteur);
	fprintf(fichier, "255\n");
	for (i = 0; i < hauteur; i++) {
		for (j = 0; j < largeur; j++) {
			EZ_recupere_rvb_image(image, j, i, &r, &v, &b);
			fprintf(fichier, "%d %d %d\n", r, v, b);
		}
	}
	fclose(fichier);
}

// Sauvegarde une image en format ppm P3
void EZ_sauvegarde_EZ_image_BMP(EZ_image *image, char *nom)
{
	SDL_SaveBMP((SDL_Surface *) (image->surface), nom);
}

// Comme la fonction EZ_trace_image sauf que l'on donne l'image d�j� charg�e
int EZ_trace_EZ_image(EZ_image *image, int x, int y)
{
	extern SDL_Renderer *EZ_rendu;
	SDL_Rect rectangle;
	SDL_Surface *surface = (SDL_Surface *) (image->surface);
	if (surface == NULL) {
		fprintf(stderr, "Erreur pas d'image\n");
		return 0;
	}

	SDL_Texture *texture = SDL_CreateTextureFromSurface(EZ_rendu, surface);
	if (texture == NULL) {
		SDL_FreeSurface(surface);
		fprintf(stderr, "Erreur d'initialisation de la texture\n");
		return 0;
	}
	SDL_QueryTexture(texture, NULL, NULL, &(rectangle.w), &(rectangle.h));

	rectangle.x = x;
	rectangle.y = y;

	SDL_RenderCopy(EZ_rendu, texture, NULL, &rectangle);
	SDL_DestroyTexture(texture);
	return 1;
}

void EZ_affiche_EZ_image(EZ_image *image)
{
	int x, y;
	EZ_donne_dimension_image(image, &x, &y);
	EZ_destruction_fenetre();

	EZ_creation_fenetre("", x, y);
	EZ_trace_rectangle_plein(0, 0, x, y, 255, 0, 0, 0);
	EZ_mise_a_jour();
	EZ_trace_EZ_image(image, 0, 0);
	EZ_mise_a_jour();
	EZ_attendre_action();
	EZ_destruction_fenetre();
}

// trace une EZ_image (x et y sont les coordonn�es du coin sup�rieur gauche avec une trasparence 0 transparent 255 opaque
int EZ_trace_EZ_image_transparence(EZ_image *image, unsigned int x, unsigned int y, unsigned char transparence)
{
	if (image == NULL)return 0;
	extern SDL_Renderer *EZ_rendu;
	SDL_Rect rectangle;
	SDL_Surface *surface = (SDL_Surface *) (image->surface);
	if (surface == NULL) {
		fprintf(stderr, "Erreur d'initialisation de la surface\n");
		return 0;
	}
	SDL_Texture *texture = SDL_CreateTextureFromSurface(EZ_rendu, surface);
	if (texture == NULL) {
		fprintf(stderr, "Erreur d'initialisation de la texture\n");
		return 0;
	}
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(texture, transparence);
	SDL_QueryTexture(texture, NULL, NULL, &(rectangle.w), &(rectangle.h));
	rectangle.x = x;
	rectangle.y = y;

	SDL_RenderCopy(EZ_rendu, texture, NULL, &rectangle);
	SDL_DestroyTexture(texture);
	return 1;
}

EZ_image *EZ_transforme_EZ_image(EZ_image *image, double angle, double zoom)
{
	extern unsigned char EZ_aliasing;
	EZ_image *resultat;
	resultat = malloc(sizeof(*resultat));
	resultat->surface = rotozoomSurface(image->surface, angle, zoom, EZ_aliasing);
	return resultat;
}
