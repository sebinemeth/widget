#ifndef WINDOW_HPP_INCLUDED
#define WINDOW_HPP_INCLUDED

#include "widgets.hpp"

#include <vector>

using namespace std;

class Window {
protected:
    vector<Widget*> widgets;
    bool _shift;
    bool _stop;
    const int _XX;
    const int _YY;
public:
    Window(int XX,int YY);
    virtual void event_loop();
    virtual void stop();
    virtual void clear_scr();
    virtual int get_XX() const;
    virtual int get_YY() const;
};

#endif // WINDOW_HPP_INCLUDED
