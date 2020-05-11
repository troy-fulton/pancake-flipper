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

Stack.h - Interface for using a stack of pancakes integrated with
            NANA. There's a pancake class and a stack that keeps
            track of the positions of the pancakes.
*/

#ifndef __STACK__        // For #including more than once
#define __STACK__

/************************************************
 *  INCLUDES
 ***********************************************/
#include "Game.h"

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
#define SCR_WIDTH 800
#define SCR_HEIGHT 600
#define MIN_PANCAKE_W 20
#define PANCAKE_H 45

/************************************************
 * Helper Classes
 ***********************************************/

using namespace std;
using namespace nana;

/* FLTK:
struct Pancake : Button {
    Image pancake_img;
    Text pancake_num;
    int value;
    bool is_human;

    Pancake(Point xy, int w, int h, const string& label, Callback cb, int val, bool ih)
        : Button(xy,w,h,label,cb),
        pancake_img(xy, "pancake_template.jpg", Suffix::Encoding::jpg),
        pancake_num(xy, to_string(val)),
        value(val),
        is_human(ih)
    {}

    void attach(Window&);

    void hide() {
        if (is_human) Button::hide();
        own->detach(pancake_img);
        own->detach(pancake_num);
    }
};
*/

struct Pancake : nana::button {
    picture pancake_img;
    label pancake_num;
    int value;
    bool is_human;

    Pancake(form& win, point p, int val, bool ih);

	void changeVal(int new_val) { value = new_val; pancake_num.caption(to_string(value)); }

	void hide();
	void show();
};

/************************************************
 * Main Class
 ***********************************************/

/* FLTK:
struct Stack : Widget {
    Stack(Point xy, int w, int h, const string& label, int sz, int* start_order, bool ih, Callback c1, Callback c2,
        Callback c3, Callback c4, Callback c5, Callback c6, Callback c7, Callback c8, Callback c9)
        : Widget(xy,w,h,label,0), offset(0), size(sz), order(start_order), is_human(ih),
        cb1(c1), cb2(c2), cb3(c3), cb4(c4), cb5(c5), cb6(c6), cb7(c7), cb8(c8), cb9(c9),
        origin(xy), width(w), height(h)
    {
        draw_order(start_order, ih, true);
    }

    Point origin;
    int width, height;
    Vector_ref<Pancake> selection;
    int offset;
    int size;
    int* order;
    bool is_human;
    int attach(Pancake& p);      // Menu does not delete &b
    Callback cb1, cb2, cb3, cb4, cb5, cb6, cb7, cb8, cb9;

    void reverse(int* stack, int size) {
        for (int i = 0; i < size/2; i++) {
            int temp = stack[i];
            stack[i] = stack[size - i - 1];
            stack[size - i - 1] = temp;
        }
    }

    void draw_order(int* stack, bool draw_buttons, bool is_first=false) {
        int* temp_stack = new int[size];
        for (int i = 0; i < size; i++) {
            temp_stack[i] = stack[i];
        }
        reverse(temp_stack, size);
        if (!is_first) {
            hide();
            selection.clear();
        }
        int vert_space = PANCAKE_HEIGHT + 10;
        int count = 0;
        int x_shift=0;
        for (int i = 0; i < size; i++) {
            x_shift = PANCAKE_WIDTH*(10-temp_stack[i]-1);

            switch (count) {
            case 0:
                selection.push_back(new Pancake(Point(origin.x+x_shift, origin.y + vert_space*i), width, height, "", cb1, temp_stack[i], draw_buttons));
                break;
            case 1:
                selection.push_back(new Pancake(Point(origin.x+x_shift, origin.y + vert_space*i), width, height, "", cb2, temp_stack[i], draw_buttons));
                break;
            case 2:
                selection.push_back(new Pancake(Point(origin.x+x_shift, origin.y + vert_space*i), width, height, "", cb3, temp_stack[i], draw_buttons));
                break;
            case 3:
                selection.push_back(new Pancake(Point(origin.x+x_shift, origin.y + vert_space*i), width, height, "", cb4, temp_stack[i], draw_buttons));
                break;
            case 4:
                selection.push_back(new Pancake(Point(origin.x+x_shift, origin.y + vert_space*i), width, height, "", cb5, temp_stack[i], draw_buttons));
                break;
            case 5:
                selection.push_back(new Pancake(Point(origin.x+x_shift, origin.y + vert_space*i), width, height, "", cb6, temp_stack[i], draw_buttons));
                break;
            case 6:
                selection.push_back(new Pancake(Point(origin.x+x_shift, origin.y + vert_space*i), width, height, "", cb7, temp_stack[i], draw_buttons));
                break;
            case 7:
                selection.push_back(new Pancake(Point(origin.x+x_shift, origin.y + vert_space*i), width, height, "", cb8, temp_stack[i], draw_buttons));
                break;
            case 8:
                selection.push_back(new Pancake(Point(origin.x+x_shift, origin.y + vert_space*i), width, height, "", cb9, temp_stack[i], draw_buttons));
            }
            count++;                               
        }
        //if (!is_first) show();
    }

    void show()                 // show all buttons
    {
        for (int i = 0; i<selection.size(); ++i)
            selection[i].show();
    }
    void hide()                 // hide all buttons
    {
        for (int i = 0; i<selection.size(); ++i) 
            selection[i].hide(); 
    }
    void move(int dx, int dy)   // move all buttons- DONT TRY THIS
    {
        for (int i = 0; i<selection.size(); ++i) 
            selection[i].move(dx,dy);
    }

    void attach(Window& win)    // attach all buttons
    {
        for (int i=0; i<selection.size(); ++i) win.attach(selection[i]);
        own = &win;
    }

    void detach(Window& win)
    {
        for (int i=0; i<selection.size(); ++i) win.detach(selection[i]);
    }
};
*/

struct Stack : nana::button {
    Stack(form& win, point p, Game* cg,/*int sz, int* start_order,*/ bool ih);
    ~Stack();

    form& curr_win;
    Game* curr_game;
    point origin;
    int width, height;
    vector<Pancake*> selection;
    int offset;
    int size;
    int* order;
    bool is_human;
    int selected_pancake;
	picture flipper_img;

    void reverse(int* stack, int size);

    int select_pancake(const nana::arg_click& ei);

    void draw_order(int* stack, bool draw_buttons, bool is_first=false, bool blink=false, int blink_index=0);
};

#endif