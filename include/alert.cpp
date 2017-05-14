#include "alert.hpp"
#include "graphics.hpp"
#include <vector>
#include <sstream>
using namespace genv;
using namespace std;

Alert::Alert(int x, int y, int sx, int sy, string title, string body)
    : Widget(x,y,sx,sy)
{
    _title = title;
    _body = split(body,sx-15);
    _header_height = 30;
    _size_y = max(_size_y,_header_height + 20 + (5+gout.cascent())*(int)_body.size());
    _dragged = false;
}

void Alert::draw() const
{
    gout << move_to(_x, _y) << color(255,255,255) << box(_size_x, _size_y);
    gout << move_to(_x+2, _y+_header_height+2) << color(0,0,0) << box(_size_x-4, _size_y-_header_height-4);
    gout << color(0,0,0) << move_to(_x+7,_y+_header_height/2+gout.cascent()/2) << text(_title);
    for(unsigned int i=0; i<_body.size(); i++)
        gout << color(255,255,255) << move_to(_x+9,_y+_header_height+4+(5+gout.cascent())*(i+1)) << text(_body[i]);
}

void Alert::handle(event ev)
{
    if(ev.button == btn_left && (ev.pos_y<_y+_header_height))
    {
        _dx = ev.pos_x-_x;
        _dy = ev.pos_y-_y;
        _dragged = true;
    }
    if(ev.button == -btn_left)
        _dragged = false;
    //if(_dragged && ev.type == ev_mouse)
        //moveto(min(max(ev.pos_x-_dx,0),XX-_size_x),min(max(ev.pos_y-_dy,0),YY-_size_y));
}
void Alert::moveto(int x, int y)
{
    _x = x;
    _y = y;
}
vector<string> Alert::split(string s, int sx)
{
    string line, word;
    stringstream sstream;
    vector<string> v;
    sstream << s;
    while(sstream >> word)
    {
        if(gout.twidth(line+word) < sx)
            line += word + ' ';
        else
        {
            v.push_back(line);
            line = word + ' ';
        }
    }
    v.push_back(line);
    return v;
};
