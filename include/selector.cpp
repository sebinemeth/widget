#include <iostream>
#include "selector.hpp"
#include "graphics.hpp"
using namespace genv;
using namespace std;

Selector::Selector(int x, int y, int sx, int sy, vector<string> content, int def, int shown_elements, int max_width)
    : Widget(x,y,sx,sy),
    _content(content),
    _val(min(max(def,-1),(int)content.size()-1)),
    _first_shown(0),
    _shown_num(shown_elements),
    _open(false),
    _max_width(max_width),
    _scrollbar_dragged(false), _drag_y(0),
    _bg_color(255,255,255),
    _text_color(100,100,100),
    _highlight_color(15,192,252),
    _scroll_color(100,100,100)
{
    set_val(_val);
    if(_content.size() == 1)
        set_val(0);
    enlarge();
}

void Selector::select()
{
    _text_color = color(0,0,0);
    _selected = true;
}

void Selector::deselect()
{
    _text_color = color(100,100,100);
    _selected = false;
    close();
}

void Selector::open()
{
    if(_content.size() != 0) _open = true;
    set_display(_val,_first_shown,true);
}

void Selector::close()
{
    _open = false;
}

void Selector::enlarge()
{
    int maxlength = gout.twidth("Choose...");
    int index = -1;
    for (int i=0;i<_content.size();i++)
        if(gout.twidth(_content[i]) > maxlength)
        {
            maxlength = gout.twidth(_content[i]);
            index = i;
        }
    _size_x = min(max(_size_x,maxlength+15+_size_y),_max_width);
}

void Selector::drag(event ev)
{
    _drag_y = ev.pos_y - _scroll_y;
    _scrollbar_dragged = true;
}

void Selector::release()
{
    set_display(_val,_first_shown);
    _scrollbar_dragged = false;
}

void Selector::add(string New, bool newdef)
{
    _content.push_back(New);
    enlarge();
    if(newdef)
        set_val(_content.size()-1);
    else
        set_val(_val);
}

void Selector::del(int index)
{
    if(index > -1 && index < _content.size())
    {
        _content.erase(_content.begin()+index);
        set_val(_val);
    }
}

void Selector::multiple_add(vector<string> New, int newdef)
{
    for (unsigned int i=0;i<New.size();i++)
        add(New[i],newdef == i);
}

void Selector::draw() const
{
    string display;
    if(_val != -1)
        display = _content[_val];
    else if(_content.size() == 0)
        display = "No items...";
    else
        display = "Choose...";
    if(_selected)
        gout << _highlight_color << move_to(_x-1,_y-1) << box(_size_x+2,_size_y+2);
    gout << move_to(_x,_y) << _text_color << box(_size_x,_size_y);
    gout << move_to(_x+2,_y+2) << _bg_color << box(_size_x-4,_size_y-4);
    gout << move_to(_x+_size_x-_size_y,_y) << _text_color << box(_size_y,_size_y);
    gout << _text_color << move_to(_x+7,_y+_size_y/2+gout.cascent()/2) << text(trim(display,_max_width-15-_size_y));
    if(!_open)
    {
        //nyíl
        gout << _bg_color;
        gout << move_to(_x+_size_x-_size_y/2,_y+2*_size_y/3) << line(_size_y/6,-_size_y/4)
        << move_to(_x+_size_x-_size_y/2,_y+2*_size_y/3) << line(-_size_y/6,-_size_y/4);
    }
    else
    {
        //nyíl
        gout << _bg_color;
        gout << move_to(_x+_size_x-_size_y/2,_y+_size_y/3) << line(_size_y/6,_size_y/4)
        << move_to(_x+_size_x-_size_y/2,_y+_size_y/3) << line(-_size_y/6,_size_y/4);
        //lenyitás
        gout << _text_color << move_to(_x,_y+_size_y) << box(_size_x,min((int)_content.size(),_shown_num)*25+2)
        << _bg_color << move_to(_x+2,_y+_size_y) << box(_size_x-4,min((int)_content.size(),_shown_num)*25);
        //kiemelés
        if(_val != -1 && _val >= _first_shown && _val < _first_shown + _shown_num)
            gout << _highlight_color << move_to(_x+2,_y+_size_y+(_val-_first_shown)*25) << box(_size_x-4-_scroll_width,25);
        //opciók
        for (unsigned int i=_first_shown;i<_first_shown+min((int)_content.size(),_shown_num);i++)
            gout << _text_color << move_to(_x+7,_y+_size_y+25/2+gout.cascent()/2+(i-_first_shown)*25) << text(trim(_content[i],_max_width-15-_size_y));
        //scrollbar
        if(_content.size() > _shown_num)
        {
            //scroll up
            gout << _scroll_color << move_to(_x+_size_x-_size_y,_y+_size_y) << box(_scroll_width,_scroll_width)
            << _bg_color << move_to(_x+_size_x-_size_y/2,_y+4*_size_y/3) << line(_size_y/6,_size_y/4)
            << move_to(_x+_size_x-_size_y/2,_y+4*_size_y/3) << line(-_size_y/6,_size_y/4);

            //scroll down
            gout << _scroll_color << move_to(_x+_size_x-_size_y,_y+_size_y+(_shown_num-1)*25-3) << box(_scroll_width,_scroll_width)
            << _bg_color << move_to(_x+_size_x-_size_y/2,_y+5*_size_y/3+(_shown_num-1)*25-3) << line(_size_y/6,-_size_y/4)
            << move_to(_x+_size_x-_size_y/2,_y+5*_size_y/3+(_shown_num-1)*25-3) << line(-_size_y/6,-_size_y/4);

            //drag
            gout << color(200,200,200) << move_to(_scroll_x,_scroll_y) << box(_scroll_width,_scroll_height);
        }
    }
}

