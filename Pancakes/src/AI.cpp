/*
CSCE 315 503
Project 3
Group 17

Abdul Campos
Marshall Hobbs
McLain Johnson
Troy Fulton

AI.cpp - AI implementation for calculating the next move
*/

#include "AI.h"
using namespace std;

AI::AI(int num_pancakes, int* order, int diff) :
    Player(num_pancakes, order), difficulty(diff) {}

int AI::calculateMove() {
    Helper h(*this);
    MMTree<Helper> mmt(h, difficulty, stack_size);
    //mmt.print();
    return mmt.bestMove();
}

// Utility function for the minimax tree:
int Helper::operator()(vector<int> path) {
    // Get initial sortedness
    int init_sortedness = ai.getSortedness();
    
    // Do all the flips in order
    for (int move : path) {
        ai.makeMove(move);
    }

    // Get the sortedness difference
    int original_score = ai.getSortedness();
    
    int score = original_score - init_sortedness;

    // Put the stack back where you found it (do the flips in reverse order)
    for (int i = path.size() - 1; i >= 0; i--) {
        ai.makeMove(path[i]);
    }
    
    if (original_score == 0) {       // signal for game-ending score
        return -10;
    }
    
    return score;
}

Helper::Helper(AI ai_player) : ai(ai_player) {}

int AI::getDifficulty()
{
	return this->difficulty;
}
