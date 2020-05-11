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

#ifndef __OPTIONS__        // For #including more than once
#define __OPTIONS__

/************************************************
 *  INCLUDES
 ***********************************************/
//#include <iostream>
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

class GameOptionsWindow : public nana::form {
private:
    /* Callbacks */
	void cb_submit(const nana::arg_click & eventinfo);
	/* FLTK:
	static void cb_submit(Address, Address);
	*/

    /* Helper Functions */
	void submit_event();

    /* Windows */
    
    /* Data members */
	/* FLTK:
	bool button_pushed = false;
	Button submit_button;
	In_box in_num_pan;
	In_box in_dif;
	Text num_pan_label;
	Text dif_label;
	*/
	button submit_button;
	textbox in_num_pan;
	textbox in_dif;
	label num_pan_label,
		dif_label;
	int num_pan;
	int dif_level;
	
public:
    /* Constructor */
    GameOptionsWindow(point p, nana::size s, string name);

    /* Interface */
	bool wait_for_button();
	int get_num_pan(){
		return num_pan;
	}
	int get_dif_level(){
		return dif_level;
	}
};



#endif