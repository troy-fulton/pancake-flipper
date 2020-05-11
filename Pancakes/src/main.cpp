/*
CSCE 315 503
Project 4
Group 12

Abdul Campos
Troy Fulton
Zehng Fang
Conner Brewster
Sournav Bhattacharya
Chris Garza

main.cpp - Program entry point for calling exec and exiting
            to another process
*/

/************************************************
 *  INCLUDES
 ***********************************************/
#include <string>

#include "GraphicsEngine.h"

/************************************************
 *  DEFINES
 ***********************************************/
#define DIFF_SIZE 2

using namespace std;
using namespace nana;

int main() {

    // Instantiate the whole thing
    /* FLTK:
    GraphicsEngine ge(SCR_LOC, SCR_WIDTH, SCR_HEIGHT, "Pancake Game");
    */
    GraphicsEngine ge("Pancake Game");
    ge.wait_for_button();

    exec();

    // Never executed...
}