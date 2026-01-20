#include <iostream>
#include <random>
#include <string>

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

    for (int i = 0;i < total_row;i++) {

       if (equation[i] == "empty") continue;

       if (equation[i] == b) {
         a = true;
        for (int x = i-1; x >= 0;x--) {
         if (equation[x] == "empty") continue;
         previous_number = str_to_int (equation[x]);
         equation[x] = "empty";
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
        else if (b == "+") result = previous_number+next_number;
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

    int solve_equation () {
    precedence_solving(divide_op_present,"/");
    precedence_solving(multiply_op_present,"*");
    precedence_solving(addition_op_present,"+");
    precedence_solving(subtraction_op_present,"-");

     int answer = 0;

     for (int i = 0; i < total_row; i++) {
       if (equation[i] != "empty") {
        answer = str_to_int(equation[i]);
        std::cout << std::endl;
        std::cout << answer;
        break;
       }
      }
     return answer;
    }


    protected :
    int previous_number = 0;
    int next_number = 0; 

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

    std::mt19937 gen{std::random_device{}()}; //random number generator engine

};

int main () {
    math_equation eq1;
    eq1.solve_equation();
}