#include "Menu.h"
#include "Niveaux.h"
#include <allegro.h>
#include <string.h>
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void afficher_texte(BITMAP *page, const char *texte, int y, int couleur) {
    textprintf_centre_ex(page, font, SCREEN_W / 2, y, couleur, -1, "%s", texte);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void afficher_ecran_accueil() {
    BITMAP *buffer = create_bitmap(800, 600);
    BITMAP *fond = load_bitmap("Accueil.bmp", NULL);
    BITMAP *Joueur[4];


    Joueur[0] = load_bitmap("Joueur0.bmp", NULL);
    Joueur[1] = load_bitmap("Joueur1.bmp", NULL);
    Joueur[2] = load_bitmap("Joueur2.bmp", NULL);
    Joueur[3] = load_bitmap("Joueur3.bmp", NULL);

    int frame = 0;
    int delay = 0;

    int actif = 1;

    while (actif) {
        clear_bitmap(buffer);
        draw_sprite(buffer, fond, 0, 0);

        // Animation joueur
        stretch_sprite(buffer, Joueur[frame], 288, 200, 224, 224);

        // Texte
        afficher_texte(buffer, "Appuie sur ESPACE pour commencer", 500, makecol(255, 255, 255));

        delay++;
        if (delay > 6) {
            frame = (frame + 1) % 4;
            delay = 0;
        }

        blit(buffer, screen, 0, 0, 0, 0, 800, 600);

        if (key[KEY_SPACE]) actif = 0;

        rest(20);
    }

    // Libération mémoire
    destroy_bitmap(buffer);
    destroy_bitmap(fond);
    for (int i = 0; i < 4; i++) destroy_bitmap(Joueur[i]);
}

void afficher_aide() {
    BITMAP *buffer = create_bitmap(800, 600);

    int actif = 1;

    while (actif) {
        clear_bitmap(buffer);

        // Titre de l'aide
        afficher_texte(buffer, "=== AIDE DU JEU ===", 80, makecol(0, 255, 0));

        // Instructions
        afficher_texte(buffer, "Fleche HAUT : Monter", 180, makecol(255, 255, 255));
        afficher_texte(buffer, "Fleche BAS : Descendre", 220, makecol(255, 255, 255));
        afficher_texte(buffer, "ESPACE : Tirer", 260, makecol(255, 255, 255));
        afficher_texte(buffer, "P : Pause", 300, makecol(255, 255, 255));

        afficher_texte(buffer, "Appuie sur ECHAP pour revenir au menu", 500, makecol(255, 0, 0));

        blit(buffer, screen, 0, 0, 0, 0, 800, 600);
        rest(20);

        if (key[KEY_ESC]) {
            actif = 0;
            while (key[KEY_ESC]) rest(10); // Anti-rebond
        }
    }

    destroy_bitmap(buffer);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void afficher_menu_principal() {
    int selection = 0;
    int total_options = 6;

    BITMAP *buffer = create_bitmap(800, 600);

    while (1) {
        clear_bitmap(buffer);

        // Titre du menu
        afficher_texte(buffer, " MENU PRINCIPAL ", 80, makecol(0, 255, 255));

        // Affichage des options directement
        for (int i = 0; i < total_options; i++) {
            int color = (i == selection) ? makecol(255, 255, 0) : makecol(200, 200, 200);
            int y_position = 180 + i * 40;

            switch (i) {
                case 0:
                    afficher_texte(buffer, "Nouvelle partie", y_position, color);
                    break;
                case 1:
                    afficher_texte(buffer, "Continuer", y_position, color);
                    break;
                case 2:
                    afficher_texte(buffer, "Scores", y_position, color);
                    break;
                case 3:
                    afficher_texte(buffer, "Aide", y_position, color);
                    break;
                case 4:
                    afficher_texte(buffer, "Code de triche", y_position, color);
                    break;
                case 5:
                    afficher_texte(buffer, "Quitter", y_position, color);
                    break;
            }
        }

        blit(buffer, screen, 0, 0, 0, 0, 800, 600);
        rest(20);

        // Navigation dans le menu
        if (key[KEY_DOWN]) {
            selection = (selection + 1) % total_options;
            while (key[KEY_DOWN]) rest(10);
        }
        if (key[KEY_UP]) {
            selection = (selection - 1 + total_options) % total_options;
            while (key[KEY_UP]) rest(10);
        }

        if (key[KEY_ENTER]) {
            switch (selection) {
                case 0: return; // Nouvelle partie
                case 1: break;  // Continuer
                case 2: break;  // Scores
                case 3: afficher_aide(); break;  // Aide
                case 4: break;  // code (niveau, Boss)
                case 5: exit(0);// Quitter
            }
        }
    }

    destroy_bitmap(buffer);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

