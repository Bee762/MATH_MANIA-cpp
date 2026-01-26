#include "include.h"
#include "game_state.h"

  game_state::game_state() : math_equation() {

  }
  game_state::~game_state () {

  }

  void game_state:: generate_options () {
  int correct_option = generaterandomnumber(1,4);
  if (correct_option == 1) {
    option_1 = answer;
    option_2 = generaterandomnumber(0,100);
    option_3 = generaterandomnumber(0,100);
    option_4 = generaterandomnumber(0,100);
  }
  else if (correct_option == 2) {
    option_1 = generaterandomnumber(0,100);
    option_2 = answer;
    option_3 = generaterandomnumber(0,100);
    option_4 = generaterandomnumber(0,100);
  }
  else if (correct_option == 3) {
    option_1 = generaterandomnumber(0,100);
    option_2 = generaterandomnumber(0,100);
    option_3 = answer;
    option_4 = generaterandomnumber(0,100);
  }
  else if (correct_option == 4) {
    option_1 = generaterandomnumber(0,100);
    option_2 = generaterandomnumber(0,100);
    option_3 = generaterandomnumber(0,100);
    option_4 =answer;
  }
  }

  char game_state:: get_input () {
    if (!_kbhit()) return 0;
    return _getch();
  }

  void game_state:: handle_keyboard_input () {
    user_answer = 1000000; //setting it unnecesarily high so if user doesnot answer the default ans wont be correct ans
    join_thread = false;
    std::cout << "\033[?25l";  // ansi escape code for hide cursor
    while (!join_thread) {
      char key = 0;
    while ((key = get_input()) == 0) {
       key = get_input();
       if (join_thread) break;
       std::this_thread::sleep_for(std::chrono::milliseconds(25));
    }
    if (key == '1') {user_answer = option_1;
                  join_thread = true;
                         break;}
    else if (key == '2') {user_answer = option_2;
                  join_thread = true;
                         break;}
    else if (key == '3') {user_answer = option_3;
                  join_thread = true;
                         break;}
    else if (key == '4') {user_answer = option_4;
                  join_thread = true;
                         break;}
    else if (key == 'q' || key == 'Q') { join_thread = true;
                    game_quit();}
    else if (key == 0) {} //this is default key,when user presses nothing and times up,we print nothing
    //else  {std::cout << "INVALID OPTION" << std::endl;}
    }
  }

  int game_state:: handle_mouse_clicks() {
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE); //getting a handle for input
    if (!hInput) return 0;  // if cannot get a handle return
    DWORD prev_mode;
    GetConsoleMode(hInput, &prev_mode);   //getting current mode and flags and storing it in previous mode
    //quick edit mode is on by default
    // Disable Quick Edit & enable mouse input

    DWORD new_mode = prev_mode;  // making a new mode will assign it later
    new_mode &= ~ENABLE_QUICK_EDIT_MODE;   //diabling quick edit mode of windows,quick edit mode uses the mouse input for text
    // selection in terminal,but we need mouse clicks for our own input system
    new_mode |= ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS; //enabbling mouse input in terminal,alsp extended flags so we can
    // edit the inputs accordint to our needs
    SetConsoleMode(hInput, new_mode); // setting console mode here and removing quick edit mode

    INPUT_RECORD record;  //to store input
    DWORD events;  // to detect a event like keypress , mouse click

    DWORD prevButtonState = 0;
    while (true) {
      get_terminal_size(); //get terminal size for accurate data of height and width of terminal
        ReadConsoleInput(hInput, &record, 1, &events); //  now read input from console , it is blocking type input not async

        if (record.EventType == MOUSE_EVENT) { // if recorded event is a mouse click

          auto& stored_event = record.Event.MouseEvent;  //storing the mouse event in a variable

          if (stored_event.dwEventFlags != 0) continue;   //if its scroll or movement type event skip the current iteration

          //if stored event is a click

            int col =stored_event.dwMousePosition.X; // get the mouse position in terminal text grid,windows handles the mapping
            // internally
            int row = stored_event.dwMousePosition.Y;
            DWORD state = stored_event.dwButtonState; //store the click in state

            bool current_left = state & FROM_LEFT_1ST_BUTTON_PRESSED;  //if its left click store in this bool
            bool previous_left = prevButtonState & FROM_LEFT_1ST_BUTTON_PRESSED; // also track if it was a left click
            //from before/ previous iterations in this bool,so sticky keys doesnot happens

            if (current_left && !previous_left) { // checking if left button is pressed
                // and also making sure its not from prvious state as we r using blocking input
                
                 if ((col >= terminal_width/2+2 && col <= terminal_width/2+10) && row == terminal_height/4 + 1)
                 {SetConsoleMode(hInput,prev_mode);  // re enabling prev mode also flags are reset because we might return after this
                   return 1;}

                 else if ((col >= terminal_width/2 && col <= terminal_width/2+14) && row == terminal_height/4 + 4)
                  {SetConsoleMode(hInput,prev_mode);
                   return 2;}

                 else if ((col >= terminal_width/2 && col <= terminal_width/2+15) && row == terminal_height/4 + 7) 
                 {SetConsoleMode(hInput,prev_mode);
                   return 3;}

                 else if ((col >= terminal_width/2+2 && col <= terminal_width/2+10) && row == terminal_height/4 + 10) 
                 {SetConsoleMode(hInput,prev_mode);
                   return 4;}

                 }

             prevButtonState = state;   //refreshing state for new input 
        }

        if (record.EventType == WINDOW_BUFFER_SIZE_EVENT) { // check if window is resized
            return 5;
        }
    } // while
} // func

