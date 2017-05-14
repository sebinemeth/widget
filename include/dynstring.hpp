#ifndef DYNSTRING_HPP_INCLUDED
#define DYNSTRING_HPP_INCLUDED

#include "graphics.hpp"
#include "widgets.hpp"
using namespace std;
using namespace genv;

class DynString : public Widget {
protected:
    string _body;
    string _placeholder;
    color _bg_color, _text_color, _button_color, _highlight_color;
public:
    DynString(int x, int y, int sx, int sy, string placeholder = "Type text...", string body = "");
    virtual void draw() const ;
    virtual void handle(genv::event ev);
    virtual void select();
    virtual void deselect();
    virtual string val() const;
    virtual void log(ostream &logfile) const;
};

#endif // DYNSTRING_HPP_INCLUDED
