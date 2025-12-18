#include "Graph.h"
#include <Application.h>
#include <FL/Enumerations.H>
#include <FL/Fl_Scroll.H>
#include <bobcat_ui/bobcat_ui.h>
#include <bobcat_ui/button.h>
#include <bobcat_ui/dropdown.h>
#include <bobcat_ui/textbox.h>
#include <bobcat_ui/window.h>
#include <fstream>
#include <string>
#include <array>

using namespace bobcat;
using namespace std;

Application::Application() {
    // App's constructor
    initData();
    initInterface();
}

void Application::handleClick(bobcat::Widget *sender) {

    results->clear();
    window->redraw();

    int startIndex = start->value();
    int destIndex = dest->value();

    if (sender == costButton) {
        cout << "sender is cost" << '\n';
        Waypoint *path =
            gCost.ucs(citiesCost[startIndex], citiesCost[destIndex]);
        if (path) {
            int totalCost = 0, totalTime = 0, totalStops = 0;
            cout << "We found a path" << endl;
            Stack<Waypoint *> stack;
            Waypoint *temp = path;
            while (temp != nullptr) {
                stack.push(temp);
                temp = temp->parent;
            }
            int y = results->y() + 5;
            int topDist = results->y();
            while (!stack.isEmpty()) {
                bool end = false;
                
                temp = stack.peek();
                stack.pop();
                results->add(new TextBox(
                    40, y, 300, 25, temp->vertex->data)); // e.g San Francisco
                y += 40;
                if (temp->parent != nullptr) {
                    totalCost += temp->weight;
                    totalTime += temp->otherWeight;
                    totalStops++;
                    results->add(new TextBox(
                        40, y, 300, 25,
                        "    Flight cost: " + to_string(temp->weight) +
                            " dollars")); // e.g 1000
                    y += 40;
                }
                cout << temp->vertex->data << " " << temp->partialCost << endl;

                totalBox->label("$" + to_string(totalCost) + ", " +
                                to_string(totalTime) + " hours, " +
                                to_string(totalStops) + " stops");
                writeCity(temp->vertex->data, end, 500, topDist);
            }
            delete path;
        } else {
            cout << "There is no path" << endl;
        }

    } else if (sender == timeButton) {
        cout << "sender is time" << '\n';
        Waypoint *path =
            gTime.ucs(citiesTime[startIndex], citiesTime[destIndex]);
        if (path) {
            int totalCost = 0, totalTime = 0, totalStops = 0;
            cout << "We found a path" << endl;
            Stack<Waypoint *> stack;
            Waypoint *temp = path;
            while (temp != nullptr) {
                stack.push(temp);
                temp = temp->parent;
            }
            int y = results->y() + 5;
            while (!stack.isEmpty()) {
                temp = stack.peek();
                stack.pop();
                results->add(new TextBox(40, y, 300, 25, temp->vertex->data));
                y += 40;
                if (temp->parent != nullptr) {
                    totalTime += temp->weight;
                    totalCost += temp->otherWeight;
                    totalStops++;
                    results->add(new TextBox(
                        40, y, 300, 25,
                        "    Flight time: " + to_string(temp->weight) +
                            " hours"));
                    y += 40;
                }
                cout << temp->vertex->data << " " << temp->partialCost << endl;
            }
            totalBox->label("$" + to_string(totalCost) + ", " +
                            to_string(totalTime) + " hours, " +
                            to_string(totalStops) + " stops");
            delete path;
        } else {
            cout << "There is no path" << endl;
        }

    } else {
        cout << "sender is stops" << '\n';
        Waypoint *path =
            gTime.bfs(citiesTime[startIndex], citiesTime[destIndex]);
        if (path) {
            int totalCost = 0, totalTime = 0, totalStops = 0;
            cout << "We found a path" << endl;
            Stack<Waypoint *> stack;
            Waypoint *temp = path;
            while (temp != nullptr) {
                stack.push(temp);
                temp = temp->parent;
            }
            int y = results->y() + 5;
            while (!stack.isEmpty()) {
                temp = stack.peek();
                stack.pop();
                results->add(new TextBox(40, y, 300, 25, temp->vertex->data));
                y += 40;
                if (temp->parent != nullptr) {
                    totalStops++;
                    totalTime += temp->weight;
                    totalCost += temp->otherWeight;
                    results->add(new TextBox(
                        40, y, 300, 25,
                        "    Flight time: " + to_string(temp->weight) +
                            " hours"));
                    y += 40;
                }
                cout << temp->vertex->data << " " << temp->partialCost << endl;
            }
            totalBox->label("$" + to_string(totalCost) + ", " +
                            to_string(totalTime) + " hours, " +
                            to_string(totalStops) + " stops");
            delete path;
        } else {
            cout << "There is no path" << endl;
        }
    }

    results->redraw();

    system("clear");
}

