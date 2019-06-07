#include "wagner.h"
#include "easysdl.h"
#include <stdio.h>
#include <inttypes.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

// 2-3 fonctions venant de ma bibliothèque C++ mais qui ont été converties.
#define lc_maths_abs(number) (number < 0 ? -(number) : number)
#define lc_maths_min(a, b) (a < b ? a : b)
#define lc_maths_max(a, b) (a > b ? a : b)
#define lc_maths_clamp(number, min, max) lc_maths_min(lc_maths_max(number, min), max)

// L'ensemble des couleurs utilisés sous forme d'un tableau de couleur hexadécimale: 0xRRGGBB
static const uint32_t COLORS_HEX[WAGNER_COLORS_MAX] = {0xE50200, 0xE41400, 0xE32600, 0xE23700, 0xE24900, 0xE15A00,
                                                       0xE06B00, 0xE07C00, 0xDF8D00, 0xDE9E00, 0xDEAF00, 0xDDBF00,
                                                       0xDCD000, 0xD7DC00, 0xC6DB00, 0xB4DA00, 0xA3DA00, 0x91D900,
                                                       0x80D800, 0x6FD800, 0x5ED700, 0x4DD600, 0x3CD600, 0x2BD500,
                                                       0x1BD400, 0x0AD400, 0x00D305, 0x00D216, 0x00D226, 0x00D136,
                                                       0x00D046, 0x00CF56, 0x00CF65, 0x00CE75, 0x00CD85, 0x00CD94,
                                                       0x00CCA3, 0x00CBB3, 0x00CBC2, 0x00C3CA, 0x00B3C9, 0x00A3C9,
                                                       0x0093C8, 0x0083C7, 0x0073C7, 0x0063C6, 0x0053C5, 0x0044C5,
                                                       0x0034C4, 0x0025C3, 0x0016C3, 0x0007C2, 0x0700C1, 0x1600C1,
                                                       0x2500C0, 0x3400BF, 0x4200BF};
// L'ensemble des couleurs convertis en structure de couleur avec les valeurs RGB bien plus lisibles.
static w_Color_t COLORS[WAGNER_COLORS_MAX];
// Les caractères utilisés.
static const char CHARS[] = "0123456789ABCDEF";
// Matrice pour les caractères (au début)
static char LINES[33][WAGNER_COLORS_MAX];
// Deuxième matrice pour afficher ISN en grand mais en soit elle est inutile puisqu'on pourrait fusionner les deux matrices.
static char FOREGROUND[33][WAGNER_COLORS_MAX];
// Les traînées
static w_Trail_t TRAILS[WAGNER_TRAILS_MAX];

// Est-ce que le logo est en marche?
bool running = true;

// Plusieurs variables ayant divers utilisation.
int state = 0;
int init_state = 0;
int g_i = 0, g_j = 0;
// Opacité du "sous-titre" qui est "Lycée Stanislas 2018-2019"
unsigned char subtitle = 0;

// Convertit une couleur hexadécimale en couleur RGB.
w_Color_t hex_to_rgb(uint32_t hex)
{
    w_Color_t color;
    color.red = (unsigned char) (((hex >> 16) & 0xFF));  // Extract the RR byte
    color.green = (unsigned char) (((hex >> 8) & 0xFF));   // Extract the GG byte
    color.blue = (unsigned char) (((hex) & 0xFF));        // Extract the BB byte

    return color;
}

// Transforme rapidement un caractère simple en chaîne de caractère (pour EZ_trace_texte)
char *get_string(char c)
{
    static char result[2];
    result[0] = c; // On prend un caractère aléatoire dans l'alphabet.
    result[1] = '\0'; // Indicateur de fin de chaîne de caractère.
    return result;
}

char wagner_pick_char()
{
    size_t length = strlen(CHARS);
    // rand est utilisé, malheureusement c'est un nombre pas vraiment aléatoire et il est peu conseillé de l'utiliser, mais il n'y a pas d'alternative dans ce cas en C donc on l'utilise quand même.
    size_t index = rand() % length; // On prend un nombre aléatoire entre 0 et length, length le nombre de caractère dans CHARS.
    return CHARS[index];
}

