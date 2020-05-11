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

GraphicsEngine.cpp - Implementations for Engine methods for running the game and
        keeping track of which game the user is on. Calls methods from various 
        other screens and instantiates them when necessary.
*/

#include "GraphicsEngine.h"
#include <boost/algorithm/string.hpp>

/*****************************************************
 * PRIVATE / PROTECTED METHODS
 ****************************************************/

/* Callbacks */

void GraphicsEngine::cb_play(const nana::arg_click & eventinfo) {
    bool keep_playing;

    this->hide();
    do {
        keep_playing = game_sequence();
    } while (keep_playing);
    this->show();

    return;
}

void GraphicsEngine::cb_inst(const nana::arg_click & eventinfo) {
    // Display an instruction screen...
    this->hide();
    InstructionsWindow iw(SCR_POINT, SCR_SIZE, "Instructions");
    iw.wait_for_button();
    this->show();
}

/* Helper Functions */

string GraphicsEngine::create_name_string(){
    int size = names.size();
	string str ="";
	int i;
	for(i=0;i<size-1;i++){
		str+=names[i]+"\t";
	}
	str+=names[i];
	return str;
}

bool GraphicsEngine::game_sequence() {

	// Display an instruction screen...
	this->hide();
	InstructionsWindow iw(SCR_POINT, SCR_SIZE, "Instructions");
	iw.wait_for_button();

    // Get options from user about game
    GameOptionsWindow gow(SCR_POINT, SCR_SIZE, "Options");
    gow.wait_for_button();
	int num_pan = gow.get_num_pan();
	int dif_level = gow.get_dif_level();

	//get stack order
	GameStackOrderWindow gsow(SCR_POINT, SCR_SIZE, "Order", num_pan);
	gsow.wait_for_button();
	
    // Get username and show scores so far
    ScoresWindow sw(SCR_POINT, SCR_SIZE, "Options", getScores(), 0, true);
    sw.wait_for_button();

    // Generate the stack and start the game
    int* new_stack = gsow.getStackOrder()[0]==-1?curr_game->gen_rand_stack(num_pan):gsow.getStackOrder();
    startGame(num_pan, dif_level, "scores.txt", new_stack);

    curr_game->username = sw.getPlayerName().c_str();

    // Play the game and get the results
    GameplayWindow gpw(SCR_POINT, SCR_SIZE, "Instructions", curr_game);
    gpw.wait_for_button();
    if (gpw.getStartOver()) return true;
    if (gpw.getQuit()) return false;

    // Get the score
    int player_score = curr_game->computeScore(curr_game->getDifficulty(), 
            curr_game->getStackSize(), 
            curr_game->getHumanStack(), 
            curr_game->getAIStack());
    curr_game->writeScore();

    // Show user's score and current score and ask to play again
    ScoresWindow sw1(SCR_POINT, SCR_SIZE, "Options", getScores(), player_score, false);
    sw1.wait_for_button();
    return sw1.getNewGame();

    return false;
}

/* FLTK:
void GraphicsEngine::play_win() {
    hide();
    bool keep_playing;

    do {
        keep_playing = game_sequence();
    } while (keep_playing);

    show();
}

void GraphicsEngine::quit_win() {
    button_pushed = true;
}

void GraphicsEngine::instructions_win() {
    hide();
    InstructionsWindow iw(SCR_LOC, SCR_WIDTH, SCR_HEIGHT, "Instructions");
    iw.wait_for_button();
    show();
}

void GraphicsEngine::cb_play(Address, Address pw) {
    reference_to<GraphicsEngine>(pw).play_win();
}

void GraphicsEngine::cb_instructions(Address, Address pw) {
    reference_to<GraphicsEngine>(pw).instructions_win();
}

void GraphicsEngine::cb_quit(Address, Address pw) {
    reference_to<GraphicsEngine>(pw).quit_win();
}
*/


/*****************************************************
 * PUBLIC METHODS
 ****************************************************/

/* Constructor */
GraphicsEngine::GraphicsEngine(string name): 
    form(SCR_RECT),
    title(*this, rectangle(TITLE_X, TITLE_Y, 200, 20)),
    ret(*this, rectangle(NAMES_X, NAMES_Y, 105, 120)),
    play_btn(*this, PLAY_RECT, true),
    inst_btn(*this, INST_RECT, true),
    quit_btn(*this, QUIT_RECT, true),
    pancake_img(*this, PIC_RECT)
    /* FLTK:
    Window(p, width, height, name),
    img_pos(360,250),
    title_pos(300,100),
    sub_title_pos(360,120),
    names_pos(43,200),
    title(title_pos,"PANCAKE SORTING GAME"),
    sub_title(sub_title_pos,"TEAM 17"),
    button_play(Point(340, 350), 100, 20, "Play",cb_play),
    button_instr(Point(340, 405), 100, 20, "Instructions",cb_instructions),
    button_qt(Point(340, 460), 100, 20, "Quit",cb_quit)
    */
    {
        /* Captions */
        title.caption("PANCAKE SORTING GAME");
        ret.caption(create_name_string());
        play_btn.caption("Play");
        inst_btn.caption("Instructions");
        quit_btn.caption("Quit");

        /* Colors */
	    title.bgcolor(BLACK); title.fgcolor(GREEN);
	    ret.bgcolor(BLACK); ret.fgcolor(GREEN);
	    this->bgcolor(BLACK);

        /* Load picture */
        pancake_img.load( paint::image("pancake_splash.bmp") );

        /* Button events */
        quit_btn.events().click(API::exit);
        play_btn.events().click(
            [this](const nana::arg_click& ei){cb_play(ei);}
        );
        inst_btn.events().click(
            [this](const nana::arg_click& ei){cb_inst(ei);}
        );

        /* Dummy game with our scores file */
        curr_game = new Game(0, 1, string("scores.txt"), NULL);

		/* Stretch out the bitmap image */
		pancake_img.stretchable(375, 100, 50, 40);
}

GraphicsEngine::~GraphicsEngine() {
    delete curr_game;
}

bool GraphicsEngine::wait_for_button() {
    this->show();
    this->wait_for_this();
    return true;
    /* FLTK (same for all classes):
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

/* For drawing various screens */

/* FLTK Implementation:
void GraphicsEngine::drawSplashScreen() {
    // SET BG_COLOR
    color(FL_BLACK);

    // CREATE NAMES STRING
    string names = create_name_string(name);
    Text name_title(names_pos,names);
    
    // LOAD IMAGE
    Suffix::Encoding x(Suffix::Encoding::jpg);
    Image image(img_pos,"pancake_splash.jpg",x);
    
    // COLORING TEXT
    title.set_color(FL_GREEN);
    sub_title.set_color(FL_GREEN);
    name_title.set_color(FL_GREEN);

    // FINAL ATTACH
    attach(button_play);
    attach(button_instr);
    attach(button_qt);
    attach(title);
    attach(sub_title);
    attach(name_title);
    attach(image);
    wait_for_button();

}

bool GraphicsEngine::runGame() {
    // FLTK: drawSplashScreen();     // and wait to continue
    return true;
}
*/

vector<string> GraphicsEngine::getScores() {
    string scores = curr_game->getHighScores();
    replace(scores.begin(),scores.end(), '\n', ' ');
    vector<string> splitScores;
    boost::split(splitScores, scores, [](char c){return c == ' ';});
    return splitScores;
}

void GraphicsEngine::startGame(int num_pancakes, int ai_difficulty, string fn, int* starting_order) {
    Game* temp = curr_game;
    curr_game = new Game(num_pancakes, ai_difficulty, fn, starting_order);
    delete temp;
}
