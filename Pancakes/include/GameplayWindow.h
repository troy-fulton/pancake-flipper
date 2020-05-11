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

GameplayWindow.h - Interface for Gameplay Window methods for showing
                each pancake stack in the current state of the game
                and handling all the events of the game.
*/

#ifndef __GPLAY__        // For #including more than once
#define __GPLAY__

/************************************************
 *  INCLUDES
 ***********************************************/
#include "Game.h"
#include "Stack.h"

//#include <iostream>
#include <string>
#include <cstring>

#include <nana/gui/wvl.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/button.hpp>

/************************************************
 *  DEFINES
 ***********************************************/
#ifndef BLACK
#define BLACK color(0,0,0)
#endif
#ifndef GREEN
#define GREEN color_rgb(0x00FF00)
#endif
#ifndef RED
#define RED color_rgb(0xFF0000)
#endif
#define BUTTON_WID 100
#define BUTTON_HT 20
#define BUTTON_RECT rectangle(350, 500, BUTTON_WID, BUTTON_HT)
#define SCR_WIDTH 800
#define SCR_HEIGHT 600
#define PANCAKE_W_1 100
#define PANCAKE_H_1 50

/************************************************
 * Helper Classes
 ***********************************************/

using namespace std;
using namespace nana;

class FinishedWindow : public nana::form {
    /* Callbacks */
    void cb_done(const nana::arg_click & eventinfo);
    /* FLTK:
    static void cb_done(Address, Address);
    */

    void quit_win() { this->close(); };

    /* Members */
    label win_or_lose;
    /* FLTK:
    Text message;
    Button done_button;
    bool button_pushed;
    */

public:
    FinishedWindow(point p, nana::size s, string label);

    bool wait_for_button();
};

/************************************************
 * Main Class
 ***********************************************/

class GameplayWindow : public nana::form {
private:
    /* Callbacks */
    void cb_quit(const nana::arg_click & eventinfo);
    void cb_restart(const nana::arg_click & eventinfo);
    /* FLTK:
    static void cb_quit(Address, Address);
    static void cb_restart(Address, Address);
    static void cb_pancake1(Address, Address);
    static void cb_pancake2(Address, Address);
    static void cb_pancake3(Address, Address);
    static void cb_pancake4(Address, Address);
    static void cb_pancake5(Address, Address);
    static void cb_pancake6(Address, Address);
    static void cb_pancake7(Address, Address);
    static void cb_pancake8(Address, Address);
    static void cb_pancake9(Address, Address);
    // ...end callbacks
    */


    /* Helper Functions */
    void quit_win();
    void restart_win();
    void pancake_select();
    int getSelection() { return selected_pancake; };
    void put_spatula(int, int);
	void put_AI_spatula(int x, int y);
    void captions();
    void colors();
    void callbacks();
    
    /* Windows */
    
    /* Data members */
    Game* curr_game;
    Stack human_stack, ai_stack;
    bool button_pushed;
    bool quit_game = false;
    bool start_over = false;
    int selected_pancake; // from the top

    button restart_btn, 
        quit_btn;

    label you_text, ai_text, instructions, turn;

    /* FLTK
    Button quit_button, restart_button;
	Stack human_stack, ai_stack;
    Text you_text, ai_text, instructions;
    Line spatula;
	Line AI_spatula;
    */

public:
    /* Interface */
    bool wait_for_button();
    bool getQuit();
    bool getStartOver();

    /* Constructor */
    GameplayWindow(point p, nana::size s, string name, Game* cg);
};



#endif