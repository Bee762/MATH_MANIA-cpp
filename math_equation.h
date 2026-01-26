#ifndef MATH_EQUATION_H
#define MATH_EQUATION_H
#include "include.h"


class math_equation {
    
    public : 
    
    math_equation ();

    ~math_equation ();

    int str_to_int (std::string a);

    std::string int_to_str (int a);

    int generaterandomnumber(int min, int max);

    std::string random_operator ();

    std::string random_number ();

    void difficulty_scaling ();

    void generate_new_equation();

    void precedence_solving (bool& a , std::string_view b);

    void solve_equation ();


    protected :
    
    float previous_number = 0;   //making these float for division round off only
    float next_number = 0; //result will be rounded off to nearest int
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

#endif