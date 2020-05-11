/*
CSCE 315 503
Project 4
Group 12

Abdul Campos
Troy Fulton
...

ScoresWindow.cpp - Implementations for Window to display scores...
*/

#include "GameStackOrderWindow.h"
#include <boost/algorithm/string.hpp>

/*****************************************************
 * PRIVATE / PROTECTED METHODS
 ****************************************************/
int* GameStackOrderWindow::splitUserInput(string userIn)
{
	vector<string> pancakes;
	boost::split(pancakes,userIn, [](char c){return c == ',';});
	stackOrder = new int[numPancakes];
	if(pancakes.size()!=numPancakes){
		stackOrder[0]=-1;
	}
	else
	{
		for(int i=0; i<pancakes.size();i++){
			if(stoi(pancakes[i])<1||stoi(pancakes[i])>numPancakes){
				stackOrder[0]=-1;
				break;
			}
			for(int j=0;j<i;j++){
				if(stoi(pancakes[i])==stackOrder[j]){
					stackOrder[0]=-1;
					break;
				}
			}
			stackOrder[i] = stoi(pancakes[i]);
		}
	}
	return stackOrder;
}
 
bool GameStackOrderWindow::wait_for_button() {
    this->show();
    this->wait_for_this();
    return true;
}

void GameStackOrderWindow::submit_event() {
	/* FLTK:
	string userIn = in_order.get_string();
	*/
	string userIn;
	in_order.getline(0, userIn);
	
	if(userIn==""){
		stackOrder = new int[1];
		stackOrder[0]=-1;
	}
	else{
		splitUserInput(userIn);
	}
	// FLTK: button_pushed = true;
	this->close();
}

void GameStackOrderWindow::cb_submit(const nana::arg_click & eventinfo) {
    submit_event();
}

/*****************************************************
 * PUBLIC METHODS
 ****************************************************/

/* Default Constructor creates a dummy game with the file name so it can get scores */
GameStackOrderWindow::GameStackOrderWindow(point p, nana::size s, string name, int numpan):
	form(rectangle(p, s)),
	numPancakes(numpan),
	submit_button(*this, rectangle(430, 340, 100, 20), true),
	in_order(*this, rectangle(285, 300, 245, 30), true),
	order_label(*this, rectangle(200, 280, 350, 20))

	/* FLTK:
    Window(p, width, height, name), 
	numPancakes(numpan),
	submit_button(Point(430,340), 100, 30, "Submit", cb_submit),
	in_order(Point(285,300),245,30,""),
	order_label(Point(160,280),"Enter order separated by commas. Press SUBMIT for random order.")
	*/
	{
		order_label.caption("Enter order separated by commas. Press SUBMIT for random order.");
		submit_button.caption("Submit");

		this->bgcolor(BLACK);
		in_order.bgcolor(BLACK); in_order.fgcolor(GREEN);
		order_label.bgcolor(BLACK); order_label.fgcolor(GREEN);
		
        submit_button.events().click(
            [this](const nana::arg_click& ei){cb_submit(ei);}
        );
		/* FLTK:
		color(FL_BLACK);
		order_label.set_color(FL_GREEN);
		attach(order_label);
		attach(in_order);
		attach(submit_button);
		*/
}

