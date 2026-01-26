#ifndef GAME_H
#define GAME_H
#include "game_ui.h"

class game : private game_ui {

  public :
  
  game();

  void play ();

};

#endif