 #include "game.h"

  game::game() : game_ui () {

  }

  void game:: play () { 
     // its public entry point ,so no other func cant be called from main
    // except this one coz we r using private inheritance from game ui
    main_menu();
  }

