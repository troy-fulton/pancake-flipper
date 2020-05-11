/*
CSCE 315 503
Project 3
Group 17

Abdul Campos
Marshall Hobbs
McLain Johnson
Troy Fulton

AI.h - Interface for the Artificial Intelligence Player class

The AI also has a helper class that inherits from it so that
when the AI needs to evaluate the tree, it can use a helper functor
which can make "imaginary" moves on its stack and put it right 
back to see the sortedness advatage of each sequence of moves.
*/

#ifndef __AI__        // For #including more than once
#define __AI__

/************************************************
 *  INCLUDES
 ***********************************************/
#include <iostream>
#include <map>
#include "Player.h"
#include "MMTree.h"
using namespace std;

/************************************************
 * Main Class
 ***********************************************/

class AI : public Player {
private:
    int difficulty;
    
public:
    // For the AI to decide under which pancake to flip:
    int calculateMove();
	int getDifficulty();
    AI(int num_pancakes, int* order, int diff);
};


// Functor for implementing the utility function
class Helper {
    AI ai;
public:
    Helper(AI ai_player);
    int operator()(vector<int> path);
};

#endif