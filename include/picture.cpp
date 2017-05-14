#include "picture.hpp"
#include <fstream>
#include <iostream>


Picture::Picture(string filename, int x, int y, bool transparent, int displayX, int displayY, bool selectable) :
    Widget(x,y,0,0,selectable), _transparent(transparent)
{
    load(filename);
    if(displayX == 0)
        displayX = _size_x;
    if(displayY == 0)
        displayY = _size_y;
    resize(displayX,displayY);
    draw_canvas();
}
void Picture::load(string filename)
{
    ifstream file(filename);
    if(file.fail())
        cout << "Error: Failed to load " << filename << " as picture widget pattern" << endl;
    else
    {
        int r,g,b;
        file >> _size_x >> _size_y;
        for (int j=0; j<_size_y; j++)
        {
            vector<genv::color> row;
            for (int i=0; i<_size_x; i++)
            {
                file >> r >> g >> b;
                row.push_back(genv::color(r,g,b));
            }
            _data.push_back(row);
        }
    }
}
void Picture::draw_canvas()
{
    _c.open(_size_x,_size_y);
    for (int i=0; i<_size_x; i++)
        for (int j=0; j<_size_y; j++)
            _c << genv::move_to(i*_scaleX,j*_scaleY) << _data[j][i] << genv::dot;
    _c.transparent(_transparent);
}
void Picture::draw() const
{
    int x(_x), y(_y);
    genv::canvas c = _c;
    _data.size() == 0 ?
        genv::gout << genv::color(100,100,100) << genv::move_to(x+10,y+20) << genv::text("kep") :
        genv::gout << genv::stamp(c,x,y);
}
void Picture::draw_to(int x,int y)
{
    _x = x; _y = y;
    draw();
}
void Picture::resize(double sx,double sy)
{
    _scaleX = sx/(float)_size_x;
    _scaleY = sy/(float)_size_y;
}
void Picture::reload(string filename)
{
    _data.empty();
    load(filename);
    draw_canvas();
}
