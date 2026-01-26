  #include "include.h"
  #include "math_equation.h"
    
     //equation is used in raII method,created in constructor and deleted in destructos,so its memory safe
     //i want dynamic difficulty scaling meaning user should be able to alter difficulty from within
      //the obj,but i also want my dynamic question array to be created at constructor i cant do that normally
      // here is what i thought as solution :
      //as i cant modify the size of the array after obj creation
      //i will generate the maximum size of array user can that will be 6 number 5 operator,
      // and if user chooses easy or medium difficulty i will mark the remaining slot with placeholder
      //that my algotythm already ignores
    math_equation::math_equation () {
      equation = new std::string [max_row];
    }

    math_equation::~math_equation () {
      delete[] equation;
      equation = nullptr;
    }

    int math_equation:: str_to_int (std::string a) {
    int x = std::stoi(a);
    return x;
    }

    std::string math_equation:: int_to_str (int a) {
    return std::to_string (a);
    }

    int math_equation:: generaterandomnumber(int min, int max) {
    std::uniform_int_distribution<> dist(min, max); // Uniform distribution
    return dist(gen);// Generate and return random number
    }

    std::string math_equation:: random_operator () {
    int a = generaterandomnumber (1,4);
    if (a == 1) return "+";
    if (a == 2) return "-";
    if (a == 3) return "*";
    if (a == 4) return "/";
      return "0";
    }

    std::string math_equation:: random_number () {
    int a = generaterandomnumber(1,9);
    std::string random_num = int_to_str (a);
    return random_num;
    }

    void math_equation:: difficulty_scaling () {

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
    void math_equation:: generate_new_equation() {

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

    void math_equation:: precedence_solving (bool& a , std::string_view b) {
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

         if (b == "/") {
          float temporary_result = previous_number/next_number; //store result as a temporary float tp keep decimals
          result = std::round(temporary_result);    //then round it off to nearest int 
         }
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

    void math_equation:: solve_equation () {
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
