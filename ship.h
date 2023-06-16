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
  // Initialize all state variables to zero.
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
  // Set the current port.
  this->currentPort = currentPort;
}

Ship::Ship(const Ship &Ship):SimpleShip(id) {
  currentPort = Ship.currentPort;
  totalWeight = Ship.totalWeight;
  maxNumberOfAllContainers = Ship.maxNumberOfAllContainers;
  maxNumberOfHeavyContainers = Ship.maxNumberOfHeavyContainers;
  maxNumberOfRefrigeratedContainers = Ship.maxNumberOfRefrigeratedContainers;
  maxNumberOfLiquidContainers = Ship.maxNumberOfLiquidContainers;
  fuelConsumptionPerKM = Ship.fuelConsumptionPerKM;
}

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
  return currentNumberOfAllContainers;
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
int Ship::getMaxNumberOfLiquidContainers() const{
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
std::list<Container*> Ship::getCurrentContainers() const {
  return containers;
}

bool Ship::sailTo(Port* port) {
  double amount = 0;
  for (std::list<Container*>::iterator it = containers.begin(); it != container.end(); it++) {
    acum += (*it)->getConsumption();
  }
}

void Ship::reFuel(double amount) {
  if (amount >= 0) {
    fuel = amount + fuel;
  }
}
#endif
