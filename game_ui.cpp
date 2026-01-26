#include "include.h"
#include "game_ui.h"

  game_ui:: game_ui () : game_state () {

  }

   game_ui:: ~game_ui () {

  }
  void  game_ui:: set_colour (std::string_view a) {
    if (a == "red") {std::cout << "\033[31m";}
    else if (a == "green") {std::cout << "\033[32m";}
    else if (a == "yellow") {std::cout << "\033[33m";}
    else if (a == "blue") {std::cout << "\033[34m";}
    else if (a == "cyan") {std::cout << "\033[36m";}
    else if (a == "magenta") {std::cout << "\033[35m";}
    else if (a == "reset") {std::cout << "\033[0m";}
  }


  void  game_ui:: print_question() {
     get_terminal_size();
     border_around_question();
     set_colour ("yellow");
     move_cursor ((terminal_width/2 - (total_row/2 + 13)) , terminal_height/4);
     std::cout << "{QUESTION} : ";
      for (int i = 0; i < total_row; i++) {
        std::cout << equation [i];
      }
      std::cout << " = ?" << std::endl;
      set_colour("reset");
  }

    void  game_ui:: print_copy_question() {
     get_terminal_size();
     border_around_question();
     set_colour ("yellow");
     move_cursor ((terminal_width/2 - (total_row/2 + 13)) , terminal_height/4);
     std::cout << "{QUESTION} : ";
      for (int i = 0; i < total_row; i++) {
        std::cout << copy_question [i];
      }
      std::cout << " = ?" << std::endl;
       set_colour("reset");
     }

  void game_ui:: print_options () {
    set_colour("cyan");
    get_terminal_size();
    move_cursor ((terminal_width/2 - border_row/2 ) , terminal_height/4 + 2);
    std::cout << option_1 << "     " << option_2 << std::endl;
    move_cursor ((terminal_width/2 - border_row/2 ) , terminal_height/4 + 3);
    std::cout << option_3 << "     " << option_4 << std::endl;
    set_colour("reset");
  }

  void game_ui:: print_score () {
    get_terminal_size();
    move_cursor((terminal_width/2 - (border_row/2 + 2)) , terminal_height/4 + 9);
    set_colour("magenta");
    std::cout << "[SCORE : " << score << "]" << std::endl;
    move_cursor((terminal_width/2 - (border_row/2 + 1)) , terminal_height/4 + 10);
    print_streak();
    std::cout << std::endl;
    set_colour("reset");
  }

  void game_ui:: print_lifes () {
     get_terminal_size();
     move_cursor((terminal_width/2 - (border_row/2 + 10)) , terminal_height/4-4);
     set_colour("red");
     std::cout << "[HEALTH-BAR] : ";
     if (player_heart == 0) std::cout << "    ";
     else {
      for (int i = 0 ; i < player_heart ; i++) {
      std::cout << "[()]";
      }
      set_colour("reset");
     }
    std::cout << std::endl;
  }

  void game_ui:: answer_feedback() {

    get_terminal_size();
    move_cursor ((terminal_width/2 - (border_row/2 + 1) ) , terminal_height/4 + 4);
    set_colour("blue");
    if (time_up) std::cout << "[TIMES-UP!]" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(700));

    get_terminal_size();
    move_cursor ((terminal_width/2 - (border_row/2 + 3)) , terminal_height/4 + 5);

    if (user_answer == answer) {
      set_colour("green");
      std::cout << "[CORRECT-ANSWER!]" << std::endl;
    }
    else if (user_answer != answer && user_answer != 1000000 ) {
      set_colour("red");
      std::cout << "[WRONG-ANSWER!]" << std::endl;
    }
    else if (user_answer == 1000000) {
      set_colour ("red");

      if (player_quit) std::cout << "  GAME-ABORTED" << std::endl;

      else std::cout << "  [NO ANSWER]" << std::endl;

    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    set_colour ("reset");
  }

  void game_ui:: print_streak () {
    if (streak >= 3) {
      set_colour("green");
      std::cout << "STREAK x" << streak << std::endl;
      set_colour("reset");
    }
  }

  void game_ui:: border_around_question () {
    set_colour("red");
    //upper border
    move_cursor ((terminal_width/2 - (border_row/2 + 16)) , terminal_height/4 - 2);
    for (int i = 0; i <= 32 + border_row ; i++) {
      std::cout << ":";
    }
    //left border
    move_cursor ((terminal_width/2 - (border_row/2 + 17)) , terminal_height/4 - 2);
     for (int i =  (terminal_height/4 - 2)  ; i <= (terminal_height/4 - 2 + 9); i++) {
       move_cursor ((terminal_width/2 - (border_row/2 + 17)) , i);
      std::cout << ":" << std::endl;
    }
     //right border
     move_cursor ((terminal_width/2 - (border_row/2 - 15)) , terminal_height/4 - 2);
     for (int i =  (terminal_height/4 - 2)  ; i <= (terminal_height/4 - 2 + 9); i++) {
       move_cursor ((terminal_width/2 - (border_row/2 - 24)) , i);
      std::cout << ":" << std::endl;
    }
    //lower border
    move_cursor ((terminal_width/2 - (border_row/2 + 16)) , terminal_height/4 + 7);
    for (int i = 0; i <= 32 + border_row ; i++) {
      std::cout << ":";
    }

    // border around timer
     move_cursor ((terminal_width/2 - (border_row/2 - 21)) , terminal_height/4 - 1);
     for (int i =  (terminal_height/4 - 1)  ; i <= (terminal_height/4 ); i++) {
       move_cursor ((terminal_width/2 - (border_row/2 - 19)) , i);
      std::cout << ":" << std::endl;
     }  
    move_cursor ((terminal_width/2 - (border_row/2 - 19)) , terminal_height/4);
    for (int i = 0; i <= 4 ; i++) {
      std::cout << ":";
    }
    set_colour("reset");
  }

  void game_ui:: print_functionable_back_button(int width_left,int height) {
    //functional back mouse cllick button 
    move_cursor(width_left , height);
    set_colour("yellow");
    std::cout << ":{BACK}:" << std::endl;
    mouse_click_back_button (width_left,width_left+8,height);
    set_colour("reset");
    return ;
  }

  void game_ui:: resize_window() {
    while (!join_thread) {
    int current_height = terminal_height;
    int current_width = terminal_width;
    //store current terminal information
    get_terminal_size();//then call for get terminal size function
    //if there are changes
     if ((current_height != terminal_height) || (current_width != terminal_width)) {
      //clear screen and redraw
      system("cls");
      print_copy_question();
      print_options();
      print_lifes();
      print_score();
     }
     if (!join_thread) std::this_thread::sleep_for(std::chrono::milliseconds(50)); //if jointhread flag is not true
     //sleep current thread for a small duration for less cpu throttling
    }
  }

  void game_ui:: question_ui() {
      system("cls"); // clear the screen so new question can appear on same position
      generate_new_equation();
      print_question();
      print_lifes();
      print_score();
      solve_equation();
      generate_options();
      print_options();  
  }

  void game_ui:: answer_ui() {
    std::thread t1(&game_state::handle_keyboard_input, this);//because handle input or timer are not independent global func
      //they are functions of this obj i cant use them directly,here we basically say handle input is a func
      // for game_state  class and call it for current obj using this pointer

      std::thread t2 (&game_state::timer,this);  //handles timer for eacg question

      std::thread t3 (&game_ui::resize_window,this);  //checks if window/terminal is resized

      t1.join();
      t2.join();
      t3.join();

      answer_feedback();
      update_score_and_hearts();
      if(player_heart == 0) print_lifes(); //printing life before ending game
  }

  void game_ui:: play_game() {
  
    print_difficulty();
    difficulty = handle_mouse_clicks();

    //dynamic window resizing,if window is resized handle_mouse_clicks returns 5 
    // so if that happens we redraw,this way buttons will also be repositioned
    while (difficulty == 5 ){
    system("cls");
    print_difficulty();
    difficulty = handle_mouse_clicks();
    }

    if (difficulty == 4) return;  //return to main menu

    difficulty_scaling();

    //additional perks of difficulty

    if (difficulty == 1) {
      player_heart = 4;
      time_duration_sec = 20;
    }
    if (difficulty == 2) {
      player_heart = 3;
      time_duration_sec = 15;
    }
    if (difficulty == 3) {
      player_heart = 3;
      time_duration_sec = 10;
    }

   //resetting flags for replay
    score = 0;
    game_end = false;
    player_quit = false;
    streak = 0;

    while (true) {
      question_ui();
      answer_ui();
      if(player_quit||game_end) break;  //ending the program when player chooses to, and naturally end games when life is zero,
    }
      update_high_score();
  }

  void game_ui:: opening_screen () {

     system("cls");

     get_terminal_size();

     std::cout << "\033[1m"; //ansi escape for bold and bright text

     set_colour ("yellow");

    move_cursor(0,terminal_height/4);
    for (int i = 0; i < terminal_width ;i += 2) {
      std::cout << "><";
    }

    move_cursor(0,terminal_height*3/4);
    for (int i = 0; i < terminal_width ;i += 2) {
      std::cout << "><";
    }

    set_colour ("red");

    move_cursor (terminal_width/2 - 6,terminal_height/2);
    std::cout << ":M@TH-MANIA:" << std::endl;

    set_colour("blue");

    move_cursor(terminal_width/2 - 8,terminal_height/2 - 2);
    for (int i = terminal_width/2 - 8; i < terminal_width/2+8 ;i++) {
      std::cout << "#";
    }

    move_cursor(terminal_width/2 - 8,terminal_height/2 + 2);
    for (int i = terminal_width/2 - 8; i < terminal_width/2+8 ;i++) {
      std::cout << "#";
    }

    for (int i = (terminal_height/2-2); i < terminal_height/2 + 3 ;i++) {
      move_cursor(terminal_width/2 - 9,i);
      std::cout << "#" << std::endl;
    }

    for (int i = (terminal_height/2-2); i < terminal_height/2 + 3 ;i++) {
      move_cursor(terminal_width/2 + 8,i);
      std::cout << "#" << std::endl;
    }

    set_colour("magenta");

    for (int i = terminal_height / 4 + 1 ; i < terminal_height / 2 - 2 ; i++) {
      move_cursor(terminal_width/2 , i);
      std::cout << "|";
    }

    for (int i = terminal_height / 2 + 3 ; i < terminal_height *3 / 4  ; i++) {
      move_cursor(terminal_width/2 , i);
      std::cout << "|" ;
    }

    set_colour("cyan");

    move_cursor (terminal_width/2 - 10,terminal_height*3/4 + 1);
    std::cout << "~~ MADE BY ROHAN DEB(Bee)" << std::endl;

    //loading screen :  

    set_colour ("yellow");
     get_terminal_size();

    move_cursor(terminal_width/4,terminal_height/4 - 4);
    for (int i = terminal_width/4; i < terminal_width * 3/4 ;i++) {
      std::cout << ":";
    }

    for (int i = terminal_height / 4 - 3 ; i < terminal_height / 4  ; i++) {
      move_cursor(terminal_width/4, i);
      std::cout << ":";
    }

    for (int i = terminal_height / 4 - 3 ; i < terminal_height / 4  ; i++) {
      move_cursor(terminal_width * 3 / 4 - 1 , i);
      std::cout << ":";
    }

    move_cursor(terminal_width/4 + 4,terminal_height/4 - 2);
     set_colour ("red");
    std::cout << " LOADING : ";
  }

  void game_ui:: loading_screen () {
     std::cout << "\033[?25l";  // ansi escape code for hide cursor
     opening_screen();

     for (int i = terminal_width/4 + 15 ; i < terminal_width *3 /4 - 4 ; i++ ) {

      int current_height = terminal_height;
      int current_width = terminal_width;

      get_terminal_size();

      if (current_height!=terminal_height || current_width!=terminal_width) {
        system("cls"); //dynamic window resizing
        opening_screen();
      }

      set_colour("green");

      std::string b = random_operator();
      std::cout << b;
      std::this_thread::sleep_for(std::chrono::milliseconds(60));
    }

    set_colour("reset");

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    
  }

  void game_ui:: rulebook() {
    system("cls");
    std::cout << "\033[1m";

    get_terminal_size();
    move_cursor(terminal_width / 2 - 6 , terminal_height / 8);
    set_colour("yellow");
    std::cout << ":[RULE-B00K]:" << std::endl;
    for (int i = 0;i < terminal_width/2;i++) {
      std::cout << "><";
    }

    set_colour("red");
    move_cursor(4,terminal_height/8 + 3);
    std::cout << "{1} : RANDOM QUESTIONS ARE GENERATED DEPENDING ON DIFFICULTY,4 OPTIONS ARE GIVEN, TO ANSWER ," << std::endl;
    move_cursor(4,terminal_height/8 + 4);
    std::cout << "      PRESS CORRESPONDING OPTION NUMBER ON KEYBOARD (1,2,3,4) AND YOUR ANSWER WILL BE DETECTED." << std::endl;
    move_cursor(4,terminal_height/8 + 5);
    std::cout << "{2} : FOR EVERY CORRECT ANSWER GET +1 SCORE AND FOR 5 CORRECT ANSWER STREAK GET A HEART(MAXIMUM 5)," << std::endl;
    move_cursor(4,terminal_height/8 + 6);
    std::cout << "      FOR EVERY WRONG ANSWER LOSE A HEART AND CURRENT STREAK,GAME ENDS WHEN PLAYER HAS NO HEART LEFT." << std::endl;
    move_cursor(4,terminal_height/8 + 7);
    std::cout << "{3} : PLAYER GETS A FIXED AMOUNT OF TIME TO SOLVE A QUESTION ,TIMER IS DISPLAYED ON TOP RIGHT CORNER." << std::endl;
    move_cursor(4,terminal_height/8 + 8);
    std::cout << "{4} : IN MAIN MENU MOUSE CLICKS ARE ALLOWED BUT IN GAME ONLY KEYBOARD INPUTS ARE ALLOWED." << std::endl;
    move_cursor(4,terminal_height/8 + 9);
    std::cout << "{5} : PRESS Q TO END THE CURRENT GAME AND RETURN TO MAIN MENU." << std::endl;
    move_cursor(0,terminal_height/8 + 9 + 2);

    set_colour("yellow");
    for (int i = 0;i < terminal_width/2;i++) {
      std::cout << "><";
    }
     set_colour ("reset");

     //functional back mouse cllick button 

     print_functionable_back_button(terminal_width / 2 - 4,terminal_height / 8 + 14);

   }

   void game_ui:: check_high_score() {

    std::cout << "\033[1m";

    system("cls");
    get_terminal_size();
    set_colour ("cyan");
    move_cursor(0,terminal_height/8 - 2);
    for (int i = 0;i < terminal_width/2;i++) {
      std::cout << "><";
    }

    set_colour ("green");
    move_cursor(terminal_width/2 - 7 , terminal_height/8);
    std::ifstream file ("math_mania_highscore.txt");
    if (!file) {
      std::cout << ":{HIGHSCORE}: 0" << std::endl;
    }
    else {
      file >> high_score;
       std::cout << ":{HIGHSCORE}: " << high_score << std::endl;   
    }

    set_colour("cyan");
    move_cursor(0,terminal_height/8 + 2);
    for (int i = 0;i < terminal_width/2;i++) {
      std::cout << "><";
    }
    set_colour ("reset");

    print_functionable_back_button(terminal_width / 2 - 3,terminal_height / 8 + 5);

  }

   void game_ui:: print_menu() {
    get_terminal_size();
    std::cout << "\033[1m";
    std::cout << "\033[?25l";
    set_colour("cyan");

    //border around main menu
    //upper border
    move_cursor ((terminal_width/2 - (border_row/2 + 16)) , terminal_height/4 - 2);
    for (int i = 0; i <= 40 + border_row ; i++) {
      std::cout << "#";
    }
    //left border
    move_cursor ((terminal_width/2 - (border_row/2 + 17)) , terminal_height/4 - 2);
     for (int i =  (terminal_height/4 - 2)  ; i <= (terminal_height/4 - 2 + 15); i++) {
       move_cursor ((terminal_width/2 - (border_row/2 + 17)) , i);
      std::cout << "#" << std::endl;
    }
     //right border
     move_cursor ((terminal_width/2 - (border_row/2 - 15)) , terminal_height/4 - 2);
     for (int i =  (terminal_height/4 - 2)  ; i <= (terminal_height/4 - 2 + 15); i++) {
       move_cursor ((terminal_width/2 - (border_row/2 - 31)) , i);
      std::cout << "#" << std::endl;
    }
    //lower border
    move_cursor ((terminal_width/2 - 4) - 15 , terminal_height/4 + 13);
    for (int i = 0; i <= 40 + border_row ; i++) {
      std::cout << "#";
    }

    set_colour ("yellow");
    //print menu options : 
    move_cursor (terminal_width/2+2  , terminal_height/4 + 1);
    std::cout << "{:PLAY:}" << std::endl;
    move_cursor (terminal_width/2  , terminal_height/4 + 4);
    std::cout << "{:RULEBOOK:}" << std::endl;
    move_cursor (terminal_width/2  , terminal_height/4 + 7);
    std::cout << "{:HIGHSCORE:}" << std::endl;
    move_cursor (terminal_width/2+2  , terminal_height/4 + 10);
    std::cout << "{:QUIT:}" << std::endl;

    set_colour("reset");
   }

   void game_ui:: print_difficulty() {
    get_terminal_size();
    std::cout << "\033[1m";
    std::cout << "\033[?25l";
    set_colour("red");

    //border around main menu
    //upper border
    move_cursor ((terminal_width/2 - (border_row/2 + 16)) , terminal_height/4 - 2);
    for (int i = 0; i <= 40 + border_row ; i++) {
      std::cout << "#";
    }
    //left border
    move_cursor ((terminal_width/2 - (border_row/2 + 17)) , terminal_height/4 - 2);
     for (int i =  (terminal_height/4 - 2)  ; i <= (terminal_height/4 - 2 + 15); i++) {
       move_cursor ((terminal_width/2 - (border_row/2 + 17)) , i);
      std::cout << "#" << std::endl;
    }
     //right border
     move_cursor ((terminal_width/2 - (border_row/2 - 15)) , terminal_height/4 - 2);
     for (int i =  (terminal_height/4 - 2)  ; i <= (terminal_height/4 - 2 + 15); i++) {
       move_cursor ((terminal_width/2 - (border_row/2 - 31)) , i);
      std::cout << "#" << std::endl;
    }
    //lower border
    move_cursor ((terminal_width/2 - 4) - 15 , terminal_height/4 + 13);
    for (int i = 0; i <= 40 + border_row ; i++) {
      std::cout << "#";
    }

    set_colour ("yellow");
    //print menu options : 
    move_cursor (terminal_width/2+2  , terminal_height/4 + 1);
    std::cout << "{:EASY:}" << std::endl;
    move_cursor (terminal_width/2  , terminal_height/4 + 4);
    std::cout << " {:AVERAGE:}" << std::endl;
    move_cursor (terminal_width/2  , terminal_height/4 + 7);
    std::cout << "{:HARD-CORE:}" << std::endl;
    move_cursor (terminal_width/2+2  , terminal_height/4 + 10);
    std::cout << "{:BACK:}" << std::endl;

    set_colour("reset");
   }

   void game_ui:: main_menu () {
    loading_screen(); //gets called once as a intro scene
    while (true) {
    system("cls");
    get_terminal_size();
    print_menu();
    int mouse_input = handle_mouse_clicks();
    if (!mouse_input) handle_mouse_clicks(); //keep calling if we cant get a handle as we return 0 for that
    else if (mouse_input==1) play_game();
    else if (mouse_input==2) rulebook();
    else if (mouse_input==3) check_high_score();
    else if (mouse_input==4) return;
    else if (mouse_input==5) continue; // handle mouse input returns 5 when wimdow is resized
    // so this continue statement does nothing just skip current iteration and at next iteration
    //window is redrawn
    }
   }

