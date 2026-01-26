#ifndef GAME_STATE_H
#define GAME_STATE_H
#include "math_equation.h"

class game_state : public math_equation {

  public : 
  game_state();
  
  ~game_state ();

  void generate_options ();

  char get_input ();

  void handle_keyboard_input ();

  int handle_mouse_clicks();

  void mouse_click_back_button (int width_left,int width_right,int height);

  void update_score_and_hearts();

  void update_high_score ();

  void timer ();

  void game_quit ();

  void get_terminal_size();

  void move_cursor (int x,int y);


  protected :  
  int user_answer = 0;
  int score = 0; //answer streak ,reward user based on continuous correct answers
  int high_score = 0;
  int streak = 0;
  int player_heart = 3; // life system
  int option_1 = 0;
  int option_2 = 0;
  int option_3 = 0;
  int option_4 = 0;
  std::atomic<bool> join_thread = false; // using this in 2 func , handle input and timer
  //to avoid race condition using atomic bool
  int time_duration_sec = 15; // time limit for each question on screen
  bool game_end = false;
  bool player_quit = false;
  bool time_up = false;
  bool window_resized = false; //if user changes terminal_size

  int terminal_height = 0;
  int terminal_width = 0;
  int border_row = 7;  //for allignment of ui border

};


#endif