void wagner_draw()
{
    size_t i, c_i;
    // On affiche toutes les traînées visibles.
    for (i = 0; i < WAGNER_TRAILS_MAX; i++) {
        w_Trail_t trail = TRAILS[i];
        if (trail.active) {
            // On trace pour chaque caractère (5)
            for (c_i = 0; c_i < 5; c_i++) {
                size_t real_y = trail.y + c_i;
                if (real_y > 33 || real_y < 0)
                    break;
                unsigned char opacity = (unsigned char) (51 * c_i);
                EZ_trace_texte(get_string(trail.chars[c_i]), WAGNER_FONT_NAME, 16, trail.x * WAGNER_CHAR_WIDTH,
                               (uint32_t) (real_y * WAGNER_CHAR_HEIGHT), COLORS[trail.x].red, COLORS[trail.x].green,
                               COLORS[trail.x].blue, opacity);
            }
        }
    }

    // On affiche ici les matrices
    uint32_t x = 0;
    uint32_t y = 0;
    int i2, j;
    // Boucle des abscisse de la matrice.
    for (i2 = 0; i2 < WAGNER_COLORS_MAX; i2++) {
        // Boucle des ordonnées de la matrice.
        for (j = 0; j < 33; j++) {
            // Caractère à afficher à ces cordonnées
            char to_print = LINES[j][i2];
            if (FOREGROUND[j][i2] != ' ')
                to_print = FOREGROUND[j][i2];

            if (to_print == ' ') {
                // Caractère vide? On passe notre chemin.
                y += WAGNER_CHAR_HEIGHT;
                continue;
            }

            // On efface ce qu'il y a derrière sinon ça fait "un bouillie".
            EZ_trace_rectangle_plein(x, y, WAGNER_CHAR_WIDTH, WAGNER_CHAR_HEIGHT, 0, 0, 0, 255);
            EZ_trace_texte(get_string(to_print), WAGNER_FONT_NAME, 16, x, y, COLORS[i2].red, COLORS[i2].green, COLORS[i2].blue,
                           255);
            // On augment en ordonnées d'affichage.
            y += WAGNER_CHAR_HEIGHT;
        }
        // On renvient à l'origine pour les ordonnées et on change de colonnes.
        y = 0;
        x += WAGNER_CHAR_WIDTH;
    }

    EZ_trace_texte("Lycee Stanislas 2018-2019", WAGNER_FONT_NAME, 24, 238, 388, 255, 255, 255, subtitle);
}

// Génère une ligne de caractères aléatoire à une ordonnée de la matrice.
void gen_line(size_t y)
{
    size_t x;
    for (x = 0; x < WAGNER_COLORS_MAX; x++) {
        LINES[y][x] = wagner_pick_char();
    }
}

