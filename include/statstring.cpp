#include "statstring.hpp"
#include "graphics.hpp"
using namespace genv;

StatString::StatString(int x, int y, int sx, int sy, string body, string align, bool show_bg, color bg_color, color text_color)
    : Widget(x,y,sx,sy,false),
    _bg_color(bg_color),
    _text_color(text_color)
{
    _body = body;
    _size_x = max(sx,gout.twidth(_body) + 10);
    _align = (align == "left" || align == "center" || align == "right") ? align : "left";
    _show_bg = show_bg;
}

void StatString::draw() const
{
    if(_show_bg)
        gout << move_to(_x,_y) << _bg_color << box(_size_x,_size_y);
    gout << _text_color;
    if(_align == "left")
        gout << move_to(_x+5,_y+_size_y/2+gout.cascent()/2);
    if(_align == "center")
        gout << move_to(_x+_size_x/2-gout.twidth(_body)/2,_y+_size_y/2+gout.cascent()/2);
    if(_align == "right")
        gout << move_to(_x+_size_x-gout.twidth(_body)-5,_y+_size_y/2+gout.cascent()/2);
    gout << text(_body);
}

void StatString::set_body(string body)
{
    _body = body;
}
