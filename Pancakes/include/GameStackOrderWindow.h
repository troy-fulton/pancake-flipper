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

#ifndef __ORDER__        // For #including more than once
#define __ORDER__

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

class GameStackOrderWindow : public nana::form {
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
	int* splitUserInput(string userIn);
	/* FLTK:
	bool button_pushed = false;
	Button submit_button;
	In_box in_order;
	Text order_label;
	*/
	button submit_button;
	textbox in_order;
	label order_label;
	int* stackOrder;
	int numPancakes;
	
public:
    /* Interface */
	bool wait_for_button();
	int* getStackOrder(){
		return stackOrder;
	}
	int getNumPancakes()
	{
		return numPancakes;
	}
    /* Constructor */
    GameStackOrderWindow(point p, nana::size s, string name, int numpan);
};



#endif