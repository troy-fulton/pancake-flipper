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

GraphicsEngine.h - Interface for Engine methods for running the game and
        keeping track of which game the user is on. Calls methods from various 
        other screens and instantiates them when necessary.
*/

#ifndef __GRAPHICS__        // For #including more than once
#define __GRAPHICS__

/************************************************
 *  INCLUDES
 ***********************************************/
#include "InstructionsWindow.h"
#include "GameOptionsWindow.h"
#include "GameStackOrderWindow.h"
#include "GameplayWindow.h"
#include "ScoresWindow.h"
#include "Game.h"

#include <iostream>
#include <vector>
#include <string>
#include <cstring>

#include <nana/gui/wvl.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/picture.hpp>

/************************************************
 *  DEFINES
 ***********************************************/
#define SCR_WIDTH 800
#define SCR_HEIGHT 600
#define SCR_SIZE nana::size(SCR_WIDTH, SCR_HEIGHT)
#define SCR_POINT point(100, 100)
#define SCR_RECT rectangle(SCR_POINT, SCR_SIZE)
#define TITLE_X SCR_WIDTH/2 - 70
#define TITLE_Y 150
#define NAMES_X SCR_WIDTH/2 - 50
#define NAMES_Y 200
#define PLAY_RECT rectangle(SCR_WIDTH/2 - 50,350,100,15)
#define INST_RECT rectangle(SCR_WIDTH/2 - 50,380,100,15)
#define QUIT_RECT rectangle(SCR_WIDTH/2 - 50,410,100,15)
#define PIC_RECT rectangle(SCR_WIDTH/2 - 25,100,50,40)

/************************************************
 * Main Class
 ***********************************************/

using namespace nana;
using namespace std;

class GraphicsEngine : public nana::form {
private:
    Game* curr_game;

    /* Callbacks */
    void cb_play(const nana::arg_click & eventinfo);
    void cb_inst(const nana::arg_click & eventinfo);
/* FLTK:
    static void cb_play(Address, Address);
    static void cb_instructions(Address, Address);
    static void cb_quit(Address, Address);
*/

    /* Helper Functions */
    string create_name_string();
    bool game_sequence();

/* FLTK:
    void quit_win();
    void play_win();
    void instructions_win();
*/

    /* Variables used for the Splash Screen */
    bool button_pushed;
    label title, ret;
    button play_btn, inst_btn, quit_btn;
    picture pancake_img;
/* FLTK:
    Point img_pos;
    Point title_pos;
    Point sub_title_pos;
    Point names_pos;
    Text title;
    Text sub_title;
    Button button_play;
    Button button_instr;
    Button button_qt;
*/
    vector<string> names = {
        "Sournav Bhattacharya",
        "Conner Brewster",
        "Troy Fulton",
        "Zheng Fang",
        "Abdul Quintanilla",
        "Chris Garza"
    };

public:

    // Constructor / Destructor
    /* FLTK:
    GraphicsEngine(Point p, int w, int h, string name);
    */
    GraphicsEngine(string name);
    ~GraphicsEngine();
    bool wait_for_button();

    // Function for drawing the splash screen
    /* FLTK:
    void drawSplashScreen();
    bool runGame();
    */

   // For running the game and facilitating gameplay
    vector<string> getScores();
    void startGame(int num_pancakes, int ai_difficulty, string fn, int* starting_order);
};



#endif