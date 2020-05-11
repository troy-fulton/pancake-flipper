/*
CSCE 315 503
Project 4
Group 12

Abdul Campos
Troy Fulton
...

ScoresWindow.cpp - Implementations for Window to display scores...
*/

#include "ScoresWindow.h"
#include <boost/algorithm/string.hpp>
#include <iostream>

/*****************************************************
 * PRIVATE / PROTECTED METHODS
 ****************************************************/

void ScoresWindow::quit_win() {
    in_initials.getline(0, player_name);
    if (player_name.size() <= 3 && player_name.size() > 0)
        this->close();
    else 
        enter_initials.fgcolor(RED);

    /* FLTK:
    player_name = in_initials.get_string();
    button_pushed = player_name.size() <= 3 && player_name.size() > 0;
    if (button_pushed == false)
        enter_initials.set_color(FL_RED);
    redraw();
    */
}

void ScoresWindow::cb_done(const nana::arg_click & eventinfo) {
    quit_win();
}

void ScoresWindow::restart_win() {
    // FLTK: button_pushed = true;
    is_new_game = true;
    this->close();
}

void ScoresWindow::cb_new_game(const nana::arg_click & eventinfo) {
    restart_win();
}

void ScoresWindow::main_win() {
    // FLTK: button_pushed = true;
    is_new_game = false;
    this->close();
}

void ScoresWindow::cb_main_menu(const nana::arg_click & eventinfo) {
    main_win();
}

/*****************************************************
 * PUBLIC METHODS
 ****************************************************/

bool ScoresWindow::wait_for_button() {
    this->show();
    this->wait_for_this();
    return true;
}

void ScoresWindow::set_colors() {
    this->bgcolor(BLACK);
    scores_title.fgcolor(GREEN); scores_title.bgcolor(BLACK);
    enter_initials.fgcolor(GREEN); enter_initials.bgcolor(BLACK);
    in_initials.fgcolor(GREEN); in_initials.bgcolor(BLACK);
    score1.fgcolor(WHITE); score1.bgcolor(BLACK);
    score2.fgcolor(WHITE); score2.bgcolor(BLACK);
    score3.fgcolor(WHITE); score3.bgcolor(BLACK);
    score4.fgcolor(WHITE); score4.bgcolor(BLACK);
    score5.fgcolor(WHITE); score5.bgcolor(BLACK);
    your_score.fgcolor(GREEN); your_score.bgcolor(BLACK);
    your_score_prompt.fgcolor(GREEN); your_score_prompt.bgcolor(BLACK);
}

void ScoresWindow::set_labels() {
    int num_scores = scores.size()/2;
    if (num_scores > 0) score1.caption(scores[1] + "        " + scores[2]);
    if (num_scores > 1) score2.caption(scores[3] + "        " + scores[4]);
    if (num_scores > 2) score3.caption(scores[5] + "        " + scores[6]);
    if (num_scores > 3) score4.caption(scores[7] + "        " + scores[8]);
    if (num_scores > 4) score5.caption(scores[9] + "        " + scores[10]);
    scores_title.caption("TOP SCORES");
    new_game.caption("New Game");
    main_menu.caption("Main Menu");

    if (is_beginning) {
        enter_initials.caption("Please enter your initials: ");
        done_button.caption("Done");
    }
    else {
        your_score_prompt.caption("Your Score is: ");
        your_score.caption(to_string(player_score));
    }
}

/* FLTK:
void ScoresWindow::do_attaches() {
    attach(scores_title);
    attach(score1);
    attach(score2);
    attach(score3);
    attach(score4);
    attach(score5);
    if (is_beginning) {
        attach(in_initials);
        attach(enter_initials);
        attach(done_button);
    }
    else {
        attach(your_score_prompt);
        attach(your_score);
        attach(new_game);
        attach(main_menu);
    }
}
*/

string ScoresWindow::getPlayerName() {
    return player_name;
}

bool ScoresWindow::getNewGame() {
    return is_new_game;
}

/* Default Constructor creates a dummy game with the file name so it can get scores */
ScoresWindow::ScoresWindow(point p, nana::size s, string name, vector<string> strs, int ps, bool ib):
    // FLTK: Window(p, width, height, name),
    form(rectangle(p, s)),
    scores(strs),
	is_beginning(ib),
    player_score(ps),
	done_button(*this, rectangle(350, 500, 100, 20), ib),
    in_initials(*this, rectangle(455, 400, 40, 20), ib),
    enter_initials(*this, rectangle(240, 405, 200, 20)),
    scores_title(*this, rectangle(360, 100, 100, 20)),
    score1(*this, rectangle(360, 125 + 20, 200, 20)),
    score2(*this, rectangle(360, 125 + 40, 200, 20)),
    score3(*this, rectangle(360, 125 + 60, 200, 20)),
    score4(*this, rectangle(360, 125 + 80, 200, 20)),
    score5(*this, rectangle(360, 125 + 100, 200, 20)),
    your_score_prompt(*this, rectangle(300, 300, 150, 20)),
    your_score(*this, rectangle(450, 300, 150, 20)),
    new_game(*this, rectangle(250, 400, 100, 20), !ib),
    main_menu(*this, rectangle(450, 400, 100, 20), !ib)

    /* FLTK:
    done_button(Point(350, 500), 100, 20, "Done", cb_done),
    in_initials(Point(455, 400), 40, 30, ""),
    enter_initials(Point(240, 420), "Please enter your initials: "),
    scores_title(Point(360, 100), "TOP SCORES"),
    score1(Point(360, 125 + 20), ""),
    score2(Point(360, 125 + 40), ""),
    score3(Point(360, 125 + 60), ""),
    score4(Point(360, 125 + 80), ""),
    score5(Point(360, 125 + 100), ""),
    your_score_prompt(Point(300, 300), "Your Score is: "),
    your_score(Point(450, 300), "100"),
    new_game(Point(250, 400), 100, 20, "New Game", cb_new_game),
    main_menu(Point(450, 400), 100, 20, "Main Menu", cb_main_menu) 
    */
    {
        done_button.events().click(
            [this](const nana::arg_click& ei){cb_done(ei);}
        );
        new_game.events().click(
            [this](const nana::arg_click& ei){cb_new_game(ei);}
        );
        main_menu.events().click(
            [this](const nana::arg_click& ei){cb_main_menu(ei);}
        );

        set_colors();
        set_labels();
        // FLTK: do_attaches();
}
