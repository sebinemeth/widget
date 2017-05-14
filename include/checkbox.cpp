#include "checkbox.hpp"
#include "graphics.hpp"
using namespace genv;

CheckBox::CheckBox(int x, int y, int sx, int sy, bool checked)
    : Widget(x,y,sx,sy), _bg_color(255,255,255), _text_color(100,100,100), _button_color(255,255,255), _highlight_color(15,192,252)
{
    _checked=checked;
}

void CheckBox::draw() const
{
    if(_selected)
    {
        gout << _highlight_color << move_to(_x-1,_y-1) << box(_size_x+2,_size_y+2);
    }
    gout << _text_color << move_to(_x, _y) << box(_size_x, _size_y);
    gout << _bg_color << move_to(_x+2, _y+2) << box(_size_x-4, _size_y-4);
    if (_checked) {
        gout << _text_color;
        gout << move_to(_x+4, _y+4) << line(_size_x-8, _size_y-8);
        gout << move_to(_x+5, _y+4) << line(_size_x-8, _size_y-8);
        gout << move_to(_x+_size_x-4, _y+4) << line(-_size_x+8, _size_y-8);
        gout << move_to(_x+_size_x-5, _y+4) << line(-_size_x+8, _size_y-8);
    }
}

void CheckBox::handle(event ev)
{
    if (ev.type == ev_key && (ev.keycode == key_enter || ev.keycode == ' ')) {
        _checked = !_checked;
    }
    if (ev.type == ev_mouse && ev.button==btn_left && is_hover(ev.pos_x,ev.pos_y)) {
        _checked = !_checked;
    }
}
bool CheckBox::is_checked() const
{
    return _checked;
}
void CheckBox::select()
{
    _text_color = color(0,0,0);
    _selected = true;
}
void CheckBox::deselect()
{
    _text_color = color(100,100,100);
    _selected = false;
}
