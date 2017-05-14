#ifndef ALERT_HPP_INCLUDED
#define ALERT_HPP_INCLUDED

#include "graphics.hpp"
#include "widgets.hpp"
#include <vector>
using namespace std;

class Alert : public Widget {
protected:
    string _title;
    int _header_height;
    bool _dragged;
    int _dx, _dy;
    vector<string> _body;
public:
    Alert(int x, int y, int sx, int sy, string title, string body);
    virtual void draw() const ;
    virtual void handle(genv::event ev);
    virtual void moveto(int x, int y);
    virtual vector<string> split(string s, int sx);
};

#endif // ALERT_HPP_INCLUDED
