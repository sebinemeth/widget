#include "widgets.hpp"
#include "graphics.hpp"
using namespace genv;

Widget::Widget(int x, int y, int sx, int sy, bool selectable)
{
    _x=x;
    _y=y;
    _size_x = sx;
    _size_y=sy;
    _selected = false;
    _selectable = selectable;
}

bool Widget::is_hover(int mouse_x, int mouse_y) const
{
    return mouse_x>_x && mouse_x<_x+_size_x && mouse_y>_y && mouse_y<_y+_size_y;
}
bool Widget::is_selected() const
{
    return _selected;
}
bool Widget::is_selectable() const
{
    return _selectable;
}
void Widget::select()
{
    _selected = true;
}
void Widget::deselect()
{
    _selected = false;
}
string Widget::trim(string s, int w) const
{
    if(gout.twidth(s) > w)
    {
        while (gout.twidth(s+"...") > w)
            s = s.substr(0,s.length()-1);
        return s+"...";
    }
    return s;
}
void Widget::draw() const {}
void Widget::log(ostream &logfile) const {}
void Widget::handle(event ev) {}





