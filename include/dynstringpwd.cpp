#include "dynstringpwd.hpp"
#include "graphics.hpp"
#include <string>
using namespace genv;
using namespace std;

DynStringPwd::DynStringPwd(int x, int y, int sx, int sy, string body)
    : DynString(x,y,sx,sy,body)
{}

void DynStringPwd::draw() const
{
    string body = "";
    for(int i=0; i<_body.length(); i++)
        body += '.';
    if(_selected)
        body += '|';
    gout << _text_color << move_to(_x, _y) << box(_size_x, _size_y);
    gout << _bg_color << move_to(_x+2, _y+2) << box(_size_x-4, _size_y-4);
    gout << _text_color << move_to(_x+5,_y+_size_y/2+gout.cascent()/2) << text(body);
}
