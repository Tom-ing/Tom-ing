#include <allegro.h>
#include "Menu.h"


int main() {
    allegro_init();
    install_keyboard();
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0);

    afficher_ecran_accueil();
    afficher_menu_principal();


    return 0;
}
END_OF_MAIN();
