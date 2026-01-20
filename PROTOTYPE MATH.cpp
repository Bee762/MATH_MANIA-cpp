#include <iostream>
#include <random>
int previous_number = 0;
int next_number = 0;
int generaterandomnumber(int min, int max) {
    std::random_device rd;  // Seed generator
    std::mt19937 gen(rd()); // Mersenne Twister engine
    std::uniform_int_distribution<> dist(min, max); // Uniform distribution
    return dist(gen);// Generate and return random number
}
    char random_operator () {
    int a = generaterandomnumber (1,4);
    if (a == 1) return '+';
    if (a == 2) return '-';
    if (a == 3) return '*';
    if (a == 4) return '/';
      return 0;
    }
    char random_number () {
    int a = generaterandomnumber(1,9);
    char random_num  = a + '0';
    return random_num;
    }

    int str_to_int (std::string a) {
        int x = std::stoi(a);
        return x;
    }
    std::string int_to_str (int a) {
        return std::to_string (a);
    }

int main () {
    int number = 4;
    int op = number-1;
    int total_row = number+op;

    std::string equation [total_row] ;

    for (int i = 0; i < total_row ; i++) {
            if (i % 2 == 0) {
            equation [i] = random_number();
            std::cout << equation [i]; 
            }
            else {
            equation[i] = random_operator();
            std::cout << equation [i]; 
            }
    } // for i

    //solving the equation : 
    while (true) {

        bool divide_op_present = true;
        bool multiply_op_present = true;
        bool addition_op_present = true;
        bool subtraction_op_present = true;

    while (divide_op_present == true) {

    for (int i = 0;i < total_row;i++) {

       if (equation[i] == "empty") continue;

       if (equation[i] == "/") {
        divide_op_present = true;
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

        int result = previous_number/next_number;
        equation [i] = int_to_str(result);
        break;
       }

       else {
        divide_op_present = false;
       }
    }

}

while (multiply_op_present == true) {

    for (int i = 0;i < total_row;i++) {

       if (equation[i] == "empty") continue;

       if (equation[i] == "*") {
        multiply_op_present = true;
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

        int result = previous_number*next_number;
        equation [i] = int_to_str(result);
        break;
       }

       else {
        multiply_op_present = false;
       }
    }

}

while (addition_op_present == true) {

    for (int i = 0;i < total_row;i++) {

       if (equation[i] == "empty") continue;

       if (equation[i] == "+") {
        addition_op_present = true;
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

        int result = previous_number+next_number;
        equation [i] = int_to_str(result);
        break;
       }

       else {
        addition_op_present = false;
       }
    }

}

while (subtraction_op_present == true) {

    for (int i = 0;i < total_row;i++) {

       if (equation[i] == "empty") continue;

       if (equation[i] == "-") {
        subtraction_op_present = true;
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

        int result = previous_number-next_number;
        equation [i] = int_to_str(result);
        break;
       }

       else {
        subtraction_op_present = false;
       }
    }

}
break;
}//equation loop
 std::cout << std::endl;
for (int i = 0; i < total_row; i++) {
    if (equation[i] != "empty")
        std::cout << equation[i];
}
}
