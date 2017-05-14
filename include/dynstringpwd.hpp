#ifndef DYNSTRINGPWD_HPP_INCLUDED
#define DYNSTRINGPWD_HPP_INCLUDED

#include "graphics.hpp"
#include "widgets.hpp"
#include "dynstring.hpp"
using namespace std;

class DynStringPwd : public DynString {
public:
    DynStringPwd(int x, int y, int sx, int sy, string body);
    virtual void draw() const;
};

#endif // DYNSTRINGPWD_HPP_INCLUDED
