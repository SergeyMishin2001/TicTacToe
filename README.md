TicTacToe written in C++ and SFML. Was bored so thought this might be a good practice.
In case you care, there is a shell script for easier building.
Please point out known bugs or code simplifications, i've decide to stay with OOP since it's a lot more readable
than C-style code, but i could have made it more complex than i supposed to.

Requirements:
  1) latest SFML version
  2) g++ compiler
  3) bash (not neccessary)
  
How to build from source on linux:
  1) Make sure you have a proper SFML library for g++ compiler downloaded and installed to a standard path.
     If you have it on a different path, then add "-I path/SFML/include" to build.sh at compilation line
     and "-L path/SFML/lib" to linkage line
  2) Run ./build.sh
  3) Run ./tictactoe
  
  
