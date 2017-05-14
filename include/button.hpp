#ifndef BUTTON_HPP_INCLUDED
#define BUTTON_HPP_INCLUDED

#include "graphics.hpp"
#include "widgets.hpp"
#include "window.hpp"
#include <functional>
using namespace genv;

class Button : public Widget {
protected:
    string _label;
    color _bg_color, _text_color, _button_color, _highlight_color;
    bool _pushed;
    std::function<void()> _action;
public:
    Button(int x, int y, int sx, int sy, string label, std::function<void()> action = [](){});
    virtual void draw() const ;
    virtual void handle(genv::event ev);
    virtual void select();
    virtual void deselect();
    virtual void push();
    virtual void release();
    virtual string get_label() const;
    virtual void set_label(string label);
    virtual void set_action(std::function<void()> action);
    virtual void log(ostream &logfile) const;
};


#endif // BUTTON_HPP_INCLUDED
