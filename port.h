// =========================================================
// File: port.h
// Author:
// Date:
// Description:
// =========================================================
#ifndef PORT_H
#define PORT_H

#include <list>
#include <cmath>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include "container.h"
#include "simpleship.h"

class Port {
private:
  int id{};
  double x{}, y{};
  std::list<Container*> containers;
  std::list<SimpleShip*> history;
  std::list<SimpleShip*> current;

public:
  Port(int, double, double);
  Port(const Port&);

  int getId() const;
  double getX() const;
  double getY() const;
  std::list<Container*> getContainers() const;
  std::list<SimpleShip*> getHistory() const;
  std::list<SimpleShip*> getCurrent() const;

  double getDistance(Port*) const;
  void incomingShip(SimpleShip*);
  void outgoingShip(SimpleShip*);

  bool contains(Container*);
  void add(Container*);
  void remove(Container*);

  std::string toString() const;
};

Port::Port(int id, double x, double y) {
    this -> id = id;
    this -> x = x;
    this -> y = y;
}

Port::Port(const Port&other) {
    this -> id = other.id;
    this -> x = other.x;
    this -> y = other.y;
}

int Port::getId() const {
    return id;
}

double Port::getX() const {
    return x;
}

double Port::getY() const {
    return y;
}

double Port::getDistance(Port *other) const {
    return sqrt(pow(y - other->y,2)+pow(x - other->x,2));
}

void Port::incomingShip(SimpleShip* ship) {
    if (std::find(current.begin(), current.end(), ship) == current.end()) {
        current.push_back(ship);
    }
}

void Port::outgoingShip(SimpleShip* ship) {
    if (std::find(current.begin(), current.end(), ship) != current.end()) {
      current.remove(ship);
      if (std::find(history.begin(), history.end(), ship) == history.end()) {
        history.push_back(ship);
      }
    }
}

bool Port::contains(Container* container) {
    return std::find(containers.begin(), containers.end(), container) != containers.end();
}

void Port::add(Container* container) {
    containers.push_back(container);
}

void Port::remove(Container* container) {
    containers.remove(container);
}

std::list<Container*> Port::getContainers() const {
    return containers;
}

std::list<SimpleShip*> Port::getHistory() const {
    return history;
}

std::list<SimpleShip*> Port::getCurrent() const {
    return current;
}

std::string Port::toString() const{

    std::stringstream ss;
    ss << std::fixed << std::setprecision(2);

    ss << "Port " << id << ": (" << std::fixed << std::setprecision(2) << x << ", " << y << ")" << std::endl;

    if(containers.size() != 0){
        ss << "\tLight Containers: ";
        for (std::list<Container*>::const_iterator it = containers.begin(); it != containers.end(); ++it) {
            if ((*it)->getType() == LIGHT) {
                ss << (*it)->getId() << " ";
            }
        }
        ss << std::endl;

        ss << "\tHeavy Containers: ";
        for (std::list<Container*>::const_iterator it = containers.begin(); it != containers.end(); ++it) {
            if ((*it)->getType() == HEAVY) {
                ss << (*it)->getId() << " ";
            }
        }
        ss << std::endl;

        ss << "\tRefrigerated Containers: ";
        for (std::list<Container*>::const_iterator it = containers.begin(); it != containers.end(); ++it) {
            if ((*it)->getType() == REFRIGERATED) {
                ss << (*it)->getId() << " ";
            }
        }
        ss << std::endl;

        ss << "\tLiquid Containers: ";
        for (std::list<Container*>::const_iterator it = containers.begin(); it != containers.end(); ++it) {
            if ((*it)->getType() == LIQUID) {
                ss << (*it)->getId() << " ";
            }
        }
        ss << std::endl;

    }

    for (std::list<SimpleShip*>::const_iterator it = current.begin(); it != current.end(); ++it) {

        ss << (*it)->toString();

    }

    return ss.str();

}
#endif