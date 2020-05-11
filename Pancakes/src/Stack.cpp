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

Stack.cpp - Implementation for a stack of pancakes integrated with
            NANA. There's a pancake class and a stack that keeps
            track of the positions of the pancakes.
*/

#include "Stack.h"



Pancake::Pancake(form& win, point p, int val, bool ih): 
    button(win, rectangle(point(p.x, p.y + PANCAKE_H*33/50), nana::size(val*MIN_PANCAKE_W, PANCAKE_H*12/50)), ih),
    pancake_img(win, rectangle(p, nana::size(val*MIN_PANCAKE_W, PANCAKE_H*3/5))),
    pancake_num(win, rectangle(point(p.x + val*MIN_PANCAKE_W/2 - 3, p.y + PANCAKE_H*6/50), nana::size(9, 12))),
    value(val),
    is_human(ih)
{
    pancake_img.load( paint::image("pancake_template.bmp") );
    pancake_num.bgcolor(color_rgb(0xB97B57));
    pancake_num.fgcolor(color_rgb(0xFFFF00));
    pancake_num.caption(to_string(val));
    if (val == 1)
        caption("^^");
    else if (val == 2)
        caption("^FLIP^");
    else
        caption("^^ FLIP ^^");
    pancake_img.stretchable(PANCAKE_H*(30/50), val*MIN_PANCAKE_W, PANCAKE_H*(30/50), val*MIN_PANCAKE_W);
}

void Pancake::show() {
	if (is_human) button::show();
	pancake_img.load(paint::image("pancake_template.bmp"));
	pancake_num.bgcolor(color_rgb(0xB97B57));
	pancake_num.fgcolor(color_rgb(0xFFFF00));
	pancake_num.caption(to_string(value));
	if (value == 1)
		caption("^^");
	else if (value == 2)
		caption("^FLIP^");
	else
		caption("^^ FLIP ^^");
	pancake_img.stretchable(PANCAKE_H*(30 / 50), value*MIN_PANCAKE_W, PANCAKE_H*(30 / 50), value*MIN_PANCAKE_W);
	pancake_img.show();
	pancake_num.show();
}

void Pancake::hide() {
	button::hide();
	pancake_img.hide();
	pancake_num.hide();
}

Stack::Stack(form& win, point p, Game* cg,/*int sz, int* start_order,*/ bool ih):
    button(win, rectangle(
        point(p.x + 40,
            p.y + PANCAKE_H*cg->getStackSize() + 10),
        nana::size(100,20)), ih),
    curr_game(cg),
    offset(0),
    size(cg->getStackSize()),
    order(cg->getHumanStack()),
    is_human(ih),
    origin(p),
    width((cg->getStackSize()-1)*MIN_PANCAKE_W),
    height(cg->getStackSize()*PANCAKE_H),
    curr_win(win),
	flipper_img(win, rectangle(0, 0, 80, 22))	// dummy position and size
{
	flipper_img.load(paint::image("flipper.bmp"));
	flipper_img.stretchable(22, 80, 22, 80);
	flipper_img.hide();
    // Human and AI stacks are the same when constructed
    draw_order(cg->getHumanStack(), ih, true);
    bgcolor(GREEN);
    caption("SELECT");
}

void Stack::reverse(int* stack, int size) {
    for (int i = 0; i < size/2; i++) {
        int temp = stack[i];
        stack[i] = stack[size - i - 1];
        stack[size - i - 1] = temp;
    }
}

int Stack::select_pancake(const nana::arg_click& ei) {
    // Indicates which pancake was selected
    int pancake;
    Pancake* p = (Pancake*) API::get_widget(ei.window_handle);
    for (int i = 0; i < size; i++) {
        if (p == selection[i]) {
            selected_pancake = i;
        }
    }
    for (Pancake* pan: selection){
        pan->fgcolor(BLACK);
    }
    p->fgcolor(GREEN);
	// Put flipper down there:
	flipper_img.show();
	flipper_img.move(rectangle(p->pos().x - 80, p->pos().y - 20, 80, 22));
    return selected_pancake;
}

void Stack::draw_order(int* stack, bool draw_buttons, bool is_first, bool blink, int blink_index) {
    // For the case when the AI turn is over and it just needs to draw buttons:
    bool stacks_same = true;
    for (int i = 0; i < size; i++) {
        if (order[i] != stack[i]) {
            stacks_same = false;
            break;
        }
    }
    bool just_redraw_buttons = !is_first && draw_buttons && stacks_same;

    if (just_redraw_buttons) {
		for (Pancake* p : selection) {
			if (draw_buttons) p->is_human = true;
			p->show();
		}
        this->show();
        return;
    }

    int* temp_stack = new int[size];
    for (int i = 0; i < size; i++) {
        temp_stack[i] = stack[i];
    }
    reverse(temp_stack, size);

    if (!is_first) {
		
		// Then hide them:
		for (Pancake* p : selection) {
			p->hide();
		}
		for (int i = 0; i < size; i++) {
			selection[i]->close();
			delete selection[i];
		}
		selection.clear();
    }

    int vert_space = PANCAKE_H;
    int x_shift=0;
    for (int i = 0; i < size; i++) {

        x_shift = (MIN_PANCAKE_W-10)*(10-temp_stack[i]-1);

        Pancake* temp = new Pancake(curr_win, point(origin.x + x_shift, origin.y + vert_space*i), temp_stack[i], draw_buttons);

        temp->events().click([this](const nana::arg_click& ei){select_pancake(ei);});

        selection.push_back(temp);
    }

	_sleep(500);
	if (blink) {
		// Do the blinking:
		for (int j = 0; j <2; j++) {
			for (int i = blink_index; i >= 0; i--) {
				selection[i]->hide();
				if (i == blink_index) flipper_img.move(point(flipper_img.pos().x, flipper_img.pos().y - 10));
				_sleep(100);
				selection[i]->show();
				if (i == blink_index) flipper_img.move(point(flipper_img.pos().x, flipper_img.pos().y + 10));
				_sleep(100);
			}
		}
	}

    if (!draw_buttons) this->hide();
}

Stack::~Stack() {
    for (Pancake* p: selection)
        delete p;
}