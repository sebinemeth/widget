#ifndef PICTURE_HPP_INCLUDED
#define PICTURE_HPP_INCLUDED

#include "graphics.hpp"
#include "widgets.hpp"
#include <vector>

class Picture : public Widget
{
protected:
    genv::canvas _c;
    bool _transparent;
    vector<vector<genv::color> > _data;
    double _scaleX, _scaleY;
public:
    Picture(string filename,int x,int y,bool transparent = false, int displayX = 0, int displayY = 0, bool selectable = false);
    void reload(string filename);
    void load(string filename);
    void draw_canvas();
    virtual void draw() const;
    virtual void draw_to(int x,int y);
    virtual void resize(double sx,double sy);
};

#endif // PICTURE_HPP_INCLUDED
