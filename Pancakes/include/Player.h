/*
CSCE 315 503
Project 3
Group 17

Abdul Campos
Marshall Hobbs
McLain Johnson
Troy Fulton

Player.h - Interface for the Player class
*/

#ifndef __PLAYER__        // For #including more than once
#define __PLAYER__

/************************************************
 *  INCLUDES
 ***********************************************/
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <algorithm>
#include <random>
#include <chrono>
#include <array>
//#include <unistd.h>
#include <vector>
#include "MMTree.h"

/************************************************
 * Main Class
 ***********************************************/

class Player {
protected:
    int *stack;         // Pancake Stack size
    int stack_size;     // Number of Pancakes

    void swapPancakes(int i, int j);

public:
    int* getStack();
    int getStackSize();
    void makeMove(int pancake);     // Same "flipping" action for all players
    int getSortedness();

    Player(int num_pancakes, int* order);
    //~Player();
};

#endif
