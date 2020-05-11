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

GameOptionsWindow.cpp - Implementations for Game Options Window that prompts the
        user for the level of difficulty of the AI and details about the
		stack of pancakes used to play the game.
*/

#ifndef __SCORES__        // For #including more than once
#define __SCORES__

/************************************************
 *  INCLUDES
 ***********************************************/
#include <iostream>
#include <string>
#include <nana/gui/wvl.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/textbox.hpp>

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
#ifndef WHITE
#define WHITE color_rgb(0xFFFFFF)
#endif

/************************************************
 * Main Class
 ***********************************************/

using namespace nana;
using namespace std;

class ScoresWindow : public nana::form {
private:
    /* Callbacks */
    void cb_done(const nana::arg_click & eventinfo);
    void cb_new_game(const nana::arg_click & eventinfo);
    void cb_main_menu(const nana::arg_click & eventinfo);
    /* FLTK:
    static void cb_done(Address, Address);
    static void cb_new_game(Address, Address);
    static void cb_main_menu(Address, Address);
    */

    /* Helper Functions */
    void quit_win();
    void restart_win();
    void main_win();
    // FLTK: void do_attaches();
    void set_colors();
    void set_labels();

    /* Windows */
    
    /* Data members */
    vector<string> scores;
    // FLTK: bool button_pushed;
    bool is_beginning;
    int player_score;

    string player_name;
    bool is_new_game;

    button done_button;
    textbox in_initials;
    label enter_initials, scores_title;
    label score1, score2, score3, score4, score5;
    label your_score_prompt, your_score;
    button new_game, main_menu;

    /* FLTK:
    Button done_button;
    In_box in_initials;
    Text enter_initials, scores_title;
    Text score1, score2, score3, score4, score5;
    Text your_score_prompt, your_score;
    Button new_game, main_menu;
    */

public:
    /* Interface */
    bool wait_for_button();
    string getPlayerName();
    bool getNewGame();

    /* Constructor */
    ScoresWindow(point p, nana::size, string name, vector<string> strs, int ps, bool ib);
};



#endif