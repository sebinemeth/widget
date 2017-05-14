#ifndef SELECT_HPP_INCLUDED
#define SELECT_HPP_INCLUDED

#include "graphics.hpp"
#include "widgets.hpp"
#include <vector>
using namespace genv;

class Selector : public Widget {
protected:
    vector<string> _content;
    color _bg_color, _text_color, _highlight_color, _scroll_color;
    int _val;
    int _first_shown;
    int _shown_num;
    bool _scrollbar_dragged;
    int _drag_y, _scroll_x, _scroll_y, _scroll_width, _scroll_height;
    int _max_width;
    bool _open;
public:
    Selector(int x, int y, int sx, int sy, vector<string> content, int def = -1, int show_elements = 5, int max_width = 500);
    virtual void draw() const ;
    virtual void handle(genv::event ev);
    virtual bool is_hover(int mouse_x, int mouse_y) const;
    virtual int val() const;
    virtual string get_content() const;
    virtual void set_val(int val);
    virtual void set_display(int val, int first_shown, bool movetoval = false);
    virtual void select();
    virtual void deselect();
    virtual void open();
    virtual void close();
    virtual void enlarge();
    virtual void drag(event ev);
    virtual void release();
    virtual void add(string New,bool newdef = false);
    virtual void del(int index /*= _val*/);
    virtual void multiple_add(vector<string> New,int newdef = -1);
    virtual void log(ostream &logfile) const;
};


#endif // SELECT_HPP_INCLUDED
