#ifndef STATSTRING_HPP_INCLUDED
#define STATSTRING_HPP_INCLUDED

#include "graphics.hpp"
#include "widgets.hpp"
using namespace std;
using namespace genv;

class StatString : public Widget {
protected:
    string _body, _align;
    bool _show_bg;
    color _bg_color, _text_color;
public:
    StatString(int x, int y, int sx, int sy, string body, string align = "left", bool show_bg = false, color bg_color = color(255,255,255), color text_color = color(0,0,0));
    virtual void draw() const ;
    virtual void set_body(string body);
};

#endif // STATSTRING_HPP_INCLUDED
