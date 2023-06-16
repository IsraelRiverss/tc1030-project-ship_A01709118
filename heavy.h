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
    HeavyContainer(int id, int weight, ContainerType type);
    HeavyContainer(const HeavyContainer& other);

    double getConsumption() const;
};

HeavyContainer::HeavyContainer(int id, int weight) : Container(id, weight, HEAVY) {}

HeavyContainer::HeavyContainer(int id, int weight, ContainerType type) : Container(id, weight, type) {}

HeavyContainer::HeavyContainer(const HeavyContainer& other) : Container(other) {}

double HeavyContainer::getConsumption() const {
    return 3.0 * getWeight();
}
#endif