//for back button making a overload
void game_state:: mouse_click_back_button (int width_left,int width_right,int height) {
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE); //getting a handle for input
    if (!hInput) hInput = GetStdHandle(STD_INPUT_HANDLE);  // if cannot get a handle return
    DWORD prev_mode;
    GetConsoleMode(hInput, &prev_mode);   //getting current mode and flags and storing it in previous mode
    //quick edit mode is on by default
    // Disable Quick Edit & enable mouse input

    DWORD new_mode = prev_mode;  // making a new mode will assign it later
    new_mode &= ~ENABLE_QUICK_EDIT_MODE;   //diabling quick edit mode of windows,quick edit mode uses the mouse input for text
    // selection in terminal,but we need mouse clicks for our own input system
    new_mode |= ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS; //enabbling mouse input in terminal,alsp extended flags so we can
    // edit the inputs accordint to our needs
    SetConsoleMode(hInput, new_mode); // setting console mode here and removing quick edit mode

    INPUT_RECORD record;  //to store input
    DWORD events;  // to detect a event like keypress , mouse click

    DWORD prevButtonState = 0;
    while (true) {
      get_terminal_size(); //get terminal size for accurate data of height and width of terminal
        ReadConsoleInput(hInput, &record, 1, &events); //  now read input from console , it is blocking type input not async

        auto& stored_event = record.Event.MouseEvent;  //storing the mouse event in a variable

        if (stored_event.dwEventFlags != 0) continue;   //if its scroll or movement type event skip the current iteration


        if (record.EventType == MOUSE_EVENT) { // if recorded event is a mouse click
            int col = stored_event.dwMousePosition.X; // get the mouse position in terminal text grid,windows handles the mapping
            // internally
            int row = stored_event.dwMousePosition.Y;
            DWORD state = stored_event.dwButtonState; //store the click in state

            bool current_left = state & FROM_LEFT_1ST_BUTTON_PRESSED;  //if its left click store in this bool
            bool previous_left = prevButtonState & FROM_LEFT_1ST_BUTTON_PRESSED; // also track if it was a left click
            //from before/ previous iterations in this bool,so sticky keys doesnot happens

            if (current_left && !previous_left) { // checking if left button is pressed
                // and also making sure its not from prvious state as we r using blocking input
                
                 if ((col >= width_left && col <= width_right) && row == height)
                 {SetConsoleMode(hInput,prev_mode);  // re enabling prev mode also flags are reset because we might return after this
                   return ;}
                   
            }

             prevButtonState = state;   //refreshing state for new input
             std::this_thread::sleep_for(std::chrono::milliseconds(25)); //sleeping the thread for less cpu hogging 
         }
        
      } //while
    } //func



  void game_state:: update_score_and_hearts() {
    if (user_answer == answer) {
      score++;
      streak++;
      if(streak % 5 == 0 && player_heart < 5) player_heart++; //for 5 streak reward player a heart but maximum 5 hearts allowed
    }
    else {
     player_heart--;
     streak = 0;
    if (player_heart == 0) {game_end = true;}
    }
  }

  void game_state:: update_high_score () {
    std::ifstream file ("math_mania_highscore.txt");
    if (!file){
      std::ofstream file ("math_mania_highscore.txt");
      file << high_score;
    }
    file >> high_score;
    if (score > high_score) {
      std::ofstream file ("math_mania_highscore.txt");
      file << score;
       move_cursor((terminal_width/2 - (total_row/2 + 5)) , terminal_height/4 + 10);
       std::cout << "[NEW HIGH-SCORE!]" << std::endl;
       std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    file.close();
  }

    void game_state:: get_terminal_size() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        terminal_width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        terminal_height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;//this func returns the height nd width of terminal in windows
    } else {
       terminal_width = 80;
       terminal_height  = 25;//if it cant do that for some reason,this is default terminal size most terminal in windows use
    }
  }

   void game_state:: move_cursor (int x,int y) {
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
  }

  void game_state:: timer () {
    time_up = false; //resetting the flag
    for (int i = time_duration_sec; i >= 0; i-- ) {
      if (i >= 10) {  // double digit  printing
       move_cursor ((terminal_width/2 - (border_row/2 - 21)) , terminal_height/4 - 1);
       std::cout << i ;
      }
      else { // if number is single digit printing a empty space before digit so number is erased properly
        move_cursor ((terminal_width/2 - (border_row/2 - 21)) , terminal_height/4 - 1);
        std::cout << " " << i ; 
      }
      
      if(!join_thread) std::this_thread::sleep_for(std::chrono::seconds(1)); // if join thread is true 
      // means input is recived then no sleep delay 
       else {break;} // immediately break

       if (i == 0) {time_up = true;  //to print it later storing data in a flag

           join_thread = true;} // if times up mark  join thread as true
    }
  }

  void game_state:: game_quit () {
    player_quit = true;
  }


