#include <iostream>
#include "Button.hpp"
#include "graphics.hpp"
using namespace genv;
using namespace std;

Button::Button(int x, int y, int sx, int sy, string label, std::function<void()> action)
    : Widget(x,y,sx,sy), _label(label), _pushed(false), _action(action), _bg_color(255,255,255), _text_color(100,100,100), _button_color(255,255,255), _highlight_color(15,192,252)
{}

void Button::select()
{
    _text_color = color(0,0,0);
    _selected = true;
}
void Button::deselect()
{
    _text_color = color(100,100,100);
    _selected = false;
}

void Button::push()
{
    _bg_color = color(15,192,252);
    _pushed = true;
}
void Button::release()
{
    _bg_color = color(255,255,255);
    _pushed = false;
}

void Button::draw() const
{
    if(_selected)
    {
        gout << _highlight_color << move_to(_x-1,_y-1) << box(_size_x+2,_size_y+2);
    }
    gout << _text_color << move_to(_x, _y) << box(_size_x, _size_y);
    gout << _bg_color << move_to(_x+2, _y+2) << box(_size_x-4, _size_y-4);
    gout << _text_color << move_to(_x+_size_x/2-gout.twidth(_label)/2,_y+_size_y/2+gout.cascent()/2) << text(trim(_label,_size_x-10));
}

void Button::handle(event ev)
{
    if((ev.button == btn_left && is_hover(ev.pos_x,ev.pos_y)) || ev.keycode == key_enter)
        push();
    if((ev.button == -btn_left && is_hover(ev.pos_x,ev.pos_y)) || ev.keycode == -key_enter)
    {
        release();
        _action();
    }
}
string Button::get_label() const
{
    return _label;
}
void Button::set_label(string label)
{
    _label = label;
}
void Button::set_action(std::function<void()> action)
{
    _action = action;
}
void Button::log(ostream &logfile) const
{
    logfile << "#noinfo" << endl;
}

