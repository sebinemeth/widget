#ifndef CheckBox_HPP_INCLUDED
#define CheckBox_HPP_INCLUDED

#include "graphics.hpp"
#include "widgets.hpp"

using namespace genv;

class CheckBox : public Widget {
protected:
    bool _checked;
    color _bg_color, _text_color, _button_color, _highlight_color;
public:
    CheckBox(int x, int y, int sx, int sy, bool checked = false);
    virtual void draw() const ;
    virtual void handle(genv::event ev);
    virtual bool is_checked() const;
    virtual void select();
    virtual void deselect();
};


#endif // CheckBox_HPP_INCLUDED