void Application::initData() {

    ifstream VERTEXFILE("assets/vertices.csv");
    ifstream EDGEFILE("assets/edges.csv");

    if (!VERTEXFILE.is_open()) {
        cout << "ERROR OPENING VERTEXFILE\n";
    } else {
        cout << "SUCCESS OPENING VERTEXFILE\n";
    }

    if (!EDGEFILE.is_open()) {
        cout << "ERROR OPENING EDGEFILE\n";
    } else {
        cout << "SUCCESS OPENING EDGEFILE\n";
    }

    string cityString;
    while (getline(VERTEXFILE, cityString)) {
        citiesTime.append(new Vertex(cityString));
        citiesCost.append(new Vertex(cityString));
        cout << "SUCCESS Read City: " << cityString << '\n';
    }

    for (int i = 0; i < citiesTime.size(); i++) {
        gTime.addVertex(citiesTime[i]);
        gCost.addVertex(citiesCost[i]);
    }
    string startCity, destCity, hoursInfo, costInfo;

    while (getline(EDGEFILE, startCity, ',') &&
           getline(EDGEFILE, destCity, ',') &&
           getline(EDGEFILE, hoursInfo, ',') && getline(EDGEFILE, costInfo)) {
        int startCityInt = stoi(startCity);
        int destCityInt = stoi(destCity);
        int hoursInfoInt = stoi(hoursInfo);
        int costInfoInt = stoi(costInfo);

        gTime.addEdge(citiesTime[startCityInt], citiesTime[destCityInt],
                      hoursInfoInt, costInfoInt);
        gCost.addEdge(citiesCost[startCityInt], citiesCost[destCityInt],
                      costInfoInt, hoursInfoInt);

        cout << "SUCCESS Read Info: " << startCityInt << " " << destCityInt
             << " " << hoursInfoInt << " " << costInfoInt << '\n';
    }
}

void Application::initInterface() {
    int len = fileLength("assets/vertices.csv");
    double num = (double) len / 3;

    int x = 300*((int) num);

    window = new Window(100, 100, x, 600, "Flight Planner");

    makeGraph("assets/vertices.csv");
    
    //makeGraph("assets/vertices.csv");

    start = new Dropdown(20, 40, 360, 25, "Starting Point");
    dest = new Dropdown(20, 100, 360, 25, "Destination");

    for (int i = 0; i < citiesTime.size(); i++) {
        start->add(citiesTime[i]->data);
        dest->add(citiesTime[i]->data);
    }

    costButton = new Button(20, 150, 360, 25, "Cheapest");      // ucs
    timeButton = new Button(20, 180, 360, 25, "Shortest Time"); // ucs
    stopsButton = new Button(20, 210, 360, 25, "Least Stops");  // bfs

    ON_CLICK(costButton, Application::handleClick);
    ON_CLICK(timeButton, Application::handleClick);
    ON_CLICK(stopsButton, Application::handleClick);

    results = new Fl_Scroll(20, 270, 360, 275, "Results");
    results->type(Fl_Scroll::VERTICAL_ALWAYS);
    results->align(FL_ALIGN_TOP_LEFT);
    results->box(FL_BORDER_BOX);
    results->end();

    totalBox = new TextBox(20, 560, 360, 30, "Results");
    totalBox->box(FL_BORDER_BOX);

    window->show();
}

void Application::makeGraph(std::string fileName) {
    ifstream VERTEXFILE(fileName);

    int len = fileLength(fileName);
    bobcat::TextBox* cities[len];

    int x = 400;
    int y = 25;

    string cityString;

    for(int j = 0; j < len; j++) {
        getline(VERTEXFILE, cityString);
        cities[j] = new TextBox(x, y, 100, 100, cityString);
        if(y > 400) {
            y = 25;
            x += 200;
            continue;
        }
        y += 200;
    }
}

int Application::fileLength(std::string fileName) {
    ifstream VERTEXFILE(fileName);

    int count = 0;

    if (!VERTEXFILE.is_open()) {
        cout << "ERROR OPENING VERTEXFILE\n";
    } else {
        cout << "SUCCESS OPENING VERTEXFILE\n";
    }

    string cityString;
    while (getline(VERTEXFILE, cityString)) {
        count++;
    }
    cout << count << endl;
    return count;
}


void Application::writeCity(std::string cityName, bool end, int x, int y) {
    bobcat::TextBox* city = new TextBox(x, y, 50, 25, cityName);
    if(!end) {
        bobcat::TextBox* arrowTop = new TextBox(x, y + 10, 1, 1, "|");
        bobcat::TextBox* arrowBot = new TextBox(x, y + 15, 1, 1, "V");
    }
}