void Selector::handle(event ev)
{
    bool buttonover = ev.pos_x>_x+_size_x-_size_y && ev.pos_x<_x+_size_x && ev.pos_y>_y && ev.pos_y<_y+_size_y;
    if((ev.button == btn_left && buttonover) || ev.keycode == key_space || ev.keycode == key_enter)
    {
        if(_open) close();
        else open();
    }
    if(ev.keycode == key_up)
        set_val(_val-1);
    if(ev.keycode == key_down)
        set_val(_val+1);
    if(ev.button == btn_left && ev.pos_x > _x+2 && ev.pos_x < _x+_size_x-4-_scroll_width && _open)
    {
        for (unsigned int i=0;i<_content.size();i++)
            if(ev.pos_y > _y+_size_y+i*25 && ev.pos_y < _y+_size_y+(i+1)*25)
            {
                _val = i+_first_shown;
                close();
                break;
            }
    }
    //click on scrollbar
    if(ev.button == btn_left && ev.pos_x > _x+_size_x-_size_y && ev.pos_x < _x+_size_x-2)
    {
        //scroll up
        if(ev.pos_y > _y+_size_y && ev.pos_y < _y+_size_y+_scroll_width)
            set_display(_val,_first_shown-1);
        //scroll down
        if(ev.pos_y > _y+_size_y+_shown_num*25-_scroll_width && ev.pos_y < _y+_size_y+_shown_num*25)
            set_display(_val,_first_shown+1);
        //drag
        if(ev.pos_y > _scroll_y && ev.pos_y < _scroll_y + _scroll_height)
            drag(ev);
    }
    //wheel scrolling
    //scroll in closed state:
    if(ev.button == btn_wheelup)
    {
        if(!_open)
            set_val(_val-1);
        else if(_content.size() > _shown_num)
            set_display(_val,_first_shown-1);
    }
    if(ev.button == btn_wheeldown)
    {
        if(!_open)
            set_val(_val+1);
        else if(_content.size() > _shown_num)
            set_display(_val,_first_shown+1);
    }

    //no scroll in closed state:
    /*if(ev.button == btn_wheelup && _content.size() > _shown_num)
        set_display(_val,_first_shown-1);
    if(ev.button == btn_wheeldown && _content.size() > _shown_num)
        set_display(_val,_first_shown+1);*/

    //dragged moving
    if(_scrollbar_dragged)
    {
        _scroll_y = min(max(ev.pos_y - _drag_y,_y+_size_y+_scroll_width),_y+_size_y-_scroll_width+_shown_num*25-_scroll_height);
        int element_height = _scroll_height/_shown_num;
        _first_shown = min(max((_scroll_y-_y-_size_y-_scroll_width)/element_height,0),(int)_content.size()-_shown_num);
    }
    if(ev.button == -btn_left)
        release();
}

bool Selector::is_hover(int mouse_x, int mouse_y) const
{
    if (_open)
        return mouse_x>_x && mouse_x<_x+_size_x && mouse_y>_y && mouse_y<_y+_size_y+_content.size()*25+2;
    else
        return mouse_x>_x && mouse_x<_x+_size_x && mouse_y>_y && mouse_y<_y+_size_y;
}

void Selector::set_val(int val)
{
    _val = min(max(val,-1),(int)_content.size()-1);
    set_display(_val,_first_shown,true);
}

void Selector::set_display(int val, int first_shown, bool movetoval)
{
    //set _first_shown
    if((int)_content.size() > _shown_num)
    {
        if(!movetoval)
            _first_shown = min(max(first_shown,0),(int)_content.size()-_shown_num);
        else
        {
            if(_val > _first_shown+_shown_num-1)
                _first_shown = _val-_shown_num+1;
            if(_val < _first_shown && _val > -1)
                _first_shown = _val;
        }
    }
    //set scrollbar
    _scroll_x = _x+_size_x-_size_y;
    _scroll_y = _y+_size_y+_scroll_width+ (float)_first_shown/(float)_content.size()*(_shown_num*25-_scroll_width*2);
    _scroll_width = (int)_content.size() > _shown_num ? _size_y-2 : 0;
    _scroll_height = (float)_shown_num/(float)_content.size()*(_shown_num*25-_scroll_width*2)+1;
}

int Selector::val() const
{
    return _val;
}
string Selector::get_content() const
{
    return _val == -1 ? "" : _content[_val];
}

void Selector::log(ostream &logfile) const
{
    logfile << "widget_class: Selector" << endl
    << "options: [" << endl;
    for (unsigned int i=0;i<_content.size();i++)
        logfile << "\t" << i << ":" << _content[i] << endl;
    logfile << "]" << endl
    << "value: " << _val << endl
    << "number of shown elements: " << _shown_num << endl
    << "index of first shown element: " << _first_shown << endl
    << "selected: ";
    is_selected() ? logfile << "true" : logfile << "false";
    logfile << endl
    << endl;
}
