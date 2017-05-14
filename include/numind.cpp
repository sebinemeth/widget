#include <sstream>
#include "numind.hpp"
#include "graphics.hpp"
using namespace genv;
using namespace std;

NumInd::NumInd(int x, int y, int sx, int sy, int mn, int mx, int def)
    : Widget(x,y,sx,sy), _val(min(max(def,mn),mx)), _min(mn), _max(mx), _bg_color(255,255,255), _text_color(100,100,100), _button_color(255,255,255), _highlight_color(15,192,252)
{}

void NumInd::select()
{
    _text_color = color(0,0,0);
    _selected = true;
}
void NumInd::deselect()
{
    _text_color = color(100,100,100);
    _selected = false;
}

void NumInd::draw() const
{
    stringstream ss;
    string s;
    ss << _val;
    ss >> s;
    if(_selected)
        gout << _highlight_color << move_to(_x-1,_y-1) << box(_size_x+2,_size_y+2);
    //doboz
    gout << move_to(_x,_y) << _text_color << box(_size_x,_size_y);
    gout << move_to(_x+2,_y+2) << _bg_color << box(_size_x-4,_size_y-4);
    //felgomb
    gout << _text_color;
    gout << move_to(_x+_size_x-_size_y/2,_y) << box(_size_y/2,_size_y/2);
    //legomb
    gout << _text_color;
    gout << move_to(_x+_size_x-_size_y/2,_y+_size_y/2) << box(_size_y/2,_size_y/2);
    //szam
    gout << _text_color << move_to(_x+_size_x-_size_y/2-5-gout.twidth(s),_y+_size_y/2+gout.cascent()/2) << text(s);
    //felnyil
    gout << _button_color;
    gout << move_to(_x+_size_x-_size_y/4,_y+_size_y/6) << line(_size_y/6,_size_y/4)
    << move_to(_x+_size_x-_size_y/4,_y+_size_y/6) << line(-_size_y/6,_size_y/4);
    //lenyil
    gout << move_to(_x+_size_x-_size_y/4,_y+5*_size_y/6) << line(_size_y/6,-_size_y/4)
    << move_to(_x+_size_x-_size_y/4,_y+5*_size_y/6) << line(-_size_y/6,-_size_y/4);
}

void NumInd::handle(event ev)
{
    bool upover = ev.pos_x>_x+_size_x-_size_y/2 && ev.pos_x<_x+_size_x && ev.pos_y>_y && ev.pos_y<_y+_size_y/2;
    bool downover = ev.pos_x>_x+_size_x-_size_y/2 && ev.pos_x<_x+_size_x && ev.pos_y>_y+_size_y/2 && ev.pos_y<_y+_size_y;
    if(ev.button == btn_left)
    {
        if(upover)
            change_val(+1);
        if(downover)
            change_val(-1);
    }
    if (ev.keycode == key_up)
        change_val(+1);
    if (ev.keycode == key_down)
        change_val(-1);
    if (ev.keycode == key_pgup)
        change_val(+10);
    if (ev.keycode == key_pgdn)
        change_val(-10);
    if (ev.keycode == key_end)
        change_val(_max-_val);
    if (ev.keycode == key_home)
        change_val(-_val+_min);
}
void NumInd::change_val(int amount)
{
    _val = min(_max,max(_min,_val+amount));
}
int NumInd::get_val() const
{
    return _val;
}
void NumInd::log(ostream &logfile) const
{
    logfile << "widget_class: NumericIndicator" << endl
    << "range: [" << _min << ":" << _max << "]" << endl
    << "value: " << _val << endl
    << "selected: ";
    is_selected() ? logfile << "true" : logfile << "false";
    logfile << endl << endl;
}
