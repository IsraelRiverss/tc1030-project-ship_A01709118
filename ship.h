// =========================================================
// File: ship.h
// Author:
// Date:
// Description:
// =========================================================
#ifndef SHIP_H
#define SHIP_H

#include <list>
#include <string>
#include <sstream>
#include <iomanip>
#include "container.h"
#include "light.h"
#include "heavy.h"
#include "refrigerated.h"
#include "liquid.h"
#include "simpleship.h"
#include "port.h"

class Ship : public SimpleShip {
private:
  int currentWeight, totalWeight;
  int currentNumberOfAllContainers, maxNumberOfAllContainers;
  int currentNumberOfHeavyContainers, maxNumberOfHeavyContainers;
  int currentNumberOfRefrigeratedContainers, maxNumberOfRefrigeratedContainers;
  int currentNumberOfLiquidContainers, maxNumberOfLiquidContainers;
  double fuel, fuelConsumptionPerKM;
  Port *currentPort;
  std::list<Container*> containers;

  bool contains(Container*);
  void remove(Container*);

public:
  Ship(int, Port*, int, int, int, int, int, double);
  Ship(const Ship&);

  int getId() const;
  int getCurrentWeight() const;
  int getTotalWeight() const;
  int getCurrentNumberOfAllContainers() const;
  int getMaxNumberOfAllContainers() const;
  int getCurrentNumberOfHeavyContainers() const;
  int getMaxNumberOfHeavyContainers() const;
  int getCurrentNumberOfRefrigeratedContainers() const;
  int getMaxNumberOfRefrigeratedContainers() const;
  int getCurrentNumberOfLiquidContainers() const;
  int getMaxNumberOfLiquidContainers() const;
  double getFuel() const;
  double getFuelConsumptionPerKM() const;
  Port* getCurrentPort() const;
  std::list<Container*> getCurrentContainers() const;

  bool sailTo(Port*);
  void reFuel(double);
  bool load(Container*);
  bool unLoad(Container*);

  std::string toString() const;
};

Ship::Ship(int id, Port* currentPort, int totalWeight, int maxNumberOfAllContainers, int maxNumberOfHeavyContainers, int maxNumberOfRefrigeratedContainers, int maxNumberOfLiquidContainers, double fuelConsumptionPerKM): SimpleShip(id) {
  this->currentWeight = 0;
  this->totalWeight = totalWeight;
  this->currentNumberOfAllContainers = 0;
  this->maxNumberOfAllContainers = maxNumberOfAllContainers;
  this->currentNumberOfHeavyContainers = 0;
  this->maxNumberOfHeavyContainers = maxNumberOfHeavyContainers;
  this->currentNumberOfRefrigeratedContainers = 0;
  this->maxNumberOfRefrigeratedContainers = maxNumberOfRefrigeratedContainers;
  this->currentNumberOfLiquidContainers = 0;
  this->maxNumberOfLiquidContainers = maxNumberOfLiquidContainers;
  this->fuel = 0;
  this->fuelConsumptionPerKM = fuelConsumptionPerKM;
  this->currentPort = currentPort;
}

Ship::Ship(const Ship &other):SimpleShip(id) {
  currentWeight = other.currentWeight;
  totalWeight = other.totalWeight;
  maxNumberOfAllContainers = other.maxNumberOfAllContainers;
  currentNumberOfAllContainers = other.currentNumberOfAllContainers;
  maxNumberOfHeavyContainers = other.maxNumberOfHeavyContainers;
  currentNumberOfHeavyContainers = other.currentNumberOfHeavyContainers;
  maxNumberOfRefrigeratedContainers = other.maxNumberOfRefrigeratedContainers;
  currentNumberOfRefrigeratedContainers = other.currentNumberOfRefrigeratedContainers;
  maxNumberOfLiquidContainers = other.maxNumberOfLiquidContainers;
  currentNumberOfLiquidContainers = other.currentNumberOfLiquidContainers;
  fuel = other.fuel;
  fuelConsumptionPerKM = other.fuelConsumptionPerKM;
  currentPort = other.currentPort;
}

//Getters
int Ship::getId() const {
  return id;
}
int Ship::getCurrentWeight() const {
  return currentWeight;
}
int Ship::getTotalWeight() const {
  return totalWeight;
}
int Ship::getCurrentNumberOfAllContainers() const {
  return currentNumberOfAllContainers;
}
int Ship::getMaxNumberOfAllContainers() const {
  return maxNumberOfAllContainers;
}
int Ship::getCurrentNumberOfHeavyContainers() const {
  return currentNumberOfHeavyContainers;
}
int Ship::getMaxNumberOfHeavyContainers() const {
  return maxNumberOfHeavyContainers;
}
int Ship::getCurrentNumberOfRefrigeratedContainers() const {
  return currentNumberOfRefrigeratedContainers;
}
int Ship::getMaxNumberOfRefrigeratedContainers() const {
  return maxNumberOfRefrigeratedContainers;
}
int Ship::getCurrentNumberOfLiquidContainers() const {
  return currentNumberOfLiquidContainers;
}
int Ship::getMaxNumberOfLiquidContainers() const {
  return maxNumberOfLiquidContainers;
}
double Ship::getFuel() const {
  return fuel;
}
double Ship::getFuelConsumptionPerKM() const {
  return fuelConsumptionPerKM;
}
Port* Ship::getCurrentPort() const {
  return currentPort;
}
std::list<Container*> Ship::getCurrentContainers() const { //List of pointers to Container Class objects
  return containers;
}

