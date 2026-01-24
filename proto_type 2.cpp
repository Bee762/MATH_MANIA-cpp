#include <iostream>
#include <random>
#include <string>
#include <windows.h>
#include <conio.h>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <atomic>
#include <string_view>
#include <fstream>


class math_equation {
    
    public : 
    //equation is used in raII method,created in constructor and deleted in destructos,so its memory safe
    //i want dynamic difficulty scaling meaning user should be able to alter difficulty from within
      //the obj,but i also want my dynamic question array to be created at constructor i cant do that normally
      // here is what i thought as solution :
      //as i cant modify the size of the array after obj creation
      //i will generate the maximum size of array user can that will be 6 number 5 operator,
      // and if user chooses easy or medium difficulty i will mark the remaining slot with placeholder
      //that my algotythm already ignores
    math_equation () {
      equation = new std::string [max_row];
     }

    ~math_equation () {
      delete[] equation;
      equation = nullptr;
      }

    int str_to_int (std::string a) {
    int x = std::stoi(a);
    return x;
    }

     std::string int_to_str (int a) {
    return std::to_string (a);
    }

    int generaterandomnumber(int min, int max) {
    std::uniform_int_distribution<> dist(min, max); // Uniform distribution
    return dist(gen);// Generate and return random number
    }

    std::string random_operator () {
    int a = generaterandomnumber (1,4);
    if (a == 1) return "+";
    if (a == 2) return "-";
    if (a == 3) return "*";
    if (a == 4) return "/";
      return "0";
    }

    std::string random_number () {
    int a = generaterandomnumber(1,9);
    std::string random_num = int_to_str (a);
    return random_num;
    }

    void difficulty_scaling () {

      if (difficulty == 1) {  //easy
        number = 4;
      }

      else if (difficulty == 2) {  //medium
        number = 5;
      }

      else if (difficulty == 3) {  //hard
        number = 6;
      }

      else if (difficulty > 3) return;//simply return on wrong input; 

      op = number-1;
      total_row = number+op;
      
    }

    //generating question
    void generate_new_equation() {

      //empty whole existing array
      for (int i = 0;  i < max_row ; i++) {
        equation [i] = "empty";
        }

    // filling in with data
   for (int i = 0; i < total_row ; i++) {  //using total row here and that will be decided from difficulty scaling
    if (i % 2 == 0) equation [i] = random_number(); //put a number in odd position  
    else equation[i] = random_operator(); // put a operator in even position
    } // so equation will look number op number op number like this

      //copying current question in question array with emptyspaces
       for (int i = 0;  i < max_row ; i++) {
        copy_question [i] = equation[i];
        }



      // reseting the variables

     divide_op_present = true;
     multiply_op_present = true;
     addition_op_present = true;
     subtraction_op_present = true;
     answer = 0;

    }

    //algorithm to solve the equation with precedence

    void precedence_solving (bool& a , std::string_view b) {
     while (a == true) {  // it will check for multiplr times if it find 1 instance of b;
    	previous_op = "empty";  //resetting previous op

     for (int i = 0;i < total_row;i++) {

       if (equation[i] == "empty") continue;  //if string is empty ignore

       if (equation[i] == b) {    //find the passed op
         a = true; //set condition to true
        for (int x = i-1; x >= 0;x--) {
         if (equation[x] == "empty") continue;
         previous_number = str_to_int (equation[x]);  //get the previous number
         equation[x] = "empty"; // make it empty

         //checking for  unary minus bug where - 12 and -12 are separate entity

        if (b== "+" || b== "-") {  //only for adition and subtraction
          	for (int i = x-1 ; i >= 0 ; i--) { //check for the operator before previous no
              if (equation[i] == "empty") continue;
            else if (equation[i] != "empty" && equation[i] != "-") break; //if previous op is anything else than -,break
            else if (equation[i] == "-") // if previous op is -
          	previous_op = equation [i]; // store it
          	equation[i] = "empty"; // make it empty in array but we will put it back if needed later
          	   break;
          	    }	          	
          }    
         break;
        }
        // get next number from same method
        for (int x = i+1; x < total_row ; x++) {
         if (equation[x] == "empty") continue;
         next_number = str_to_int (equation [x]);
         equation[x] = "empty";
         break;
        }

        int result = 0; // reset result;

        if (b == "/") result = previous_number/next_number;
        else if (b == "*") result = previous_number*next_number;
        else if (b == "+" && previous_op == "-") { int temporary_result = -previous_number +next_number;
          //here solving the unary operator problem by taking a -ve sign before prev number only for this specific condition
             if (temporary_result < 0) { // if result is negative
              equation [i-1] = "-";} //we put a -ve sign before results position in array
             else if (temporary_result > 0) { // if its positive we put a +ve sign in arry before result position
              equation [i-1] = "+";}
              result = std::abs(temporary_result);} // then we take the absolute value of result because sign problem is 
        // already dealt with before
        else if (b == "+") result = previous_number+next_number;
        else if (b == "-" && previous_op == "-") { int temporary_result = -previous_number - next_number;
             if (temporary_result < 0) {
              equation [i-1] = "-";}
             else if (temporary_result > 0) {
        	    equation [i-1] = "+";}
              result = std::abs(temporary_result);}
        else if (b == "-") result = previous_number-next_number;

        equation [i] = int_to_str(result);   //convering result back to sring and put it in the position of the current operator
        break;
        }

        else {
        a = false;
        }
       }//for loop

     }//while loop

    }//function end

