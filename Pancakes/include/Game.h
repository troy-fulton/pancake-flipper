/*
CSCE 315 503
Project 3
Group 17
Abdul Campos
Marshall Hobbs
McLain Johnson
Troy Fulton
Game.h - Interface for the Game class
*/

#ifndef __GAME__        // For #including more than once
#define __GAME__

/************************************************
 *  INCLUDES
 ***********************************************/
#include <iostream>
#include "Player.h"
#include "AI.h"

/************************************************
 * Main Class
 ***********************************************/

class Game {
private:

    Player human;
    AI ai;
    string filename;

    int human_score;
    int stack_size;     // new

    // To check if a stack is in order (for checkWin and generateStack)
    bool checkStackOrder(int *stack, int size);
    void sortInsertScore(string scores[5][2]);
public:
    string username;
    // For starting the game:
    Game(int num_pancakes, int ai_difficulty, string fn, int* starting_order);
    ~Game();
    int* generateStack(int stackSize, string stackState, bool test);
    int getDifficulty();
    int getScore();
    // For getting the state of each stack before and after each move:
    int* getHumanStack();
    int* getAIStack();
    int getStackSize();
    int getAIMove();         // For getting the result of AI.calculateMove()

    // For gameplay loop:
    void moveHuman(int pancake);
    void moveAI(int pancake);

    bool checkWin();

    // For when the game is over:
    int computeScore(int diff, int n, int* userS, int* aiS);
    string getHighScores();

	// For dealing with the high scores file
	  void writeScore();
    int* gen_rand_stack(int stackSize);
    vector<string> stackToString(int* stack, int stackSize);
};

#endif