//Methods
bool Ship::sailTo(Port* port) {
  double fuelConsumptionPerContianer = 0;
  double totalFuelConsumption = 0;
  double distance = this->currentPort->getDistance(port);
  for (auto it = containers.begin(); it != containers.end(); ++it) {
    fuelConsumptionPerContianer += (*it)->getConsumption();
  }
  totalFuelConsumption = fuelConsumptionPerContianer + (fuelConsumptionPerKM * distance);
  if (totalFuelConsumption <= fuel) {
    fuel -= totalFuelConsumption;
    currentPort->outgoingShip(this);
    port->incomingShip(this);
    currentPort = port;
    return true;
    }
}
void Ship::reFuel (double amount) {
  if (amount > 0) {
    amount += fuel;
  }
}
bool Ship::load(Container* container) {
  if ((currentPort->contains(container) == false) || (currentNumberOfAllContainers >= maxNumberOfAllContainers) || (currentWeight + container->getWeight() > totalWeight)) {
    return false;
  }
  ContainerType type = container->getType();
    if (type == HEAVY && currentNumberOfHeavyContainers <= maxNumberOfHeavyContainers)
    {
      currentPort->remove(container);
      containers.push_back(container);
      currentNumberOfAllContainers += 1;
      currentNumberOfHeavyContainers += 1;
      currentWeight = currentWeight + container->getWeight();
      return true;
    }
    else if (type == LIQUID && currentNumberOfLiquidContainers <= maxNumberOfLiquidContainers)
    {
      currentPort->remove(container);
      containers.push_back(container);
      currentNumberOfAllContainers += 1;
      currentNumberOfLiquidContainers += 1;
      currentWeight = currentWeight + container->getWeight();
      return true;
    }
    else if (type == REFRIGERATED && currentNumberOfRefrigeratedContainers <= maxNumberOfRefrigeratedContainers)
    {
      currentPort->remove(container);
      containers.push_back(container);
      currentNumberOfAllContainers += 1;
      currentNumberOfRefrigeratedContainers += 1;
      currentWeight = currentWeight + container->getWeight();
      return true;
    }
    else if (type == LIGHT)
    {
      currentPort->remove(container);
      containers.push_back(container);
      currentNumberOfAllContainers += 1;
      currentWeight = currentWeight + container->getWeight();
      return true;
    }
    else
      return false;
  }
bool Ship::contains(Container* container) { //Check method????
  for (auto it = containers.begin(); it != containers.end(); ++it) {
    if (*it == container) {
      return true;
    }
  }
}
void Ship::remove(Container* container) { //Check method????
  for (auto it = containers.begin(); it != containers.end(); ++it) {
    if (*it == container) {
      containers.erase(it);
      return;
    }
  }
}
bool Ship::unLoad(Container* container) {
  if (contains(container) == false) {
    return false;
  }
  ContainerType type = container->getType();
  if (type == HEAVY) {
    containers.remove(container);
    this->currentPort->add(container);
    currentNumberOfAllContainers -= 1;
    currentNumberOfHeavyContainers -= 1;
    return true;
  }
  if (type == LIQUID) {
    containers.remove(container);
    this->currentPort->add(container);
    currentNumberOfAllContainers -= 1;
    currentNumberOfLiquidContainers -= 1;
    return true;
  }
  if (type == REFRIGERATED) {
    containers.remove(container);
    this->currentPort->add(container);
    currentNumberOfAllContainers -= 1;
    currentNumberOfRefrigeratedContainers -= 1;
    return true;
  }
  if (type == LIGHT) {
    containers.remove(container);
    this->currentPort->add(container);
    currentNumberOfAllContainers -= 1;
    return true;
  }
  else {
    return false;
  }
}

std::string Ship::toString() const{

  std::stringstream ss;
  ss << std::fixed << std::setprecision(2);

  ss << "\tShip " << this->id << ": " << this->fuel <<std::endl;

  if(currentNumberOfAllContainers != 0){
    
    ss << "\t\tLight Containers: ";
    for (std::list<Container*>::const_iterator it = this->containers.begin(); it != this->containers.end(); ++it) {
      if ((*it)->getType() == LIGHT) {
        ss << (*it)->getId() << " ";
      }
      }
    ss << std::endl;

    ss << "\t\tHeavy Containers: ";
    for (std::list<Container*>::const_iterator it = this->containers.begin(); it != this->containers.end(); ++it) {
      if ((*it)->getType() == HEAVY) {
        ss << (*it)->getId() << " ";
      }
    }
    ss << std::endl;

    ss << "\t\tRefrigerated Containers: ";
    for (std::list<Container*>::const_iterator it = this->containers.begin(); it != this->containers.end(); ++it) {
      if ((*it)->getType() == REFRIGERATED) {
        ss << (*it)->getId() << " ";
      }
    }
    ss << std::endl;

    ss << "\t\tLiquid Containers: ";
    for (std::list<Container*>::const_iterator it = this->containers.begin(); it != this->containers.end(); ++it) {
      if ((*it)->getType() == LIQUID) {
        ss << (*it)->getId() << " ";
      }
    }
    ss << std::endl;
  }

  return ss.str();


}
#endif
