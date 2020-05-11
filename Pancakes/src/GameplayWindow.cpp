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

GameplayWindow.cpp - Implementations for Gameplay Window methods for showing
                each pancake stack in the current state of the game
                and handling all the events of the game.
*/

#include "GameplayWindow.h"
#include <boost/algorithm/string.hpp>
#include "stdlib.h"

/*****************************************************
 * FinishedWindow PRIVATE / PROTECTED METHODS
 ****************************************************/

void FinishedWindow::cb_done(const nana::arg_click & eventinfo) {
    quit_win();
}

/*****************************************************
 * FinishedWindow PUBLIC METHODS
 ****************************************************/

FinishedWindow::FinishedWindow(point p, nana::size s, string label) :
    form(rectangle(p, s)),
    win_or_lose(*this, rectangle(100, 100, 100, 100))
    /* FLTK:
    Window(p, ww, hh, label), message(Point(180, 100), label), 
    done_button(Point(150, 150), ww/3, 20, "DONE", cb_done) 
    */
    {
        win_or_lose.caption(label);
        win_or_lose.fgcolor(BLACK);
        win_or_lose.bgcolor(color_rgb(0x0ffff0));
        this->bgcolor(color_rgb(0x0ffff0));
        /* FLTK:
        color(FL_BLACK);
        message.set_color(FL_GREEN);
        attach(done_button);
        attach(message);
        */
}

bool FinishedWindow::wait_for_button() {
    this->show();
    this->wait_for_this();
    return true;
}

/*****************************************************
 * GameplayWindow PRIVATE / PROTECTED METHODS
 ****************************************************/

void GameplayWindow::cb_quit(const nana::arg_click & eventinfo) {
    quit_win();
}
void GameplayWindow::cb_restart(const nana::arg_click & eventinfo) {
    restart_win();
}

/* FLTK:
// Callbacks...
void GameplayWindow::cb_quit(Address, Address pw) {
    reference_to<GameplayWindow>(pw).quit_win();
}
void GameplayWindow::cb_restart(Address, Address pw) {
    reference_to<GameplayWindow>(pw).restart_win();
}
void GameplayWindow::cb_pancake1(Address, Address pw) {
    reference_to<GameplayWindow>(pw).pancake_select(1);
}
void GameplayWindow::cb_pancake2(Address, Address pw) {
    reference_to<GameplayWindow>(pw).pancake_select(2);
}
void GameplayWindow::cb_pancake3(Address, Address pw) {
    reference_to<GameplayWindow>(pw).pancake_select(3);
}
void GameplayWindow::cb_pancake4(Address, Address pw) {
    reference_to<GameplayWindow>(pw).pancake_select(4);
}
void GameplayWindow::cb_pancake5(Address, Address pw) {
    reference_to<GameplayWindow>(pw).pancake_select(5);
}
void GameplayWindow::cb_pancake6(Address, Address pw) {
    reference_to<GameplayWindow>(pw).pancake_select(6);
}
void GameplayWindow::cb_pancake7(Address, Address pw) {
    reference_to<GameplayWindow>(pw).pancake_select(7);
}
void GameplayWindow::cb_pancake8(Address, Address pw) {
    reference_to<GameplayWindow>(pw).pancake_select(8);
}
void GameplayWindow::cb_pancake9(Address, Address pw) {
    reference_to<GameplayWindow>(pw).pancake_select(9);
}
// ...end callbacks
*/

void GameplayWindow::quit_win() {
	quit_game = true;
    // FLTK: button_pushed = true;
    this->close();
}

void GameplayWindow::restart_win() {
    /* FLTK:
	detach(spatula);
	detach(AI_spatula);
    button_pushed = true;
    */
    start_over = true;
    this->close();
}

void GameplayWindow::pancake_select() {
    
    // Flip the stack to represent the change
    selected_pancake = human_stack.selected_pancake;
	human_stack.draw_order(curr_game->getHumanStack(), false, false, true, selected_pancake);	// draw with blinking
    curr_game->moveHuman(curr_game->getStackSize() - selected_pancake - 1); //return the adjusted selection
    human_stack.draw_order(curr_game->getHumanStack(), false);
	_sleep(1000);
    /* FLTK: 
    detach(human_stack);
    human_stack.draw_order(curr_game->getHumanStack(), false);
    attach(human_stack);
    */
	
    // Show the spatula as a helpful thing
    /*
	int spat_y = human_stack.origin.y + 40*i-5;
	int spat_x = human_stack.origin.x + 100;
    put_spatula(spat_x, spat_y);
    */

	human_stack.flipper_img.hide();
	turn.caption("AI's turn...");

    // Do the AI's move
    int ai_move = curr_game->getAIMove();

	Pancake* p = ai_stack.selection[curr_game->getStackSize() - ai_move - 1];
	ai_stack.flipper_img.show();
	ai_stack.flipper_img.move(rectangle(p->pos().x - 80, p->pos().y - 18, 80, 22));

    // Blink on the AI's stack
    /*
	redraw();
	int spat_AI_y = ai_stack.origin.y + 40*(curr_game->getStackSize()-ai_move)-5;
	int spat_AI_x = ai_stack.origin.x + 100;
	put_AI_spatula(spat_AI_x,spat_AI_y);
    */
    // Move the AI and redraw its stack
	ai_stack.draw_order(curr_game->getAIStack(), false, false, true, curr_game->getStackSize() - ai_move - 1);
    curr_game->moveAI(ai_move);
    ai_stack.draw_order(curr_game->getAIStack(), false);
	_sleep(1000);
	ai_stack.flipper_img.hide();
    
    /* FLTK:
    detach(ai_stack);
    ai_stack.draw_order(curr_game->getAIStack(), false);
    attach(ai_stack);
    */
	
    /*
    detach(human_stack);
    human_stack.draw_order(curr_game->getHumanStack(), true);
    attach(human_stack);
	redraw();
    */

    if (curr_game->checkWin()) {
        // FLTK: hide();
        string mesg;
        int score = curr_game->computeScore(
            curr_game->getDifficulty(),
            curr_game->getStackSize(),
            curr_game->getHumanStack(),
            curr_game->getAIStack()
        );

        if (score == curr_game->getStackSize()*(curr_game->getDifficulty()+1)) {
            mesg = "YOU TIED!";
        }
        else if (score == curr_game->getStackSize()) {
            mesg = "YOU LOSE!";
        }
        else {
            mesg = "YOU WIN!";
        }
        FinishedWindow fw(point(850, 200), nana::size(400, 200), mesg);
        fw.wait_for_button();
        // FLTK: button_pushed = true;
        this->close();
    }
	else {
		// Redraw the Player stack with buttons only if the game isn't over
		human_stack.draw_order(curr_game->getHumanStack(), true);

		turn.caption("YOUR turn!");
	}
}

