#include "widgets.hpp"
#include "graphics.hpp"
#include "window.hpp"

using namespace genv;

Window::Window(int XX,int YY) :
    _shift(false),
    _stop(false),
    _XX(XX),
    _YY(YY)
{}

int Window::get_XX() const
{
    return _XX;
}
int Window::get_YY() const
{
    return _YY;
}

void Window::stop()
{
    _stop = true;
}
void Window::clear_scr()
{
    gout << move_to(0,0) << color(255,255,255) << box(_XX,_YY);
}

void Window::event_loop() {
    event ev;
    int focus = -1;
    _stop = false;
    bool first = true;
    while(!_stop && (first || gin >> ev)) {
        //TODO deselecting all does not mean loosing focus
        if(ev.keycode == key_lshift || ev.keycode == key_rshift)
            _shift = true;
        if(ev.keycode == -key_lshift || ev.keycode == -key_rshift)
            _shift = false;
        if(ev.keycode == key_tab/* && focus != -1*/)
        {
            if(_shift)
            {
                if(focus!=0)
                    focus--;
                else
                    focus = widgets.size()-1;
                if(!widgets[focus]->is_selectable())
                {
                    if(focus!=0)
                        focus--;
                    else
                        focus = widgets.size()-1;
                }
            }
            else
            {
                if(focus!=(int)widgets.size()-1)
                    focus++;
                else
                    focus = 0;
                if(!widgets[focus]->is_selectable())
                {
                    if(focus!=(int)widgets.size()-1)
                        focus++;
                    else
                        focus = 0;
                }
            }
        }
        bool priority = false;
        if(focus != -1)
            priority = widgets[focus]->is_hover(ev.pos_x,ev.pos_y);
        clear_scr();
        for (size_t i=0;i<widgets.size();i++) {
            if(ev.button == btn_left || ev.keycode == key_tab)
            {
                if((widgets[i]->is_hover(ev.pos_x,ev.pos_y) && !priority && widgets[i]->is_selectable()) || focus == i)
                {
                    focus = i;
                    widgets[i]->select();
                }
                else
                    widgets[i]->deselect();
            }
            if(ev.button == btn_left && !widgets[i]->is_hover(ev.pos_x,ev.pos_y))
                widgets[i]->deselect();
        }
        if (focus != -1)
            widgets[focus]->handle(ev);
        for (size_t i=0;i<widgets.size();i++) {
            widgets[i]->draw();
        }
        if (focus != -1)
            widgets[focus]->draw();
        gout << refresh;
        first = false;
    }
}
