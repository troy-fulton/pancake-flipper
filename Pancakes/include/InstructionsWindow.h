/*
CSCE 315 503
Project 4
Group 12

Abdul Campos
Troy Fulton
...

ScoresWindow.h - Interface for the Scores Window
*/

#ifndef __INSTRUCTIONS__        // For #including more than once
#define __INSTRUCTIONS__

/************************************************
 *  INCLUDES
 ***********************************************/
#include "Stack.h"

#include <iostream>
#include <string>
#include <cstring>

#include <nana/gui/wvl.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/picture.hpp>

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

/************************************************
 * Main Class
 ***********************************************/

using namespace std;
using namespace nana;

class InstructionsWindow : public nana::form {
private:
    /* Callbacks */
    void cb_done(const nana::arg_click & eventinfo);
/* FLTK:
    static void cb_done(Address, Address);
*/

    /* Helper Functions */
    void set_colors();
    void set_captions();
    /* FLTK:
    void quit_win();
    */
    
    /* Windows */
    
    /* Data members */
    bool button_pushed = false;

    string hello = "HELLO";

    string instructions_strings[10] = {
        "You and an Artificial Intelligence player will be given two versions",
        "of the same stack of pancakes. Your goal is to sort the pancakes",
        "from top to bottom (meaning the smallest pancake will be on the top",
        "and the largest on bottom).",
        "To do this, you will insert a spatula under any of the pancakes",
        "in the (left) stack by clicking under the pancake. This 'flips' the",
        "pancakes at and above that pancake. The spatula will show which",
        "pancakes will be flipped and the pancakes will blink before flipping.",
        "",
        "Here is an example pancake of size 6:"
    };

    button continue_button;
    label instructions_title;
    label inst1, inst2, inst3,
            inst4, inst5, inst6,
            inst7, inst8, inst9, 
            inst10;
	Pancake* pan;
	picture flipper_img;
    
    //picture sample_pancake;

public:
    /* Interface */
    bool wait_for_button();

    /* Constructor */
    InstructionsWindow(point p, nana::size s, string name);
};



#endif