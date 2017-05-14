#include "graphics.hpp"
#include "window.hpp"
#include "widgets.hpp"
#include "checkbox.hpp"
#include "statstring.hpp"
#include "dynstring.hpp"
#include "dynstringpwd.hpp"
#include "alert.hpp"
#include "numind.hpp"
#include "selector.hpp"
#include "button.hpp"
#include "picture.hpp"
#include <vector>
#include <cstdlib>
#include <sstream>
using namespace std;
using namespace genv;


class MyWindow : public Window
{
protected:
    StatString* autolabel;
    Selector* autoinput;
    StatString* emberlabel;
    Selector* emberinput;

    Button* kivesz;

    StatString* kivittlabel;
    Selector* kivittinput;

    Button* visszahoz;

    vector<string> autok;
    vector<string> emberek;
public:
    MyWindow(int XX,int YY);
};

MyWindow::MyWindow(int XX, int YY)
    : Window(XX,YY)
{
    string autocska = "BMW";
    autok.push_back(autocska);
    autocska = "Audi";
    autok.push_back(autocska);
    autocska = "Trabant";
    autok.push_back(autocska);

    string emberke = "Sanyi";
    emberek.push_back(emberke);
    emberke = "Eszter";
    emberek.push_back(emberke);
    emberke = "Jozeph";
    emberek.push_back(emberke);

    autolabel = new StatString(50,50,100,30,"Autok:");
    autoinput = new Selector(250,50,200,30,autok);
    emberlabel = new StatString(50,100,100,30,"Emberek:");
    emberinput = new Selector(250,100,200,30,emberek);

    autok.clear();
    emberek.clear();

    kivesz = new Button(50,150,100,30,"Kivesz",[&](){
                        if(this->autoinput->val() > -1 && this->emberinput->val() > -1)
                        {
                            this->autok.push_back(this->autoinput->get_content());
                            this->emberek.push_back(this->emberinput->get_content());
                            this->kivittinput->add(this->emberinput->get_content() + ": " + this->autoinput->get_content(),true);
                            this->autoinput->del(this->autoinput->val());
                            this->emberinput->del(this->emberinput->val());
                        }
                        });

    kivittlabel = new StatString(50,200,100,30,"Kivitt autok:");
    vector<string> ures;
    kivittinput = new Selector(250,200,200,30,ures);

    visszahoz = new Button(50,250,100,30,"Visszahoz",[&](){
                        if(this->kivittinput->val())
                        {
                            this->autoinput->add(autok[kivittinput->val()],true);
                            this->emberinput->add(emberek[kivittinput->val()],true);
                            /*for (int i=kivittinput->val();i<emberek.size();i++)
                            {
                                emberek[i] = emberek[i+1];
                                autok[i] = autok[i+1];
                                emberek.pop_back();
                                autok.pop_back();
                            }*/
                        }
                        });

    widgets.push_back(autolabel);
    widgets.push_back(autoinput);
    widgets.push_back(emberlabel);
    widgets.push_back(emberinput);
    widgets.push_back(kivesz);
    widgets.push_back(kivittlabel);
    widgets.push_back(kivittinput);
    widgets.push_back(visszahoz);
}

class Calculator : public Window
{
protected:
    Button *b0, *b1, *b2, *b3, *b4, *b5, *b6, *b7, *b8, *b9, *plusz, *minusz, *eq;
    StatString *screen;
    int _a, _b, _eredmeny;
    char _op;
public:
    Calculator(int XX,int YY);
    void append(int c);
    void set_screen();
};

void Calculator::set_screen()
{
    stringstream scr;
    if(_op != '=')
    {
        scr << _a;
        if(_op != '0')
            scr << " " << _op;
        if(_b != 0)
            scr << " " << _b;
    }
    else
        scr << "ans = " << _eredmeny;
    screen->set_body(scr.str());
}

void Calculator::append(int c)
{
    if(_op == '=')
    {
        _a = 0;
        _b = 0;
        _op = '0';
    }
    if(_op == '0')
    {
        _a *= 10;
        _a += c;
    }
    else
    {
        _b *= 10;
        _b += c;
    }
    if(_op == '+')
        _eredmeny = _a + _b;
    if(_op == '-')
        _eredmeny = _a - _b;
    set_screen();
}

Calculator::Calculator(int XX, int YY)
    : Window(XX,YY), _a(0), _b(0), _eredmeny(0), _op('0')
{
    screen = new StatString(150,100,200,30,"Type something");

    b7 = new Button(150,150,40,30,"7",[this](){append(7);});
    b8 = new Button(200,150,40,30,"8",[this](){append(8);});
    b9 = new Button(250,150,40,30,"9",[this](){append(9);});
    b4 = new Button(150,200,40,30,"4",[this](){append(4);});
    b5 = new Button(200,200,40,30,"5",[this](){append(5);});
    b6 = new Button(250,200,40,30,"6",[this](){append(6);});
    b1 = new Button(150,250,40,30,"1",[this](){append(1);});
    b2 = new Button(200,250,40,30,"2",[this](){append(2);});
    b3 = new Button(250,250,40,30,"3",[this](){append(3);});
    b0 = new Button(200,300,40,30,"0",[this](){append(0);});

    plusz = new Button(350,150,40,30,"+",[this](){_op = '+'; set_screen();});
    minusz = new Button(350,200,40,30,"-",[this](){_op = '-'; set_screen();});
    eq = new Button(350,250,40,30,"=",[this](){_op = '='; set_screen();});

    widgets.push_back(screen);

    widgets.push_back(b0);
    widgets.push_back(b1);
    widgets.push_back(b2);
    widgets.push_back(b3);
    widgets.push_back(b4);
    widgets.push_back(b5);
    widgets.push_back(b6);
    widgets.push_back(b7);
    widgets.push_back(b8);
    widgets.push_back(b9);

    widgets.push_back(plusz);
    widgets.push_back(minusz);
    widgets.push_back(eq);
}

class PictureTester : public Window
{
protected:
    Picture * pic;
public:
    PictureTester(int XX, int YY) :
        Window(XX,XX)
    {
        pic = new Picture("stamp.kep",50,50,true);
        widgets.push_back(pic);
    }

};

int main()
{
    //MyWindow* mywindow = new MyWindow(600,600);
    //gout.open(mywindow->get_XX(),mywindow->get_YY());
    //mywindow->event_loop();

    //Calculator* calc = new Calculator(600,600);
    //gout.open(calc->get_XX(),calc->get_YY());
    //calc->event_loop();

    PictureTester* p = new PictureTester(600,600);
    gout.open(p->get_XX(),p->get_YY());
    p->event_loop();

    return 0;
}