void wagner_update()
{
    size_t i, x, y, a;
    // Première étape: affichage d'un bloc de caractère qui descend
    if (state == 0) {
        // On génère la première rangée.
        if (init_state == 0) {
            for (i = 0; i < WAGNER_COLORS_MAX; i++)
                LINES[0][i] = wagner_pick_char();
            init_state++;
            return;
        }
            // Tant que la dernière ligne est vide, on bouge toutes les lignes de 1 vers le bas.
        else if (init_state == 1) {
            static char copy[33][57];
            for (y = 0; y < 33; y++)
                for (x = 0; x < WAGNER_COLORS_MAX; x++)
                    copy[y][x] = LINES[y][x];

            for (y = 0; y < 33; y++) {
                if (y + 1 < 33)
                    for (i = 0; i < WAGNER_COLORS_MAX; i++)
                        LINES[y + 1][i] = copy[y][i];
            }
            gen_line(0);
            if (LINES[32][0] != ' ')
                init_state++;
        }
            // La fin, on fait disparaître tous les caractères et on change d'étape, on passe à la deuxième étape.
        else {
            static char copy[33][57];
            for (y = 0; y < 33; y++)
                for (x = 0; x < WAGNER_COLORS_MAX; x++)
                    copy[y][x] = LINES[y][x];

            for (x = 0; x < WAGNER_COLORS_MAX; x++) {
                LINES[g_i][x] = ' ';
            }

            for (y = 0; y < 33; y++) {
                if (LINES[y][0] != ' ')
                    if (y + 1 < 33)
                        for (i = 0; i < WAGNER_COLORS_MAX; i++)
                            LINES[y + 1][i] = copy[y][i];
            }

            g_i++;
            if (g_i >= 33) {
                state++;
                g_i = 0;
            }
        }
    }
        // Pour la deuxième et troisième étapes on retrouve les traînées.
    else if (state == 1 || state == 2) {
        // Pour la troisième et dernière étape on affiche toutes les WAGNER_CLOCK_SPEED * 2 ms une nouvelle ligne du mot ISN écrit avec divers caractères.
        if (state == 2) {
            if (g_j == 0 || g_j == 1) {
                y = (size_t) (WAGNER_LOGO_START_Y + g_j);
                for (a = 0; a < 6; a++)
                    FOREGROUND[y][WAGNER_LOGO_START_X + a] = wagner_pick_char();
                int start_x = WAGNER_LOGO_START_X + 6 + 4;
                for (a = 0; a < 6; a++)
                    FOREGROUND[y][start_x + 2 + a] = 'S';
                start_x += 8 + 4;
                for (a = 0; a < 2; a++)
                    FOREGROUND[y][start_x + a] = 'N';
                for (a = 0; a < 2; a++)
                    FOREGROUND[y][start_x + 8 + a] = 'N';
            } else if (g_j == 2 || g_j == 3) {
                y = (size_t) (WAGNER_LOGO_START_Y + g_j);
                for (a = 0; a < 2; a++)
                    FOREGROUND[y][WAGNER_LOGO_START_X + 2 + a] = wagner_pick_char();
                int start_x = WAGNER_LOGO_START_X + 6 + 4;
                for (a = 0; a < 2; a++)
                    FOREGROUND[y][start_x + a] = 'S';
                start_x += 8 + 4;
                for (a = 0; a < 4; a++)
                    FOREGROUND[y][start_x + a] = 'N';
                for (a = 0; a < 2; a++)
                    FOREGROUND[y][start_x + 8 + a] = 'N';
            } else if (g_j == 4 || g_j == 5) {
                y = (size_t) (WAGNER_LOGO_START_Y + g_j);
                for (a = 0; a < 2; a++)
                    FOREGROUND[y][WAGNER_LOGO_START_X + 2 + a] = wagner_pick_char();
                int start_x = WAGNER_LOGO_START_X + 6 + 4;
                for (a = 0; a < 4; a++)
                    FOREGROUND[y][start_x + 2 + a] = 'S';
                start_x += 8 + 4;
                for (a = 0; a < 2; a++)
                    FOREGROUND[y][start_x + a] = 'N';
                for (a = 0; a < 2; a++)
                    FOREGROUND[y][start_x + 4 + a] = 'N';
                for (a = 0; a < 2; a++)
                    FOREGROUND[y][start_x + 8 + a] = 'N';
            } else if (g_j == 6 || g_j == 7) {
                y = (size_t) (WAGNER_LOGO_START_Y + g_j);
                for (a = 0; a < 2; a++)
                    FOREGROUND[y][WAGNER_LOGO_START_X + 2 + a] = wagner_pick_char();
                int start_x = WAGNER_LOGO_START_X + 6 + 4;
                for (a = 0; a < 2; a++)
                    FOREGROUND[y][start_x + 6 + a] = 'S';
                start_x += 8 + 4;
                for (a = 0; a < 2; a++)
                    FOREGROUND[y][start_x + a] = 'N';
                for (a = 0; a < 4; a++)
                    FOREGROUND[y][start_x + 6 + a] = 'N';
            } else if (g_j == 8 || g_j == 9) {
                y = (size_t) (WAGNER_LOGO_START_Y + g_j);
                for (a = 0; a < 6; a++)
                    FOREGROUND[y][WAGNER_LOGO_START_X + a] = wagner_pick_char();
                int start_x = WAGNER_LOGO_START_X + 6 + 4;
                for (a = 0; a < 6; a++)
                    FOREGROUND[y][start_x + a] = 'S';
                start_x += 8 + 4;
                for (a = 0; a < 2; a++)
                    FOREGROUND[y][start_x + a] = 'N';
                for (a = 0; a < 2; a++)
                    FOREGROUND[y][start_x + 8 + a] = 'N';
            }
                // On a finit d'afficher alors on commence à afficher "Lycée Stanislas 2018-2019 progressivement en augmentant son alpha.
            else {
                subtitle = (unsigned char) lc_maths_clamp(subtitle + 25, 0, 255);
            }
            g_j++;

            // Une fois qu'on a atteint 200 mise à jour on sort du programme. Ce qui correspondrait à 10 secondes depuis la dernière étape.
            if (g_j == 200)
                running = false;
        }

        // Activation aléatoire des traînées inactives.
        int o = lc_maths_clamp(lc_maths_abs(rand() % WAGNER_COLORS_MAX), 0, WAGNER_COLORS_MAX);
        {
            w_Trail_t trail = TRAILS[o];
            trail.active = true;
            TRAILS[o] = trail;
        }

        // On bouge les traînées ver le bas et on revient à -5 si c'est fini.
        for (i = 0; i < WAGNER_TRAILS_MAX; i++) {
            w_Trail_t trail = TRAILS[i];

            if (trail.active) {
                if (trail.y + 1 > 33) {
                    trail.y = -5;
                } else
                    trail.y++;
            }

            TRAILS[i] = trail;
        }

        if (state != 2) {
            g_i++;
            if (g_i == 10)
                state++;
        }
    }
}

