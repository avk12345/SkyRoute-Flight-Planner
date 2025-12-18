#ifndef APPLICATION_H
#define APPLICATION_H

#include <FL/Fl_Scroll.H>
#include <Graph.h>
#include <bobcat_ui/bobcat_ui.h>
#include <bobcat_ui/button.h>
#include <bobcat_ui/dropdown.h>
#include <bobcat_ui/textbox.h>
#include <bobcat_ui/window.h>
#include <string>

class Application : public bobcat::Application_ {
    bobcat::Window *window;
    bobcat::Dropdown *start;
    bobcat::Dropdown *dest;
    bobcat::TextBox *totalBox;

    bobcat::Button *costButton;
    bobcat::Button *timeButton;
    bobcat::Button *stopsButton;


    Fl_Scroll *results;

    ArrayList<Vertex *> citiesTime;
    ArrayList<Vertex *> citiesCost;
    Graph gTime;
    Graph gCost;

    void initData();
    void initInterface();

    void makeGraph(std::string fileName);
    void writeCity(std::string cityName, bool end, int x, int y);

    void handleClick(bobcat::Widget *sender);

    int fileLength(std::string fileName);

public:
    Application(); // Constructor for the app
};

#endif