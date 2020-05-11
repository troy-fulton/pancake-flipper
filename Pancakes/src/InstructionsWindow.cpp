/*
CSCE 315 503
Project 4
Group 12

Abdul Campos
Troy Fulton
...

ScoresWindow.cpp - Implementations for Window to display scores...
*/

#include "InstructionsWindow.h"
#include <boost/algorithm/string.hpp>

/*****************************************************
 * DEFINES
 ****************************************************/

/*****************************************************
 * PRIVATE / PROTECTED METHODS
 ****************************************************/

void InstructionsWindow::cb_done(const nana::arg_click & eventinfo) {
	delete pan;
    this->close();
}

bool InstructionsWindow::wait_for_button() {
    this->show();
    this->wait_for_this();
    return true;
    /*
    // modified event loop:
    // handle all events (as per default), quit when button_pushed becomes true
    // this allows graphics without control inversion
        show();
        button_pushed = false;
    #if 1
        // Simpler handler
        while (!button_pushed) Fl::wait();
        Fl::redraw();
    #else
        // To handle the case where the user presses the X button in the window frame
        // to kill the application, change the condition to 0 to enable this branch.
        Fl::run();
    #endif
        return button_pushed;
    */
}

/* FLTK:
void InstructionsWindow::quit_win() {
    button_pushed = true;
}

void InstructionsWindow::cb_done(const nana::arg_click & eventinfo) {
    reference_to<InstructionsWindow>(pw).quit_win();
}
*/

void InstructionsWindow::set_captions() {
    continue_button.caption("Done");
    instructions_title.caption("INSTRUCTIONS");
    inst1.caption(instructions_strings[0]);
    inst2.caption(instructions_strings[1]);
    inst3.caption(instructions_strings[2]);
    inst4.caption(instructions_strings[3]);
    inst5.caption(instructions_strings[4]);
    inst6.caption(instructions_strings[5]);
    inst7.caption(instructions_strings[6]);
    inst8.caption(instructions_strings[7]);
    inst9.caption(instructions_strings[8]);
    inst10.caption(instructions_strings[9]);
}

void InstructionsWindow::set_colors() {
    this->bgcolor(BLACK);
    instructions_title.bgcolor(BLACK); instructions_title.fgcolor(GREEN);
    inst1.bgcolor(BLACK); inst1.fgcolor(GREEN);
    inst2.bgcolor(BLACK); inst2.fgcolor(GREEN);
    inst3.bgcolor(BLACK); inst3.fgcolor(GREEN);
    inst4.bgcolor(BLACK); inst4.fgcolor(GREEN);
    inst5.bgcolor(BLACK); inst5.fgcolor(GREEN);
    inst6.bgcolor(BLACK); inst6.fgcolor(GREEN);
    inst7.bgcolor(BLACK); inst7.fgcolor(GREEN);
    inst8.bgcolor(BLACK); inst8.fgcolor(GREEN);
    inst9.bgcolor(BLACK); inst9.fgcolor(GREEN);
    inst10.bgcolor(BLACK); inst10.fgcolor(GREEN);
}


/*****************************************************
 * PUBLIC METHODS
 ****************************************************/

/* Default Constructor creates a dummy game with the file name so it can get scores */
InstructionsWindow::InstructionsWindow(point p, nana::size s, string name):
    form(rectangle(p, s), appear::decorate<appear::taskbar>()),
    continue_button(*this, BUTTON_RECT, true),
    instructions_title(*this, rectangle(point(s.width/2 - 35, s.height/10), nana::size(150,20)), "INSTRUCTIONS"),
    inst1(*this, rectangle(point(s.width/2 - 165, s.height/5 + 0), nana::size(400,20))),
    inst2(*this, rectangle(point(s.width/2 - 165, s.height/5 + 20), nana::size(400,20))),
    inst3(*this, rectangle(point(s.width/2 - 165, s.height/5 + 40), nana::size(400,20))),
    inst4(*this, rectangle(point(s.width/2 - 165, s.height/5 + 60), nana::size(400,20))),
    inst5(*this, rectangle(point(s.width/2 - 165, s.height/5 + 120), nana::size(400,20))),
    inst6(*this, rectangle(point(s.width/2 - 165, s.height/5 + 140), nana::size(400,20))),
    inst7(*this, rectangle(point(s.width/2 - 165, s.height/5 + 160), nana::size(400,20))),
    inst8(*this, rectangle(point(s.width/2 - 165, s.height/5 + 180), nana::size(400,20))),
    inst9(*this, rectangle(point(s.width/2 - 165, s.height/5 + 200), nana::size(400,20))),
    inst10(*this, rectangle(point(s.width/2 - 95, s.height/5 + 240), nana::size(400,20))),
	flipper_img(*this, rectangle(s.width / 2 - 60 - 80, (s.height * 7 / 10) + 3, 80, 22))
    //sample_pancake(*this, rectangle(point(s.width/2 - 100, s.height*7/10), nana::size(100, 40)))
    {
		flipper_img.load(paint::image("flipper.bmp"));
		flipper_img.stretchable(22, 80, 22, 80);
		pan = new Pancake(*this, point(s.width / 2 - 60, s.height * 7 / 10), 6, true);
        set_captions();
        set_colors(); // here
        
        continue_button.events().click(
            [this](const nana::arg_click& ei){cb_done(ei);}
        );

        /* FLTK:
        color(FL_BLACK);
        attach(continue_button);
        set_colors();
        attach(instructions_title);
        attach(inst1);
        attach(inst2);
        attach(inst3);
        attach(inst4);
        attach(inst5);
        attach(inst6);
        attach(inst7);
        attach(inst8);
        attach(inst9);
        attach(inst10);
        sample_pancake.resize(200, 50);
        label.set_color(FL_YELLOW);
        label.set_font_size(label.font_size() + 2);
        attach(sample_pancake);
        attach(label);
        */
}