void GameplayWindow::put_spatula(int x, int y) {
    /* FLTK:
	detach(spatula);
	Point end (10,y);
	Point start(x,y);
	spatula.change_point(1,end);
	spatula.change_point(0,start);
	spatula.set_color(FL_GRAY);
	attach(spatula);
	redraw();
    */
}

void GameplayWindow::captions() {
    quit_btn.caption("Quit");
    restart_btn.caption("New Game");
    you_text.caption("YOUR STACK");
    ai_text.caption("AI STACK");
    instructions.caption("Select the pancake under which you would like to insert the spatula...");
	turn.caption("YOUR turn!");
}

void GameplayWindow::colors() {
    this->bgcolor(BLACK);
    you_text.bgcolor(BLACK); you_text.fgcolor(GREEN);
    ai_text.bgcolor(BLACK); ai_text.fgcolor(GREEN);
    instructions.bgcolor(BLACK); instructions.fgcolor(GREEN);
	turn.bgcolor(BLACK); turn.fgcolor(GREEN);
}

void GameplayWindow::callbacks() {
    quit_btn.events().click(
        [this](const nana::arg_click& ei){cb_quit(ei);}
    );

    restart_btn.events().click(
        [this](const nana::arg_click& ei){cb_restart(ei);}
    );

    human_stack.events().click([this](const nana::arg_click& ei){
        pancake_select();
    });
}

/*****************************************************
 * GameplayWindow PUBLIC METHODS
 ****************************************************/

bool GameplayWindow::wait_for_button() {
    this->show();
    this->wait_for_this();
    return true;
}

bool GameplayWindow::getQuit() {
    return quit_game;
}

bool GameplayWindow::getStartOver() {
    return start_over;
}

/* Default Constructor creates a dummy game with the file name so it can get scores */
GameplayWindow::GameplayWindow(point p, nana::size s, string name, Game* cg):
    form(rectangle(p, s)),
    quit_btn(*this, rectangle(670, 550, BUTTON_WID, BUTTON_HT)),
    restart_btn(*this, rectangle(540, 550, BUTTON_WID, BUTTON_HT)),
    you_text(*this, rectangle(150, 50, 100, 20)),
    ai_text(*this, rectangle(510, 50, 100, 20)),
    instructions(*this, rectangle(100, 550, 400, 30)),
    human_stack(*this, point(100, 100), /*cg->getStackSize(), cg->getHumanStack(),*/cg, true),
    ai_stack(*this, point(450, 100), /*cg->getStackSize(), cg->getAIStack(),*/cg, false),
    curr_game(cg),
	turn(*this, rectangle(350, 70, 100, 20))
    /* FLTK:
    Window(p, width, height, name),
    curr_game(cg),
    quit_button(Point(670, 550), BUTTON_WID, BUTTON_HT, "Quit", cb_quit), 
    restart_button(Point(540, 550), BUTTON_WID, BUTTON_HT, "New Game", cb_restart), 
    human_stack(Point(100, 100), 100, 100, "Pancake", cg->getStackSize(), cg->getHumanStack(), true, cb_pancake1, cb_pancake2,
        cb_pancake3, cb_pancake4, cb_pancake5, cb_pancake6, cb_pancake7, cb_pancake8, cb_pancake9),
    ai_stack(Point(450, 100), 100, 100, "Pancake", cg->getStackSize(), cg->getHumanStack(), false, cb_pancake1, cb_pancake2,
        cb_pancake3, cb_pancake4, cb_pancake5, cb_pancake6, cb_pancake7, cb_pancake8, cb_pancake9),
    you_text(Point(150, 50), "YOUR STACK"),
    ai_text(Point(510, 50), "AI STACK"),
    instructions(Point(150, 520), "Select the pancake under which you would like to insert the spatula"),
	spatula(Point(0,200),Point(10,200)),
	AI_spatula(Point(0,200),Point(10,200))
    */
    {
        colors();
        captions();
        callbacks();       
        
        /* FLTK:
        color(FL_BLACK);
        attach(quit_button);
        attach(restart_button);
        attach(human_stack);
        attach(ai_stack);

        you_text.set_color(FL_GREEN);
        ai_text.set_color(FL_GREEN);
        instructions.set_color(FL_GREEN);
		attach(spatula);
		attach(AI_spatula);
        attach(you_text);
        attach(ai_text);
        attach(instructions);
        */
}

