#include "dynstring.hpp"
#include "graphics.hpp"
#include <iostream>
using namespace genv;
using namespace std;

DynString::DynString(int x, int y, int sx, int sy, string placeholder, string body)
    : Widget(x,y,sx,sy), _bg_color(255,255,255), _text_color(100,100,100), _button_color(255,255,255), _highlight_color(15,192,252)
{
    _placeholder = placeholder;
    _body = body;
}

void DynString::select()
{
    _text_color = color(0,0,0);
    _selected = true;
}
void DynString::deselect()
{
    _text_color = color(100,100,100);
    _selected = false;
}

void DynString::draw() const
{
    string body = _body;
    if(body.length() == 0 && !_selected)
        body = _placeholder;
    if(_selected)
    {
        gout << _highlight_color << move_to(_x-1,_y-1) << box(_size_x+2,_size_y+2);
        body += '|';
    }
    gout << _text_color << move_to(_x, _y) << box(_size_x, _size_y);
    gout << _bg_color << move_to(_x+2, _y+2) << box(_size_x-4, _size_y-4);
    gout << _text_color << move_to(_x+5,_y+_size_y/2+gout.cascent()/2) << text(trim(body,_size_x-10));
}
void DynString::handle(event ev)
{
    if(ev.keycode == key_backspace)
    {
        if(_body != "")
            _body = _body.substr(0,_body.length()-1);
    }
    else if(ev.keycode > 0 && ev.keycode != key_tab && ev.keycode != key_lshift && ev.keycode != key_rshift && gout.twidth(_body+(char)ev.keycode) < _size_x-12)
        _body += ev.keycode;
}
string DynString::val() const
{
    return _body;
}
void DynString::log(ostream &logfile) const
{
    logfile << "#noinfo" << endl;
}
