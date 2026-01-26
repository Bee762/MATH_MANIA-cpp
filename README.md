## M@TH-MANIA 

Truly random math equation generator with timelimit for solving and score tracking and added difficulty
In c++ terminal ,no external framework.
Other game related stuffs are in game rulebook,read it before playing.

## FEATURES OF THIS PROJECT : 

* Truly random number and mathematical operator generation and forming a equation.
* Solving the equation with precedence (division>>multiplication>>addition>>subtraction).
* Unary minus (negative number) is detected correctly and is accounted for in result calculations.
* Storing the result internally,and getting user answer asynchronusly(non-blocking input).
* Dynamic window resizing.
* Multithreading (1 thread for timelimit,1 thread for user input (answer) and 1 thread for window resizing).
* Atomic bool to avoid race conditions (thread safety).
* score tracking.
* PLayer Heart tracking (life system).
* Correct answer streak tracking and rewarding user based on streak.
* Mouse input enabled in main menu , but in game only keyboard inputs are allowed.
* Tracking and saving high score as a .txt file (I/O management).
* Colours in terminal using ansi escape sequence.
* Dynamic difficulty scaling (player can choose difficulty before game starts).
* Interactive console ui.
* and many more :)

## CONCEPTS USED :

* c++
* object oriented programming.
* Custom made algorithm for precedence solving.

## GAMEPLAY SCREENSHOTS :

* <img width="1481" height="761" alt="Screenshot 26-01-2026 14_12_58" src="https://github.com/user-attachments/assets/b90c25b8-fe36-4481-aaff-93b58585398c" />
* <img width="1481" height="761" alt="Screenshot 26-01-2026 14_13_01" src="https://github.com/user-attachments/assets/f96009e5-3664-446c-95fd-5a5494eb2ce1" />
* <img width="1481" height="761" alt="Screenshot 26-01-2026 14_13_11" src="https://github.com/user-attachments/assets/02be5644-10ec-4ea7-8409-96b26d0d596e" />
* <img width="1481" height="761" alt="Screenshot 26-01-2026 14_13_16" src="https://github.com/user-attachments/assets/ea8ccd25-0f80-4941-9131-b4852f7f92d0" />
* <img width="1481" height="761" alt="Screenshot 26-01-2026 14_13_26" src="https://github.com/user-attachments/assets/9adfc76a-e7fb-489f-a814-371abc68527f" />
* <img width="1481" height="761" alt="Screenshot 26-01-2026 14_13_05" src="https://github.com/user-attachments/assets/de02a6b5-1332-40d8-a8d8-4aa8477794d4" />

## ABOUT DEVELOPER : 

Hello , My name is Rohan Deb.I am from India and currently pursuing my B.tech Computer Science degree .
I am currently in First year and am learning c++.THis project was built to practice oop and other c++
fundamentals and thats why i didnot use any game engine or any other framework.
If you like this project ,let me know at :
rohanden232@gmail.com
   ~~Thank you :>

## HOW TO COMPILE AND RUN : 

*keep all source file in same folder ,then compile and run.
 
using g++ (minGW / GCC)
```bash
g++ *.cpp -o math_mania.exe
./math_mania.exe
