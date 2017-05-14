#ifndef WIDGETS_HPP_INCLUDED
#define WIDGETS_HPP_INCLUDED

#include "graphics.hpp"

using namespace std;

class Widget {
protected:
    int _x, _y, _size_x, _size_y;
    bool _selected;
    bool _selectable;
public:
    Widget(int x, int y, int sx, int sy, bool selectable = true);
    virtual bool is_hover(int mouse_x, int mouse_y) const;
    virtual bool is_selected() const;
    virtual bool is_selectable() const;
    virtual void select();
    virtual void deselect();
    virtual void draw() const;
    virtual void log(ostream &logfile) const;
    virtual void handle(genv::event ev);
    virtual string trim(string s, int w) const;
};


#endif // WIDGETS_HPP_INCLUDED
