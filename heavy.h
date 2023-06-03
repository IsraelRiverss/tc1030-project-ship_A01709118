// =========================================================
// File: heavy.h
// Author: Fernando Israel Rios Garcia
// Date: 06/02/2023
// Description:
// =========================================================
#ifndef HEAVY_H
#define HEAVY_H

#include "container.h"

class HeavyContainer : public Container {
public:
  HeavyContainer(int id, int weight);
  HeavyContainer(int, int, ContainerType);
  HeavyContainer(const HeavyContainer&);

  double getConsumption() const;
};

HeavyContainer::HeavyContainer(int id, int weight) :Container(id, weight >= 0 ? weight : 0, LIGHT) {}

HeavyContainer::HeavyContainer(int id, int weight)
double HeavyContainer::getConsumption() const {
    return 3 * getWeight(); // El consumo de combustible por llevar este tipo de contenedor es 3 veces el peso del mismo
}
#endif