#!/bin/bash
# Debug script

g++ -c tictactoe.cpp # compilation

g++ tictactoe.o -o -O2 tictactoe -lsfml-graphics -lsfml-window -lsfml-system # linkage

# Make sure you have sfml libraries and modules installed


