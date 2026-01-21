#include <iostream>
#include <random>
#include <string>
#include <windows.h>
#include <conio.h>
#include <chrono>
#include <thread>
#include <cstdlib>

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
    equation [i] = random_number();
    std::cout << equation [i]; 
       }
    else {
    equation[i] = random_operator();
    std::cout << equation [i]; 
       }
      } 
      std::cout << std::endl;
     }

     ~math_equation () {

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

    int str_to_int (std::string a) {
    int x = std::stoi(a);
    return x;
    }

    std::string int_to_str (int a) {
    return std::to_string (a);
    }

    void precedence_solving (bool& a , std::string_view b) {
    while (a == true) {
    	previous_op = "empty";

    for (int i = 0;i < total_row;i++) {

       if (equation[i] == "empty") continue;

       if (equation[i] == b) {
         a = true;
        for (int x = i-1; x >= 0;x--) {
         if (equation[x] == "empty") continue;
         previous_number = str_to_int (equation[x]);
         equation[x] = "empty";
         
        if (b== "+" || b== "-") {
          	for (int i = x-1 ; i >= 0 ; i--) {
              if (equation[i] == "empty") continue;
            else if (equation[i] != "empty" && equation[i] != "-") break;
            else if (equation[i] == "-")
          	previous_op = equation [i];
          	equation[i] = "empty";
          	   break;
          	    }	          	
          }    
         break;
        }

        for (int x = i+1; x < total_row ; x++) {
         if (equation[x] == "empty") continue;
         next_number = str_to_int (equation [x]);
         equation[x] = "empty";
         break;
        }

        int result = 0;
        if (b == "/") result = previous_number/next_number;
        else if (b == "*") result = previous_number*next_number;
        else if (b == "+" && previous_op == "-") { int temporary_result = -previous_number +next_number;
        if (temporary_result < 0) {
        equation [i-1] = "-";}
        else if (temporary_result > 0) {
        	equation [i-1] = "+";}
        result = std::abs(temporary_result);}
        else if (b == "+") result = previous_number+next_number;
        else if (b == "-" && previous_op == "-") { int temporary_result = -previous_number - next_number;
            if (temporary_result < 0) {
        equation [i-1] = "-";}
        else if (temporary_result > 0) {
        	equation [i-1] = "+";}
        result = std::abs(temporary_result);}
        else if (b == "-") result = previous_number-next_number;

        equation [i] = int_to_str(result);
        break;
        }

        else {
        a = false;
        }
       }//for loop

     }//while loop

    }//function end

    void solve_equation () {
    precedence_solving(divide_op_present,"/");
    precedence_solving(multiply_op_present,"*");
    precedence_solving(addition_op_present,"+");
    precedence_solving(subtraction_op_present,"-");

     for (int i = 0; i < total_row; i++) {
       if (equation[i] != "empty") {
        answer = str_to_int(equation[i]);
        break;
       }
      }
    }

    void generate_new_equation() {
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
    while (true) {
      char key = 0;
    while ((key = get_input()) == 0) {
       key = get_input();
       std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    if (key == '1') {user_answer = option_1;
                         break;}
    else if (key == '2') {user_answer = option_2;
                         break;}
    else if (key == '3') {user_answer = option_3;
                         break;}
    else if (key == '4') {user_answer = option_4;
                         break;}
    else {std::cout << " NOT A VALID OPTION " << std::endl;}
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
  }

  void update_score() {
    if (user_answer == answer) {
      score++;
      std::cout << "CORRECT-ANSWER! " << std::endl;
      std::cout << "SCORE : " << score << std::endl;
    }
    else {
    std::cout << "WRONG-ANSWER! " << std::endl;
    std::cout << "SCORE : " << score << std::endl;
    }
  }

  void game_loop () {
    while (true) {
      solve_equation();
      generate_options();
      print_options();
      handle_input();
      update_score();
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
};

int main () {
  game_state play_game;
  play_game.game_loop();
}