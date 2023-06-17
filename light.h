// =========================================================
// File: light.h
// Author:
// Date:
// Description:
// =========================================================
#ifndef LIGHT_H
#define LIGHT_H

#include "container.h"

class LightContainer : public Container {
public:
    LightContainer(int id, int weight);
    LightContainer(const LightContainer& other);

    double getConsumption() const override;
};

LightContainer::LightContainer(int id, int weight) : Container(id, weight, LIGHT) {}
LightContainer::LightContainer(const LightContainer& other) : Container(other) {}

double LightContainer::getConsumption() const {
    return 2.5 * getWeight();
}
#endif