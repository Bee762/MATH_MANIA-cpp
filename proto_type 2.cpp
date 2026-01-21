#include <iostream>
#include <random>
#include <string>
#include <windows.h>
#include <conio.h>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <atomic>


class math_equation {
    
    public : 

    math_equation () {
    // initialising the array as empty
    for (int i = 0;  i < total_row ; i++) {
        equation [i] = "empty";
        }

    // filling in with data
    for (int i = 0; i < total_row ; i++) {
    if (i % 2 == 0) {
    equation [i] = random_number(); //put a number in odd position 
    std::cout << equation [i]; 
       }
    else {
    equation[i] = random_operator(); // put a operator in even position
    std::cout << equation [i]; // print the equation;
       }
      } 
      std::cout << std::endl;
      // so equation will look number op number op number like this
     }

     ~math_equation () {

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

    void generate_new_equation() {
      //empty existing  array
      for (int i = 0;  i < total_row ; i++) {
        equation [i] = "empty";
        }

    // filling in with data
    for (int i = 0; i < total_row ; i++) {
    if (i % 2 == 0) {
    equation [i] = random_number();
    std::cout << equation [i]; 
       }
    else {
    equation[i] = random_operator();
    std::cout << equation [i]; 
       }
      } 
      std::cout << std::endl;

      // reseting the variables

     divide_op_present = true;
     multiply_op_present = true;
     addition_op_present = true;
     subtraction_op_present = true;
     answer = 0;

    }


    protected :
    int previous_number = 0;
    int next_number = 0; 
    int answer = 0;

    static constexpr int number = 4;
    static constexpr int op = number-1;
    static constexpr int total_row = number+op;
    std::string equation [total_row] ;
    // to asign this array,its lenth must be known at compile time
    // so we are  using static (means only one copy of the var for all objs of this class ) and 
    //constexpr (means value is known at compile time)

    bool divide_op_present = true;
    bool multiply_op_present = true;
    bool addition_op_present = true;
    bool subtraction_op_present = true;
    std::string previous_op = "empty";

   std::mt19937 gen{std::random_device{}()}; //random number generator engine

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

  void print_options () {
    std::cout << option_1 <<  "    " << option_2 << std::endl;
    std::cout << option_3 <<  "    " << option_4 << std::endl;
  }

  char get_input () {
    if (!_kbhit()) return 0;
    return _getch();
  }

  void handle_input () {
    join_thread = false;
    while (!join_thread) {
      char key = 0;
    while ((key = get_input()) == 0) {
       key = get_input();
       if (join_thread) break;
       std::this_thread::sleep_for(std::chrono::milliseconds(50));
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

    else if (key == 0) {}
    else  {std::cout << " NOT A VALID OPTION " << std::endl;}
  }
}

  void update_score() {
    if (user_answer == answer) {
      score++;
      std::cout << "CORRECT-ANSWER! " << std::endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
      std::cout << "SCORE : " << score << std::endl;
    }
    else {
    std::cout << "WRONG-ANSWER! " << std::endl;
     std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "SCORE : " << score << std::endl;
    }
  }


  void timer () {
    for (int i = 0; i <= time_duration_sec; i++ ) {
      if (join_thread == true) break;
      std::this_thread::sleep_for(std::chrono::seconds(1));
      if (i == time_duration_sec) {std::cout << "[TIME-UP!]" << std::endl;}
    }
    join_thread = true;
  }

  void game_loop () {
    while (true) {
      solve_equation();
      generate_options();
      print_options();
      std::thread t1(&game_state::handle_input, this);//because handle input or timer are not independent global func
      //the are functions of this obj i cant use them directly,here we basically say handle input is a func
      // for game_state  class and call it for current obj using this pointer
      std::thread t2 (&game_state::timer,this);
      t1.join();
      t2.join();
      update_score();
      system("cls");   // clear the screen so new question can appear on same position
      generate_new_equation();
    }
  }

  protected :  
  int user_answer = 0;
  int score = 0;
  int option_1 = 0;
  int option_2 = 0;
  int option_3 = 0;
  int option_4 = 0;
  std::atomic<bool> join_thread = false; // using this in 2 func , handle input and timer
  //to avoid race condition using atomic boool
  int time_duration_sec = 15; // time limit for each question on screen
};

int main () {
  game_state play_game;
  play_game.game_loop();
}