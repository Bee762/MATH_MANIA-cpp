#ifndef GAME_UI_H
#define GAME_UI_H
#include "include.h"
#include "game_state.h"

class game_ui : public game_state {

  public : 

  game_ui ();
  
  ~game_ui ();

  void set_colour (std::string_view a);

  void print_question();

  void print_copy_question() ;

  void print_options ();

  void print_score ();

  void print_lifes ();

  void answer_feedback();

  void print_streak ();

  void border_around_question ();

  void print_functionable_back_button(int width_left,int height);

  void resize_window();

  void question_ui();

  void answer_ui();

  void play_game();

  void opening_screen ();

  void loading_screen ();

  void rulebook();

  void check_high_score();

  void print_menu();

  void print_difficulty();

  void main_menu ();

  private : 
    //colours for terminal
   std::string red     = "red";
   std::string green   = "green";
   std::string yellow  = "yellow";
   std::string blue    = "blue";
   std::string cyan    = "cyan";
   std::string magenta = "magenta";
   std::string reset   = "reset";

};

#endif