    void solve_equation () {
    precedence_solving(divide_op_present,"/"); //solve for division op first and so on
    precedence_solving(multiply_op_present,"*");
    precedence_solving(addition_op_present,"+");
    precedence_solving(subtraction_op_present,"-");

     for (int i = 0; i < total_row; i++) { // after precedence solving only 1 number will be left in array
      // and that will be final resuly,scan for it :
       if (equation[i] != "empty") {
        answer = str_to_int(equation[i]); // convert the ans back to int
        break;
       }
      }
    }


    protected :
    int previous_number = 0;
    int next_number = 0; 
    int answer = 0;

    int difficulty = 0;  //will use this as a flag to use in future depending on difficulty;

    // equation data
    int number = 0;   
    int op = 0;
    int total_row = number+op;

    int max_row = 11;   // maximum possible number in hard mode (6 number 5 operator)

    std::string* equation = nullptr;
    // to asign this array,its lenth must be known at compile time
    // so we are  using static (means only one copy of the var for all objs of this class ) and 
    //constexpr (means value is known at compile time)

    bool divide_op_present = true;
    bool multiply_op_present = true;
    bool addition_op_present = true;
    bool subtraction_op_present = true;
    std::string previous_op = "empty";  //used for unary minus detection later

   std::mt19937 gen{std::random_device{}()}; //random number generator engine

    std::string copy_question [11];  // a array that we will copy current question 
  // and print the question from here as our original array will be used in solving
  // so it will contain result and many other things and during window resize 
  //need to redraw question

};

class game_state : public math_equation {

  public : 
  game_state() : math_equation() {
  }
  ~game_state () {

  }

  void generate_options () {
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

  char get_input () {
    if (!_kbhit()) return 0;
    return _getch();
  }

  void handle_keyboard_input () {
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

  int handle_mouse_clicks() {
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
void mouse_click_back_button (int width_left,int width_right,int height) {
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



  void update_score_and_hearts() {
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

  void update_high_score () {
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
    }
    file.close();
  }

  void timer () {
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

  void game_quit () {
    player_quit = true;
  }

  void get_terminal_size() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        terminal_width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        terminal_height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;//this func returns the height nd width of terminal in windows
    } else {
       terminal_width = 80;
       terminal_height  = 25;//if it cant do that for some reason,this is default terminal size most terminal in windows use
    }
  }

  void move_cursor (int x,int y) {
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(
      GetStdHandle(STD_OUTPUT_HANDLE),pos
    );
  }


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

class game_ui : public game_state {

  public : 

  game_ui () : game_state () {

  }

  ~game_ui () {

  }
  void set_colour (std::string_view a) {
    if (a == "red") {std::cout << "\033[31m";}
    else if (a == "green") {std::cout << "\033[32m";}
    else if (a == "yellow") {std::cout << "\033[33m";}
    else if (a == "blue") {std::cout << "\033[34m";}
    else if (a == "cyan") {std::cout << "\033[36m";}
    else if (a == "magenta") {std::cout << "\033[35m";}
    else if (a == "reset") {std::cout << "\033[0m";}
  }


  void print_question() {
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

    void print_copy_question() {
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

  void print_options () {
    set_colour("cyan");
    get_terminal_size();
    move_cursor ((terminal_width/2 - border_row/2 ) , terminal_height/4 + 2);
    std::cout << option_1 << "     " << option_2 << std::endl;
    move_cursor ((terminal_width/2 - border_row/2 ) , terminal_height/4 + 3);
    std::cout << option_3 << "     " << option_4 << std::endl;
    set_colour("reset");
  }

  void print_score () {
    get_terminal_size();
    move_cursor((terminal_width/2 - (border_row/2 + 2)) , terminal_height/4 + 9);
    set_colour("magenta");
    std::cout << "[SCORE : " << score << "]" << std::endl;
    move_cursor((terminal_width/2 - (border_row/2 + 1)) , terminal_height/4 + 10);
    print_streak();
    std::cout << std::endl;
    set_colour("reset");
  }

  void print_lifes () {
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

  void answer_feedback() {

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
      std::cout << "  [NO ANSWER]" << std::endl;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    set_colour ("reset");
  }

  void print_streak () {
    if (streak >= 3) {
      set_colour("green");
      std::cout << "STREAK x" << streak << std::endl;
      set_colour("reset");
    }
  }

  void border_around_question () {
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

  void print_functionable_back_button(int width_left,int height) {
    //functional back mouse cllick button 
    move_cursor(width_left , height);
    set_colour("yellow");
    std::cout << ":{BACK}:" << std::endl;
    mouse_click_back_button (width_left,width_left+8,height);
    set_colour("reset");
    return ;
  }

  void resize_window() {
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

  void question_ui() {
      system("cls"); // clear the screen so new question can appear on same position
      generate_new_equation();
      print_question();
      print_lifes();
      print_score();
      solve_equation();
      generate_options();
      print_options();  
  }

  void answer_ui() {
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

  void play_game() {
  
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

  void rulebook() {
    system("cls");
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

   void check_high_score() {
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

   void print_menu() {
    get_terminal_size();
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
  
   }

   void print_difficulty() {
    get_terminal_size();
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
  
   }

   void main_menu () {
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

int main () {
  game_ui game;
  game.main_menu();
}