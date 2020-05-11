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

GameOptionsWindow.h - Interface for Game Options Window that prompts the
        user for the level of difficulty of the AI and details about the
		stack of pancakes used to play the game.
*/

#include "GameOptionsWindow.h"
#include <boost/algorithm/string.hpp>

/*****************************************************
 * PRIVATE / PROTECTED METHODS
 ****************************************************/

void GameOptionsWindow::submit_event() {
	/* FLTK:
	num_pan = in_num_pan.get_int();
	dif_level = in_dif.get_int();
	*/	
	string pan_string, dif_string;
	in_num_pan.getline(0, pan_string);
	in_dif.getline(0, dif_string);
	num_pan = atoi(pan_string.c_str());
	dif_level = atoi(dif_string.c_str());
	
	bool num_pan_ok = true;
	bool difficulty_ok = true;
	if(num_pan<2 || num_pan>9){
		/* FLTK:
		num_pan_label.set_color(FL_RED);
		redraw();
		*/
		num_pan_label.fgcolor(RED);
		num_pan_ok = false;
	}
	else{
		/* FLTK:
		num_pan_label.set_color(FL_GREEN);
		redraw();
		*/
		num_pan_label.fgcolor(GREEN);
	}
	if(dif_level<1){
		/* FLTK:
		dif_label.set_color(FL_RED);
		redraw();
		*/
		dif_label.fgcolor(RED);
		difficulty_ok = false;
	}
	else if(dif_level > num_pan || (dif_level > 9 && num_pan<0)){
		/* FLTK:
		dif_label.set_color(FL_RED);
		redraw();
		*/
		dif_label.fgcolor(RED);
		difficulty_ok = false;
	}
	else{
		/* FLTK:
		dif_label.set_color(FL_GREEN);
		redraw();
		*/
		num_pan_label.fgcolor(GREEN);
	}
	/* FLTK:
    button_pushed = num_pan_ok && difficulty_ok;
	*/
	if (num_pan && difficulty_ok) this->close();
}

void GameOptionsWindow::cb_submit(const nana::arg_click & eventinfo) {
    submit_event();
}

/*****************************************************
 * PUBLIC METHODS
 ****************************************************/

/* Default Constructor creates a dummy game with the file name so it can get scores */
GameOptionsWindow::GameOptionsWindow(point p, nana::size s, string name):
    form(rectangle(p, s)),
	submit_button(*this, rectangle(350, 340, 100, 30), true),
	in_num_pan(*this, rectangle(450, 230, 20, 20), true),
	in_dif(*this, rectangle(450, 290, 20, 20), true),
	num_pan_label(*this, rectangle(285, 235, 150, 20)),
	dif_label(*this, rectangle(285, 295, 150, 20))
	/* FLTK:
    Window(p, width, height, name), 
	submit_button(Point(400,340), 100, 30, "Submit", cb_submit),
	in_num_pan(Point(450,240),40,30,""),
	in_dif(Point(450,300),40,30,""),
	num_pan_label(Point(285,260),"Number Of Pancakes"),
	dif_label(Point(326,320),"Difficulty Level")
	*/
	{
		/* Captions */
		num_pan_label.caption("Number of Pancakes");
		dif_label.caption("Difficulty Level");
		submit_button.caption("Submit");

		/* Colors */
		this->bgcolor(BLACK);
		in_num_pan.fgcolor(GREEN); in_num_pan.bgcolor(BLACK);
		in_dif.fgcolor(GREEN); in_dif.bgcolor(BLACK);
		num_pan_label.fgcolor(GREEN); num_pan_label.bgcolor(BLACK);
		dif_label.fgcolor(GREEN); dif_label.bgcolor(BLACK);

        submit_button.events().click(
            [this](const nana::arg_click& ei){cb_submit(ei);}
        );

		/* FLTK:
		color(FL_BLACK);
		num_pan_label.set_color(FL_GREEN);
		dif_label.set_color(FL_GREEN);
		attach(num_pan_label);
		attach(dif_label);
		attach(in_num_pan);
		attach(in_dif);
		attach(submit_button);
		*/
}

bool GameOptionsWindow::wait_for_button() {
    this->show();
    this->wait_for_this();
    return true;
}