// On vérifie qu'il n'y a pas toutes les traînées au même endroit.
void check_trails()
{
    size_t i, j;
    for (i = 0; i < WAGNER_TRAILS_MAX; i++) {
        w_Trail_t trail = TRAILS[i];
        for (j = 1; j < WAGNER_TRAILS_MAX; j++) {
            if (i == j)
                continue;
            w_Trail_t trail1 = TRAILS[j];
            if (trail1.x == trail.x) {
                trail.x++;
                if (trail.x > WAGNER_COLORS_MAX)
                    trail.x = 0;
            }
        }
        TRAILS[i] = trail;
    }
}


// Fonction de lancement.
int wagner_logo()
{
    // On initialise la fonction d'aléatoire à partir du temps.
    srand((uint32_t) time(NULL));
    int i, j;
    // On convertit la liste de couleurs hexadécimales en couleurs RGB.
    for (i = 0; i < WAGNER_COLORS_MAX; i++) {
        uint32_t hex = COLORS_HEX[i];
        w_Color_t rgb = hex_to_rgb(hex);
        COLORS[i] = rgb;
    }

    // Initialisation des "matrices"
    for (i = 0; i < 33; i++) {
        for (j = 0; j < 57; j++) {
            LINES[i][j] = ' ';
            FOREGROUND[i][j] = ' ';
        }
    }
    size_t i2, j2;
    // Initialisation des traînées
    for (i2 = 0; i2 < WAGNER_TRAILS_MAX; i2++) {
        w_Trail_t trail;
        trail.active = false;
        trail.x = (uint32_t) lc_maths_clamp(lc_maths_abs(rand() % WAGNER_COLORS_MAX), 0, WAGNER_COLORS_MAX);
        trail.y = 0;
        for (j2 = 0; j2 < 5; j2++)
            trail.chars[j2] = wagner_pick_char();
        TRAILS[i2] = trail;
    }

    check_trails();
    check_trails();

    // Création de la fenêtre et on joue la musique (pas de constantes pour la musique car on l'a qu'une fois?).
    EZ_creation_fenetre("ISN - Logo", WAGNER_WIDTH, WAGNER_HEIGHT);
    EZ_musique_on("../resources/the-matrix-main-title-don-davis.ogg", 1);

    // Variables pour gérer le temps des mis à jour des éléments.
    clock_t now_time = 0, last_time = clock() / WAGNER_CLOCKS_PER_MS, timer = clock() / CLOCKS_PER_SEC, delta_time = 0;
    // Elles ne sont jamais utilisés, mais on pourrait les afficher dans le cadre d'un débuggage.
    uint32_t fps = 0, updates = 0;

    // result c'est le dernier évènement récupérer
    int result;
    while (running) {
        // Arrière plan.
        EZ_trace_rectangle_plein(0, 0, WAGNER_WIDTH, WAGNER_HEIGHT, 0, 0, 0, 255);
        // On dessine.
        wagner_draw();
        fps++;

        now_time = clock() / WAGNER_CLOCKS_PER_MS;
        delta_time += (now_time - last_time);
        last_time = now_time;

        // On met à jour les calculs que lorsque la différence de temps attaint WAGNER_CLOCK_SPEED en millisecondes.
        if (delta_time >= WAGNER_CLOCK_SPEED) {
            wagner_update();
            updates++;
            delta_time = 0;
        }

        EZ_mise_a_jour();
        // On récupère les évènements: la fenêtre répond.
        result = EZ_recupere_evenement_continu();
        if (result == EZ_EXIT)
            running = false;
        else if (result == EZ_TOUCHE_ENFONCEE && EZ_touche() == '\033')
            running = false;

        if ((clock() / CLOCKS_PER_SEC) - timer > 1) {
            timer++;
            updates = 0, fps = 0;
        }
    }

    // On détruit tout et on quitte.
    EZ_musique_off();
    EZ_destruction_fenetre();
    return 0;
}
