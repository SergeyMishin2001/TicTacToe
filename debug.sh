#!/bin/bash
# Debug script
# I cant do makefiles xd

g++ -c tictactoe.cpp # compilation

g++ tictactoe.o -o -W tictactoe -lsfml-graphics -lsfml-window -lsfml-system # linkage

# Make sure you have sfml libraries and modules installed


