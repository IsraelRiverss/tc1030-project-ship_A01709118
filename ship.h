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
void reFuel (double amount) {
  if (amount > 0) {
    amount += fuel;
  }
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


#endif
