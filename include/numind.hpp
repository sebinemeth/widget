#ifndef NUMIND_HPP_INCLUDED
#define NUMIND_HPP_INCLUDED

#include "graphics.hpp"
#include "widgets.hpp"
using namespace genv;

class NumInd : public Widget {
protected:
    int _val, _min, _max;
    color _bg_color, _text_color, _button_color, _highlight_color;
public:
    NumInd(int x, int y, int sx, int sy, int mn, int mx, int def);
    virtual void draw() const ;
    virtual void handle(genv::event ev);
    virtual void change_val(int amount);
    virtual void select();
    virtual void deselect();
    virtual int get_val() const;
    virtual void log(ostream &logfile) const;
};


#endif // NUMIND_HPP_INCLUDED
