/*
CSCE 315 503
Project 3
Group 17

Abdul Campos
Marshall Hobbs
McLain Johnson
Troy Fulton

Player.cpp - Implementations for Player class (making moves, returning the stack, etc.)
*/

#include "Player.h"

Player::Player(int num_pancakes, int* order) :
    stack(order), stack_size(num_pancakes)  {}

int* Player::getStack() {
    return stack;
}

int Player::getStackSize() {
    return stack_size;
}

void Player::swapPancakes(int i, int j) {
    int temp_pancake = stack[i];
    stack[i] = stack[j];
    stack[j] = temp_pancake;
}

void Player::makeMove(int pancake) {
    // Count of pancakes at and above spatula
    int pancakes_to_flip = (stack_size - pancake)/2;

    // If we need to look at more than one
    if (pancakes_to_flip >= 1) {
        if (pancakes_to_flip > 2) pancakes_to_flip+= 2;
        // For each of the pancakes above the spatula
        for (int i = pancake; i < (pancake+1) + (pancakes_to_flip/2); i++) {
            swapPancakes(i, stack_size - i + pancake - 1);
        }
    }

    return;
}



int Player::getSortedness() {
    // Array of ls and gs for less than and greater than
    char* comparators = new char[stack_size];
    comparators[0] = 'g';

    for (int i = 0; i < stack_size - 1; i++) {
        if (stack[i] < stack[i+1])
            comparators[i+1] = 'l';
        else
            comparators[i+1] = 'g';
    }

    // Count the changes in sign from left to right
    int count = 0;
    for (int i = 0; i < stack_size - 1; i++)
        if (comparators[i] != comparators[i+1])
            count++;

    delete[] comparators;

    return count;
}
/*
Player::~Player() {
    delete[] stack;
}
*/